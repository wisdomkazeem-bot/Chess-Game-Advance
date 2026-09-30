#pragma once

#include "Chess_Piece.hpp"

class Chess;

class Pawn : public Chess_Piece{
    public:
        Pawn() : Chess_Piece(8) {}
        void action(int player_number, Chess& chess) override;
        string getSymbol() const override { return "P"; }
};