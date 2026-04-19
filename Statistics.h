#ifndef STATISTICS_H
#define STATISTICS_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include "Board.h"
#include "Rules.h"
#include "Common.h"
//thống kê ô
struct CellStat {
    long long lanxet = 0;
    long long tongGanh = 0;
    long long tongChet = 0;
};
//thống kê
struct MoveStat {
    bool valid = false;
    int ganh = 0; 
    int vay = 0;
};
//xếp hạng ô
struct XepHangO{
    Position pos;
    long long lanxet;
    long long tongGanh;
    long long tongChet;
    long long diem;
};

class Statistics {
    CellStat stat[5][5];
public:
    void reset() {
        memset(stat, 0, sizeof(stat));
    }
    // ĐẾM SỐ QUÂN BỊ GÁNH
    int demSoQuanBiGanh(Board &b, Position pos, int player) {
        int dx4[4]={1,0,1,1};
        int dy4[4]={0,1,1,-1};
        int dx2[2]={1,0};
        int dy2[2]={1,0};
        int opp = (player == 1 ? -1 : 1);
        int dem = 0;
        if ((pos.x+pos.y)%2==0) {
            for (int i = 0; i < 4; i++) {
                int x1 = pos.x + dx4[i], y1 = pos.y + dy4[i];
                int x2 = pos.x - dx4[i], y2 = pos.y - dy4[i];
                if(b.InBound({x1,y1}) && b.InBound({x2,y2})){
                    if(b.get_Board({x1,y1}) == opp && b.get_Board({x2,y2}) == opp) {
                        dem += 2;
                    }
                }
            }
        }
        //ô đi 4 hướng
        else {
            for (int i = 0; i < 2; i++) {
                int x1 = pos.x + dx2[i], y1 = pos.y + dy2[i];
                int x2 = pos.x - dx2[i], y2 = pos.y - dy2[i];
                if(b.InBound({x1,y1}) && b.InBound({x2,y2})){
                    if(b.get_Board({x1,y1}) == opp && b.get_Board({x2,y2}) == opp) {
                        dem += 2;
                    }
                }
            }
        }
        return dem;
    }
    // ĐẾM VÂY CHẾT
    int demSoQuanBiVayChet(Board &b, int player){
        Rules r;
        int enemy = (player == 1 ? -1 : 1);
        int dem = 0;
        bool visited[5][5] = {};
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                if(b.get_Board({i,j}) != enemy || visited[i][j]) continue;
                std::vector<Position> nhom;
                bool coLoThoat = false;
                r.dfsNhom({i,j}, enemy, visited, nhom, coLoThoat, b);
                if(!coLoThoat){
                    dem += nhom.size();
                }
            }
        }
        return dem;
    }
    // PHÂN TÍCH 1 NƯỚC ĐI
    MoveStat analyzeMove(const Board &b, Rules &r, Move mv, int player) {
        MoveStat res;
        if (mv.from.x == -1) return res;
        Board temp = b;
        // move
        temp.set_Board(mv.from, 0);
        temp.set_Board(mv.to, player);
        res.valid = true;
        // đếm gánh trước
        res.ganh = demSoQuanBiGanh(temp, mv.to, player);
        // áp dụng luật thật
        r.checkGanh(mv.to, player, temp);  
        // đếm vây sau
        res.vay = demSoQuanBiVayChet(temp, player);
        return res;
    }
    // UPDATE THỐNG KÊ
    void update(Board b, Rules r, int player) {
        std::vector<Move> moves;
        // lấy toàn bộ nước đi hợp lệ
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (b.get_Board({i,j}) != player) continue;
                std::vector<Position> next = b.getMoves({i,j});
                for (int k=0; k<next.size(); k++) {
                    moves.push_back({{i,j}, next[k]});
                }
            }
        }
        for (int i = 0; i < moves.size(); i++ ) {
            Move mv = moves[i];
            MoveStat res = analyzeMove(b, r, mv, player);
            if (!res.valid) continue;
            CellStat &cell = stat[mv.to.x][mv.to.y];
            cell.lanxet++;
            cell.tongGanh += res.ganh;
            cell.tongChet += res.vay;
        }
    }
    // IN KẾT QUẢ
    void In_Bang_Thong_Ke(int player) {
        if (player==1)
        std::cout << "\n===== IN BANG THONG KE ";
        if (player==1) std::cout << "Player 1" << " =====\n";
        else std::cout << "Player 2" << " =====\n";
        std::cout << "[ Lan xet | tong ganh | tong vay chet ]\n";
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                std::cout << "["
                     << stat[i][j].lanxet << "|"
                     << stat[i][j].tongGanh << "|"
                     << stat[i][j].tongChet << "] ";
            }
            std::cout << std::endl;
        }
    }
    void In_Chi_Tiet_Thong_Ke(int player){
        std::cout << "\n=====================================================\n";
        std::cout << "CHI TIET THONG KE TUNG O - BEN ";
        if (player==1) std::cout << "Player 1" << '\n';
        else std::cout << "Player 2" << '\n';
        std::cout << std::left
            << std::setw(8)  << "O"
            << std::setw(12) << "Lan xet"
            << std::setw(12) << "Tong ganh"
            << std::setw(15) << "Tong vay/chet"
            << std::setw(15) << "TB ganh"
            << std::setw(15) << "TB vay/chet"
            << '\n';

        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                double tbGanh = 0.0;
                double tbChet = 0.0;
                if(stat[i][j].lanxet > 0){
                    tbGanh = 1.0 * stat[i][j].tongGanh / stat[i][j].lanxet;
                    tbChet = 1.0 * stat[i][j].tongChet / stat[i][j].lanxet;
                }

                std::cout << std::left
                    << "(" + std::to_string(i) + "," + std::to_string(j) + ")"
                    << std::string(8 - (int)(std::to_string(i).size() + std::to_string(j).size() + 3), ' ')
                    << std::setw(12) << stat[i][j].lanxet
                    << std::setw(12) << stat[i][j].tongGanh
                    << std::setw(15) << stat[i][j].tongChet
                    << std::setw(15) << std::fixed << std::setprecision(2) << tbGanh
                    << std::setw(15) << std::fixed << std::setprecision(2) << tbChet
                    << '\n';
            }
        }
    }
    void In_Top_O(int player){
        std::vector<XepHangO> ds;
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                XepHangO x;
                x.pos={i,j};
                x.lanxet = stat[i][j].lanxet;
                x.tongGanh = stat[i][j].tongGanh;
                x.tongChet = stat[i][j].tongChet;
                x.diem = x.tongGanh + x.tongChet;
                ds.push_back(x);
            }
        }
        std::sort(ds.begin(), ds.end(), [](const XepHangO &a, const XepHangO &b){
            if(a.diem != b.diem) return a.diem > b.diem;
            if(a.tongGanh != b.tongGanh) return a.tongGanh > b.tongGanh;
            if(a.tongChet != b.tongChet) return a.tongChet > b.tongChet;
            return a.lanxet > b.lanxet;
        });
        std::cout << "\n=====================================================\n";
        std::cout << "TOP CAC O TIEM NANG NHAT - BEN ";
        if (player==1) std::cout << "Player 1" << '\n';
        else std::cout << "Player 2" << '\n';
        std::cout << std::left
            << std::setw(8)  << "Hang"
            << std::setw(8)  << "O"
            << std::setw(12) << "Lan xet"
            << std::setw(12) << "Tong ganh"
            << std::setw(15) << "Tong vay/chet"
            << std::setw(10) << "Diem"
            << '\n';

        int topK = 10;
        for(int i = 0; i < topK && i < (int)ds.size(); i++){
            std::cout << std::left
                << std::setw(8) << (i + 1)
                << ("(" + std::to_string(ds[i].pos.x) + "," + std::to_string(ds[i].pos.y) + ")")
                << std::setw(12) << ds[i].lanxet
                << std::setw(12) << ds[i].tongGanh
                << std::setw(15) << ds[i].tongChet
                << std::setw(15) << ds[i].diem
                << '\n';
        }
    }
};

#endif