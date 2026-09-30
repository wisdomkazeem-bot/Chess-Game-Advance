#include "Player.hpp"
#include "Chess_Piece.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

Player::Player() {
    // Initialize any resources or member variables here, if necessary
    //wood = 0;
}

void Player::printStatus() const{
    cout << "========Player's Chess Status========\n";
    cout << "Chess Pieces: " << chess_pieces.size() << endl;
    //Reference from Gemini, for missing pieces and material delta.
    int missingPieces = 16 - static_cast<int>(chess_pieces.size()); 
    if (missingPieces < 0) missingPieces = 0;
    cout << "Missing Chess Pieces: " << missingPieces << endl;

    int materialScore = 0;
    for (size_t i = 0; i < chess_pieces.size(); ++i) {
        if (chess_pieces[i] != nullptr) {
            std::string sym = chess_pieces[i]->getSymbol();
            if (sym == "P")      materialScore += 1;
            else if (sym == "R") materialScore += 5;
            else if (sym == "S") materialScore += 3; // 'S' for Knight
            else if (sym == "B") materialScore += 3;
            else if (sym == "Q") materialScore += 9;
        }
    }

    int materialDelta = 39 - materialScore;
    std::cout << "Match Advantage: ";
    if (materialDelta > 0) {
        std::cout << "+" << materialDelta << " (Winning Trade Battle)\n";
    } else if (materialDelta < 0) {
        std::cout << materialDelta << " (Trailing Trade Battle)\n";
    } else {
        std::cout << "0 (Perfectly Even)\n";
    }
    cout << "=====================================\n";
}

void Player::removeChess_Piece(Chess_Piece* chess_piece){
    if (chess_piece == nullptr) return;
    auto it = std::find(chess_pieces.begin(), chess_pieces.end(), chess_piece);

    if (it != chess_pieces.end()) {
        chess_pieces.erase(it);
        delete chess_piece; 
    }
}

//TODO: Add a function to add a unit (using its pointer) to the player's vector of units 
void Player::addChess_Piece(Chess_Piece* chess_piece){
    chess_pieces.push_back(chess_piece);
}