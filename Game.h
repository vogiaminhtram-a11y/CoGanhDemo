#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "Player.h"
#include "Common.h"
#include "Rules.h"
#include "Board.h"
#include "Statistics.h"
class Game {
    Board b;
    Rules coganh;
    int currentPlayer;
    public:
    void set_up () {
        b.newboard();
        currentPlayer = (rand() % 2 == 0) ? 1 : -1;
    }
    bool hasMove(int player) {
        for (int i=0;i<5;i++){
            for (int j=0;j<5;j++){
                if (b.get_Board({i,j}) == player) {
                    if (!b.getMoves({i,j}).empty())
                        return true;
                }
            }
        }
        return false;
    }
    bool isGameOver(int &winner) {
        bool hasMove1 = hasMove(1);
        bool hasMove2 = hasMove(-1);
        // 1. hết nước đi
        if (!hasMove1) {
            winner=-1;
            return true;
        }
        else if(!hasMove2) {
            winner=1;
            return true;
        }
        // 2. hết quân
        if (b.demQuan(1) == 0 ) {
            winner=-1;
            return true;
        }
        else if (b.demQuan(-1) == 0) {
            winner=1;
            return true;
        }
        return false;
    }
    int process (Player &Player1, Player &Player2, Statistics &Player1_Stat,Statistics &Player2_Stat) {
        int winner=0;
        while (!isGameOver(winner)) {
            //b.Xuat();
            if(currentPlayer == 1) Player1_Stat.update(b, coganh, 1);
            else Player2_Stat.update(b, coganh, -1);
            Move mv;
            if (currentPlayer == 1) {
                mv = Player1.PlayerMove(1, b);
            } else {
                mv = Player2.PlayerMove(-1, b);
            }
            if (!b.InBound(mv.from) || !b.InBound(mv.to)) {
                winner = -currentPlayer;
                break;
            }
            //trước move
            int before = b.demQuan(1) + b.demQuan(-1);
            // thực hiện move
            b.set_Board(mv.to, currentPlayer);
            b.set_Board(mv.from, 0);
            // áp dụng luật
            coganh.applyRules(mv.to, currentPlayer, b);
            // đổi lượt
            currentPlayer *= -1;
        }
        if (winner==-1) {
            Player2.set_win();
            return -1;
        }
        else {
            Player1.set_win();
            return 1;
        } 
        return 0;
        //b.Xuat();
    }
};
#endif
