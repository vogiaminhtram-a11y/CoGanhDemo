#ifndef RULES_H
#define RULES_H
#include <vector>
#include <string.h>
#include <iostream>
#include "Common.h"
#include "Board.h"
class Rules {
    public:
    void applyChange (Board &b, int curplayer, Position pos) {
        b.set_Board(pos,curplayer);
    }
    void checkGanh(Position cur,int player, Board &b){
        int opp = (player == 1 ? -1 : 1);
        int dx4[4]={1,0,1,1};
        int dy4[4]={0,1,1,-1};
        int dx2[2]={1,0};
        int dy2[2]={1,0};
        //ô đi 8 hướng
        if ((cur.x+cur.y)%2==0) {
            for (int i = 0; i < 4; i++) {
                int x1 = cur.x + dx4[i], y1 = cur.y + dy4[i];
                int x2 = cur.x - dx4[i], y2 = cur.y - dy4[i];
                if(b.InBound({x1,y1}) && b.InBound({x2,y2})){
                    if(b.get_Board({x1,y1}) == opp && b.get_Board({x2,y2}) == opp) {
                        applyChange(b,player,{x1,y1});
                        applyChange(b,player,{x2,y2});
                    }
                }
            }
        }
        //ô đi 4 hướng
        else {
            for (int i = 0; i < 2; i++) {
                int x1 = cur.x + dx2[i], y1 = cur.y + dy2[i];
                int x2 = cur.x - dx2[i], y2 = cur.y - dy2[i];
                if(b.InBound({x1,y1}) && b.InBound({x2,y2})){
                    if(b.get_Board({x1,y1}) == opp && b.get_Board({x2,y2}) == opp) {
                        applyChange(b,player,{x1,y1});
                        applyChange(b,player,{x2,y2});
                    }
                }
            }
        }
    }
    void dfsNhom(Position cur, int player, bool visited[5][5], std::vector<Position> &nhom, bool &coLoThoat, Board &b) {
        visited[cur.x][cur.y] = true;
        nhom.push_back(cur);
        // kiểm tra có đường thoát không
        if(!b.getMoves(cur).empty()) coLoThoat = true;
        // duyệt các quân cùng phe xung quanh
        std::vector<Position> hangxom = b.Surround(cur, player);
        for(int i = 0; i < hangxom.size(); i++){
            if(!visited[hangxom[i].x][hangxom[i].y]) dfsNhom(hangxom[i], player, visited, nhom, coLoThoat, b);
        }
    }
    //tìm quân bị vây/chẹt
    void checkVay(int player, Board &b){
        int opp = (player == 1 ? -1 : 1);
        bool visited[5][5] = {};
        std::vector<Position> captured;
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                if(b.get_Board({i,j}) != opp || visited[i][j]) continue;
                std::vector<Position> nhom;
                bool coLoThoat = false;
                dfsNhom({i,j}, opp, visited, nhom, coLoThoat, b);
                if(!coLoThoat){
                    for(int i = 0; i < nhom.size(); i++){
                        captured.push_back(nhom[i]);
                    }
                }
            }
        }
        for(int k = 0; k < captured.size(); k++){
            applyChange(b,player,captured[k]);
        }
    }
    void applyRules (Position cur, int player, Board &b) {
        checkGanh (cur,player,b);
        checkVay (player,b);
    }
};


#endif