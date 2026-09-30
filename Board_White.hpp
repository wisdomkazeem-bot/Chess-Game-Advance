#pragma once

#include "Board.hpp"
#include <iostream>
#include <string>
using namespace std;

class Board_White : public Board{
    public:
        string getType() const override { return "White"; }
};