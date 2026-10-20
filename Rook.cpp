#include "Rook.hpp"
#include "Chess.hpp"
#include <iostream>
#include <string>

void Rook::action(int playerNumber, Chess& chess) {
    cout << "======Sight Map======\n";
    chess.displayMapWithSight(playerNumber, getSR(), this);
    std::cout << "\n--- Player " << playerNumber << "'s Turn (Rook) ---\n";
    
    std::string choice;
    if (chess.getMovementOption() == 1){
        std::cout << "Move(N,S,E,W): ";
        std::cin >> choice;
        std::cin.ignore();
    } else {
        std::cout << "Enter a Target Coordinate (e.g B3, P1): ";
        std::cin >> choice;
    }
    
    
    


    if      (choice == "n" || choice == "N") choice = "N";
    else if (choice == "s" || choice == "S") choice = "S";
    else if (choice == "e" || choice == "E") choice = "E";
    else if (choice == "w" || choice == "W") choice = "W";

    bool moved = chess.moveChess_Piece(this, choice, playerNumber);
    if (!moved) {
        std::cout << "Can't move there!\n";
    }
}