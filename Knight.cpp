#include "Knight.hpp"
#include "Chess.hpp"
#include <iostream>
#include <string>
using namespace std;

void Knight::action(int player_number, Chess& chess){
    cout << "======Sight Map======\n";
    chess.displayMapWithSight(player_number, getSR(), this);
    cout << "\n ---- Player " << player_number << "'s Turn (Knight)\n";
    cout << "Move(NNE, NNW, SSE, SSW, EEN, EES, WWN, WWS): ";
    string choice;
    getline(cin, choice);

    if (choice == "nne" || choice == "NNE") choice = "NNE";
    else if (choice == "nnw" || choice == "NNW") choice == "NNW";
    else if (choice == "sse" || choice == "SSE") choice = "SSE";
    else if (choice == "ssw" || choice == "SSW") choice = "SSW";
    else if (choice == "een" || choice == "EEN") choice = "EEN";
    else if (choice == "ees" || choice == "EES") choice = "EES";
    else if (choice == "wwn" || choice == "WWN") choice = "WWN";
    else if (choice == "wws" || choice == "WWS") choice = "WWS";
    else{
        cout << "Invaild direction entered!\n";
        sight_range = 8;
        return;
    }

    bool move = chess.moveChess_Piece(this, choice, player_number);
    if (!move){
        cout << "Can't move there\n";
    }
}