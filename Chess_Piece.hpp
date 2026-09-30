#pragma once

#include <iostream>
#include <string>
using namespace std;

class Chess;

class Chess_Piece{
    private:
        int sight_range;

    public:
        Chess_Piece(int s_r) : sight_range(s_r) {}
        virtual ~Chess_Piece() {}
        int getSR() const{
            return sight_range;
        }

        virtual void action(int player_number, Chess& chess) = 0;
        virtual string getSymbol() const = 0;
};