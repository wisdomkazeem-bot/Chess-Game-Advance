#pragma once

#include "Chess_Piece.hpp"

class Chess;

class Knight : public Chess_Piece{
    private:
        int sight_range;

    public:
        Knight() : Chess_Piece(2), sight_range(8) {}
        void action(int player_number, Chess& chess) override;
        int getSR() const { return sight_range; }
        string getSymbol() const override { return "S"; }
};