#pragma once
#include <vector>
//#include "Technology.hpp"

class Chess_Piece;
//class Building;

class Player {
private:
    //TODO: Add a vector of unit pointers
    std::vector<Chess_Piece*> chess_pieces;
    //vector of building pointers
    //std::vector<Building*> buildings;
    //vector of technologies pointers
    //std::vector<Technology*> technologies;
    //bool ranger_spawned;
    //int wood;
    

public:
    Player();
    //TODO: Declare a function to add a unit to the vector
    void addChess_Piece(Chess_Piece* chess_piece);
    //void addBuilding(Building* building);
    //void addTechnology(Technology* techonology);
    
    //bool progressTechnology();
    //bool isResearched() const;
    //bool hasRangerSpawned() const { return ranger_spawned; }
    //void setRangerSpawned() { ranger_spawned = true; }
    //Technology* getTechnology(int index) { return technologies[index]; }
    
    // Other member functions...
    void printStatus() const;
    //void printInventory() const;
    //int getWood() const;
    void removeChess_Piece(Chess_Piece* chess_piece);
    
    const std::vector<Chess_Piece*>& getChess_Pieces() const { return chess_pieces; }
    //const std::vector<Building*>& getBuildings() const { return buildings; }
};