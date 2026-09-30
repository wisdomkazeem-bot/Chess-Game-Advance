#include "Bishop.hpp"
#include "Chess.hpp"
#include <iostream>
#include <string>
using namespace std;

void Bishop::action(int player_number, Chess& chess){
    cout << "======Sight Map======\n";
    chess.displayMapWithSight(player_number, getSR(), this);

    cout << "\n---- Player's " << player_number << "'s Turn (Bishop)----\n";
    cout << "Move(NE, ES, SW, WN): ";
    string choice;
    getline(cin, choice);

    if (choice == "ne" || choice == "NE" || choice == "EN" || choice == "en") choice = "NE";
    else if (choice == "es" || choice == "ES" || choice == "se" || choice == "SE") choice = "ES";
    else if (choice == "sw" || choice == "SW" || choice == "ws" || choice == "WS") choice = "SW";
    else if (choice == "wn" || choice == "WN" || choice == "NW" || choice == "nw") choice = "WN";
    else {
        cout << "Invalid direction entered!\n";
        sight_range = 6;
        return;
    }

    bool move = chess.moveChess_Piece(this, choice, player_number);
    if (!move){
        cout << "Can't move there!\n";
    }
}