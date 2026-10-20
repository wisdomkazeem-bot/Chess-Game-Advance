#pragma once

#include "Chess_Piece.hpp"

class Chess;

class Pawn : public Chess_Piece{
    private:
        int sight_range;

    public:
        Pawn() : Chess_Piece(8), sight_range(3) {}
        void action(int player_number, Chess& chess) override;
        int getSR() const { return sight_range; }
        string getSymbol() const override { return "P"; }
};