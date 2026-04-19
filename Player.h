#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string.h>
#include <iostream>
#include "Common.h"
#include "Board.h"
class Player {
    int id;
    int win=0;
    public:
    void set_Player_id (int _id) {
        id=_id;
    }
    void set_win (){
        win++;
    }
    int get_win() {
        return win;
    }
    Move PlayerMove(int player,Board b){
        std::vector<Position> moves;
        std::vector<Move> AvailableMoves;
        int dx[4]={1,0,1,1};
        int dy[4]={0,1,1,-1};
        int opp = (player == 1 ? -1 : 1);
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                if(b.get_Board({i,j}) != player) continue;
                moves = b.getMoves({i,j});
                for(int k=0; k<moves.size(); k++){
                    Position m = moves[k];
                    int x = m.x, y = m.y;
                    AvailableMoves.push_back({{i,j},{x,y}});
                }
            }
        }
        if (AvailableMoves.empty()) {
            return {-1, -1, -1, -1}; 
        }
        Move mv = AvailableMoves[rand()%AvailableMoves.size()];
        return mv;
    }
};

#endif