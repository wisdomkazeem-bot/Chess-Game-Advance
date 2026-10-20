#pragma once

#include "Board.hpp"
#include "Chess_Piece.hpp"
#include "Pawn.hpp"
#include "Board_White.hpp"
#include "Board_Black.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
using namespace std;

class Chess{
    private:
        static const int size = 8; // Adjust size for demonstration
        int movement_option = 1;
        vector<std::vector<Board*>> grid;
        unordered_map<Chess_Piece*, std::pair<std::pair<int, int>, int>> chess_piecePositions; // Unit to position and player mapping

    public:
        int current_move_steps = 1;
        Chess();
        ~Chess();
        void displayMap(std::string whiteSquareColor, std::string blackSquareColor) const; 
        void placeChess_Piece(Chess_Piece* chess_piece, int playerNumber);
        bool moveChess_Piece(Chess_Piece* chess_piece, const string& direction, int playerNumber);
        bool moveChess_Piece_To_Coordinate(Chess_Piece* chess_piece, string coord, int playerNumber);
        void displayMapWithSight(int playerNumber, int sight, Chess_Piece* chess_piece) const;
        bool isPositionOccupied(int x, int y) const;
        std::string getBoardType(Chess_Piece* chess_piece) const;
        void clearChess_Piece(Chess_Piece* moving_piece, Chess_Piece* target_piece);
        std::string getNextBoard(Chess_Piece* chess_piece, const string& direction) const;
        bool isKingDefeated(int kingPlayerNum);
        bool checkWinCondition(int kingPlayerNum);
        int timePlayer(int playerNumber, int maxTime, bool isTime);
        void setMovementOption(int m_o) { movement_option = m_o; }
        int getMovementOption() const { return movement_option; }
};