#include "Queen.hpp"
#include "Chess_Piece.hpp"
#include "Chess.hpp"
#include <iostream>
#include <string>
using namespace std;

void Queen::action(int player_number, Chess& chess){
    cout << "======Sight Map======\n";
    chess.displayMapWithSight(player_number, getSR(), this);
    cout << "\n---- Player " << player_number << "'s Turn (Queen) ----\n";
    
    string choice;
    if (chess.getMovementOption() == 1){
        cout << "Move(N,E,S,W,NE,SE,SW,NW): ";
        cin >> choice;
        cin.ignore();
        if (choice == "n" || choice == "N") choice = "N";
        else if (choice == "e" || choice == "E") choice = "E";
        else if (choice == "s" || choice == "S") choice = "S";
        else if (choice == "w" || choice == "W") choice = "W";
        else if(choice == "ne" || choice == "NE" || choice == "EN" || choice == "en") choice = "NE";
        else if (choice == "es" || choice == "ES" || choice == "se" || choice == "SE") choice = "SE";
        else if (choice == "sw" || choice == "SW" || choice == "ws" || choice == "WS") choice = "SW";
        else if (choice == "wn" || choice == "WN" || choice == "NW" || choice == "nw") choice = "NW";
    } else {
        cout << "Enter a Target Coordinate (e.g B3, P1): ";
        cin >> choice;
    }

    bool move = chess.moveChess_Piece(this, choice, player_number);
    if (!move){
        cout << "Can't move there!\n";
    }
}