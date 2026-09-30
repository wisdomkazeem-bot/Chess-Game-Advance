#pragma once

#include "Chess_Piece.hpp"

class Chess;

class King : public Chess_Piece{
    private:
        int sight_range;

    public:
        King() : Chess_Piece(1), sight_range(4) {}
        void action(int player_number, Chess& chess) override;
        int getSR() const { return sight_range; }
        string getSymbol() const override { return "K"; }
};