#include "Pawn.hpp"
#include "Chess_Piece.hpp"
#include "Chess.hpp"
#include <iostream>
#include <string>
using namespace std;

void Pawn::action(int player_number, Chess& chess){
    cout << "======Sight Map======\n";
    chess.displayMapWithSight(player_number, getSR(), this);
    string choice;
    cout << "\n---- Player " << player_number << "'s Turn (Pawn) ----\n";
    if (player_number == 1){
        cout << "Move(N,NE,NW(if you can attack a piece diagonally for NE or WN)): ";    
        cin >> choice;
    }

    if (player_number == 2){
        cout << "Move(S, SE, SW(if you can attack a piece diagonally for SE or SW)): ";
        cin >> choice;
    }

    if (choice == "n" || choice == "N") choice = "N";
    else if (choice == "s" || choice == "S") choice = "S";
    else if (choice == "ne" || choice == "NE" || choice == "EN" || choice == "en") choice = "NE";
    else if (choice == "es" || choice == "ES" || choice == "se" || choice == "SE") choice = "SE";
    else if (choice == "sw" || choice == "SW" || choice == "ws" || choice == "WS") choice = "SW";
    else if (choice == "wn" || choice == "WN" || choice == "NW" || choice == "nw") choice = "NW";

    bool move = chess.moveChess_Piece(this, choice, player_number);
    if (!move){
        cout << "Can't move there (if a chess piece is in front of you)\n";
    }
}