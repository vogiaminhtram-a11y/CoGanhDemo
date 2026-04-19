#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "Player.h"
using namespace std;
int main() {
    Player Player1, Player2;
    Player1.set_Player_id(1); 
    Player2.set_Player_id(-1);
    int draw=0;
    const int soVan = 200;
    Statistics Player1_Stat, Player2_Stat;
    srand(time(NULL));
    for(int van = 1; van <= soVan; van++){
        Game game;
        game.set_up();
        int win=game.process(Player1, Player2, draw, Player1_Stat, Player2_Stat);
        cout << "Van " << van << ": ";
        if(win == 0) cout << "Hoa";
        else if(win == 1) cout << "Player 1 thang";
        else cout << "Player 2 thang";
        cout << endl;
    }
    cout << "\n=========== KET QUA SAU " << soVan << " VAN ===========\n";
    cout << "Player 1 thang: " << Player1.get_win() << endl;
    cout << "Player 2 thang: " << Player2.get_win() << endl;
    cout << "Hoa       : " << draw << endl;

    cout << "\n================ KET QUA MO PHONG ================\n";
    cout << "Tong so van: " << soVan << '\n';
    cout << "Player 1 thang: " << Player1.get_win() << " ("
         << fixed << setprecision(2) << 100.0 * Player1.get_win() / soVan << "%)\n";
    cout << "Player 2 thang: " << Player2.get_win()  << " ("
         << fixed << setprecision(2) << 100.0 * Player2.get_win() / soVan << "%)\n";
    cout << "Hoa        : " << draw << " ("
         << fixed << setprecision(2) << 100.0 * draw / soVan << "%)\n";

    Player1_Stat.In_Bang_Thong_Ke(1);
    Player1_Stat.In_Chi_Tiet_Thong_Ke(1);
    Player1_Stat.In_Top_O(1);

    Player2_Stat.In_Bang_Thong_Ke(-1);
    Player2_Stat.In_Chi_Tiet_Thong_Ke(-1);
    Player2_Stat.In_Top_O(-1);
}