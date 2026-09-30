#pragma once

#include <iostream>
#include <string>

class Board{
    public:
        virtual ~Board() {}
        virtual std::string getType() const = 0;
};