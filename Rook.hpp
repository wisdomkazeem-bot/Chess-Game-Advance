#pragma once

#include "Chess_Piece.hpp"
#include <iostream>
#include <string>
using namespace std;

class Chess;

class Rook : public Chess_Piece{
    private:
        int sight_range;

    public:
        Rook(int s_r = 5) : Chess_Piece(2), sight_range(s_r) {}
        void action(int player_number, Chess& chess) override;
        int getSR() { return sight_range; }
        string getSymbol() const override { return "R"; }
};