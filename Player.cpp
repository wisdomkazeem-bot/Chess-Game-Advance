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

//TODO: Add a function to add a unit (using its pointer) to the player's vector of units 
void Player::addChess_Piece(Chess_Piece* chess_piece){
    chess_pieces.push_back(chess_piece);
}

void Player::printStatus() const{
    cout << "========Player's Chess Status========\n";
    cout << "Chess Pieces: " << chess_pieces.size() << endl;
    int totalSightPower = chess_pieces.size() * 2;
    cout << "Toal Map Sight Power: " << totalSightPower << endl;
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
