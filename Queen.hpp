#pragma once

#include "Chess_Piece.hpp"

class Chess;

class Queen : public Chess_Piece{
    private:
        int sight_range;

    public:
        Queen(int s_r = 8) : Chess_Piece(1), sight_range(s_r) {}
        void action(int player_number, Chess& chess) override;
        int getSR() { return sight_range; }
        string getSymbol() const override { return "Q"; }
};