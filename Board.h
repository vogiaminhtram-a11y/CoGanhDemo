#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <string.h>
#include <iostream>
#include "Common.h"

class Board {
    int board[5][5];
    public:
    void newboard(){
        memset(board, 0, sizeof(board));
        for(int i=0;i<5;i++){
            board[i][0]=-1;
            board[0][i]=1;
            board[i][4]=1;
            board[4][i]=-1;
        }
        board[1][0]=1;
        board[3][4]=-1;
    }
    void set_Board(Position pos, int state){
        board[pos.x][pos.y] = state;
    }
    int get_Board(Position pos) {
        return board[pos.x][pos.y];
    }
    void Xuat() {
        for (int i=0;i<5;i++) {
            for (int j=0;j<5;j++) {
                if (board[i][j]==1) std::cout << "X ";
                else if (board[i][j]==-1) std::cout << "O ";
                else std::cout << ". ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    bool is8Dir(Position pos) {
        return (pos.x + pos.y) % 2 == 0; 
    }
    bool InBound(Position pos) {
        return pos.x>=0 && pos.x<5 && pos.y>=0 && pos.y<5;
    }
    std::vector<Position> Surround(Position cur, int player){
        int dx8[8] = {-1,-1,-1,0,0,1,1,1};
        int dy8[8] = {-1,0,1,-1,1,-1,0,1};
        int dx4[4] = {-1,0,1,0};
        int dy4[4] = {0,1,0,-1};
        std::vector<Position> res;
        if(is8Dir(cur)){
            for(int i=0;i<8;i++){
                int nx = cur.x + dx8[i];
                int ny = cur.y + dy8[i];
                if(InBound({nx,ny}) && board[nx][ny]==player)
                    res.push_back({nx,ny});
            }
        } else {
            for(int i=0;i<4;i++){
                int nx = cur.x + dx4[i];
                int ny = cur.y + dy4[i];
                if(InBound({nx,ny}) && board[nx][ny]==player)
                    res.push_back({nx,ny});
            }
        }
        return res;
    }
    std::vector<Position> getMoves(Position cur) {
        int dx8[8] = {-1,-1,-1,0,0,1,1,1};
        int dy8[8] = {-1,0,1,-1,1,-1,0,1};
        int dx4[4] = {-1,0,1,0};
        int dy4[4] = {0,1,0,-1};
        std::vector<Position> res;
        if(is8Dir(cur)){
            for(int i=0;i<8;i++){
                int nx = cur.x + dx8[i];
                int ny = cur.y + dy8[i];
                if(InBound({nx,ny}) && board[nx][ny]==0)
                    res.push_back({nx,ny});
            }
        } else {
            for(int i=0;i<4;i++){
                int nx = cur.x + dx4[i];
                int ny = cur.y + dy4[i];
                if(InBound({nx,ny}) && board[nx][ny]==0)
                    res.push_back({nx,ny});
            }
        }
        return res;
    }
    int demQuan(int player){
        int dem = 0;
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                if(board[i][j] == player) dem++;
            }
        }
        return dem;
    }

};
#endif