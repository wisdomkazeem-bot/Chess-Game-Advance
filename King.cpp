#include "King.hpp"
#include "Chess.hpp"
#include <iostream>
#include <string>
using namespace std;

void King::action(int player_number, Chess& chess){
    cout << "======Sight Map======\n";
    chess.displayMapWithSight(player_number, getSR(), this);
    cout << "\n ---- Player " << player_number << "'s Turn (King)\n";
    cout << "Move(N,E,S,W,NE,SE,SW,NW): ";
    string choice;
    cin >> choice;

    if (choice == "n" || choice == "N") choice = "N";
    else if (choice == "s" || choice == "S") choice = "S";
    else if (choice == "e" || choice == "E") choice = "E";
    else if (choice == "w" || choice == "W") choice = "W";
    else if (choice == "ne" || choice == "NE" || choice == "EN" || choice == "en") choice = "NE";
    else if (choice == "es" || choice == "ES" || choice == "se" || choice == "SE") choice = "SE";
    else if (choice == "sw" || choice == "SW" || choice == "ws" || choice == "WS") choice = "SW";
    else if (choice == "wn" || choice == "WN" || choice == "NW" || choice == "nw") choice = "NW";
    else{
        cout << "Invaild direction entered!\n";
        sight_range = 4;
        return;
    }

    bool move = chess.moveChess_Piece(this, choice, player_number);
    if (!move){
        cout << "Can't move there\n";
    }
}