#include "Chess_Piece.hpp"
#include "Chess.hpp"
#include "Board_White.hpp"
#include "Board_Black.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <chrono>
#include <thread>

Chess::Chess() : grid(size, std::vector<Board*>(size, nullptr)) {
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if ((i + j) % 2 == 0){
                grid[i][j] = new Board_Black();
            } else {
                grid[i][j]= new Board_White();
            }
        }
    }
}

Chess::~Chess() {
    for (auto& row : grid) {
        for (auto* cell : row) {
            delete cell;
        }
    }
}

void Chess::displayMap(std::string whiteSquareColor, std::string blackSquareColor) const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            bool found = false;
            
            //TODO: Uncomment the code below when you have implemented Units
            for (const auto& pair : chess_piecePositions) {
                if (pair.second.first.first == i && pair.second.first.second == j) {
                    std::cout << pair.first->getSymbol() << pair.second.second << " "; // Display player number
                    found = true;
                    break;
                }
            }
            
            //Wooden Board
            //*Note Add an options feature
            std::string Reset_Color = "\033[0m";
            if (!found){
                Board* current_types = grid[i][j];
                if (current_types != nullptr){
                    if (current_types->getType() == "White"){
                        std::cout << whiteSquareColor << ".. " << Reset_Color;
                    } else if (current_types->getType() == "Black"){
                        std::cout << blackSquareColor << "~~ " << Reset_Color;
                    }
                }
            }
        }
        std::cout << "\n";
    }
}

//TODO: Uncomment all the code below code once Unit is implemented
void Chess::placeChess_Piece(Chess_Piece* chess_piece, int playerNumber) {
    int x = 0;
    int y = 0;

    if (playerNumber == 1){
        if (chess_piece->getSymbol() == "P"){
            x = 6;
        } else {
            x = 7;
        }
    }
    else if (playerNumber == 2){
        if (chess_piece->getSymbol() == "P"){
            x = 1;
        } else {
            x = 0;
        }
    }

    std::string other_piece = chess_piece->getSymbol();
    
    if (other_piece == "P"){
        for (int i = 0; i < size; i++){
            if (!isPositionOccupied(x, i)){
                y = i;
                break;
            }
        }
    } else if (other_piece == "R"){
        if (!(isPositionOccupied(x,0))){
            y = 0;
        } else {
            y = 7;
        }
    } else if (other_piece == "S"){
        if (!(isPositionOccupied(x, 1))){
            y = 1;
        } else {
            y = 6;
        }
    } else if (other_piece == "B"){
        if (!(isPositionOccupied(x, 2))){
            y = 2;
        } else {
            y = 5;
        }
    } else if (other_piece == "Q"){
        if (!(isPositionOccupied(x, 3))){
            y = 3;
        }
    } else if (other_piece == "K"){
        if (!(isPositionOccupied(x, 4))){
            y = 4;
        }
    }
    chess_piecePositions[chess_piece] = {{x, y}, playerNumber};
}

bool Chess::moveChess_Piece(Chess_Piece* chess_piece, const std::string& direction, int playerNumber) {
    auto it = chess_piecePositions.find(chess_piece);
    if (it == chess_piecePositions.end() || it->second.second != playerNumber) return false;

    Chess_Piece* target_piece = nullptr;
    int target_player = 0;

    bool isDiagonalMove = false;

    auto& pos = it->second.first;
    int oldX = pos.first;
    int oldY = pos.second;
    int newX = oldX;
    int newY = oldY;

    int steps = current_move_steps;
    
    if (direction == "N") newX -= steps;
    else if (direction == "S") newX += steps;
    else if (direction == "E") newY += steps;
    else if (direction == "W") newY -= steps;
    else if (direction == "NE") {newX -= steps; newY += steps; isDiagonalMove = true;}
    else if (direction == "SE") {newX += steps; newY += steps; isDiagonalMove = true;}
    else if (direction == "SW") {newX += steps; newY -= steps; isDiagonalMove = true;}
    else if (direction == "NW") {newX -= steps; newY -=steps; isDiagonalMove = true;} 

    //Knights own move sets (Reference from Gemini)
    else if (direction == "NNE") { newX -= 2; newY += 1; } 
    else if (direction == "NNW") { newX -= 2; newY -= 1; } 
    else if (direction == "SSE") { newX += 2; newY += 1; } 
    else if (direction == "SSW") { newX += 2; newY -= 1; } 
    else if (direction == "EEN") { newX -= 1; newY += 2; } 
    else if (direction == "EES") { newX += 1; newY += 2; } 
    else if (direction == "WWN") { newX -= 1; newY -= 2; } 
    else if (direction == "WWS") { newX += 1; newY -= 2; } 

    else { return false; } 

    if (newX >= 0 && newX < size && newY >= 0 && newY < size /*&& !isPositionOccupied(newX, newY)*/) {
        for (const auto& pair : chess_piecePositions) {
            if (pair.first != chess_piece && pair.second.first.first == newX && pair.second.first.second == newY) {
                target_piece = pair.first;
                target_player = pair.second.second;
                break;
            }
        }

        if (chess_piece->getSymbol() == "P" && isDiagonalMove) {
            if (target_piece == nullptr) {
                std::cout << "Pawns can only move diagonally to attack an enemy!\n";
                return false;
            }
        }
        
        if (target_piece != nullptr) {
            if (target_player == playerNumber) {
                std::cout << "Can't move there: Your own piece occupies that square!\n";
                return false; 
            } else {
                clearChess_Piece(chess_piece, target_piece); 
            }
        }

        //Reference from Gemini
        if (chess_piece->getSymbol() != "S") {
                int firstStepX = oldX + ((newX > oldX) ? 1 : ((newX < oldX) ? -1 : 0));
                int firstStepY = oldY + ((newY > oldY) ? 1 : ((newY < oldY) ? -1 : 0));
            for (const auto& pair : chess_piecePositions) {
                if (pair.second.first.first == firstStepX && pair.second.first.second == firstStepY) {
                    if (steps > 1) {
                        std::cout << "Only Knights can jump over pieces! Path is blocked.\n";
                        return false;
                    }
                }
            }
        }

        pos.first = newX;
        pos.second = newY;
        return true;
    }
    return false;
}

void Chess::displayMapWithSight(int playerNumber, int sight, Chess_Piece* chess_piece) const {
    auto chess_piecePos = chess_piecePositions.find(chess_piece);
    if (chess_piecePos == chess_piecePositions.end()) return;

    int chess_pieceX = chess_piecePos->second.first.first, chess_pieceY = chess_piecePos->second.first.second;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (std::abs(i - chess_pieceX) <= sight && std::abs(j - chess_pieceY) <= sight) {
                if (chess_pieceX == i && chess_pieceY == j) {
                    std::cout << "C"; // Current unit position
                } else if (isPositionOccupied(i, j)) {
                    std::cout << "X"; // Other units
                } else {
                    std::cout << "."; // Visible terrain
                }
            } else {
                std::cout << " "; // Out of sight
            }
        }
        std::cout << "\n";
    }
}

bool Chess::isPositionOccupied(int x, int y) const{
    for (const auto& pair : chess_piecePositions) {
        if (pair.second.first.first == x && pair.second.first.second == y) {
            return true;
        }
    }
    return false;
}

std::string Chess::getBoardType(Chess_Piece* chess_piece) const {
    auto it = chess_piecePositions.find(chess_piece);
    if (it == chess_piecePositions.end()){
        return "";
    }
    int x = it->second.first.first;
    int y = it->second.first.second;
    return grid[x][y]->getType();
}

//Reference Function from Gemini
void Chess::clearChess_Piece(Chess_Piece* moving_piece, Chess_Piece* target_piece) {
    if (moving_piece == nullptr || target_piece == nullptr) return;

    auto moveIt = chess_piecePositions.find(moving_piece);
    auto targetIt = chess_piecePositions.find(target_piece);

    int moving_player = moveIt->second.second;
    int target_player = targetIt->second.second;

    if ((moving_player == 1 && target_player == 2) || (moving_player == 2 && target_player == 1)) {
        std::cout << target_piece->getSymbol() << " has been removed from the board.\n";
        chess_piecePositions.erase(target_piece);
    }
}

std::string Chess::getNextBoard(Chess_Piece* chess_piece, const std::string& direction) const {
    auto it = chess_piecePositions.find(chess_piece);
    if (it == chess_piecePositions.end()) return "";
    int x = it->second.first.first;
    int y = it->second.first.second;
    if (direction == "N") x--;
    else if (direction == "S") x++;
    else if (direction == "E") y++;
    else if (direction == "W") y--;
    else if (direction == "NE") {x--; y++;}
    else if (direction == "SE") {x++; y++;}
    else if (direction == "SW") {x++; y--;}
    else if (direction == "NW") {x--; y--;}
    else { return ""; } 
    if (x < 0 || x >= size || y < 0 || y >= size) return "";
    return grid[x][y]->getType();
}

//Reference from Gemini
bool Chess::isKingDefeated(const std::vector<Chess_Piece*>& activePieces) {
    bool kingFound = false;
    
    for (size_t i = 0; i < activePieces.size(); ++i) {
        if (activePieces[i] != nullptr) {
            std::string sym = activePieces[i]->getSymbol();
            // Checks for both uppercase "K" or lowercase "k" 
            if (sym == "K" || sym == "k") {
                if (chess_piecePositions.find(activePieces[i]) != chess_piecePositions.end()){
                    kingFound = true;
                    break;
                }
            }
        }
    }

    return !kingFound; 
}

//Reference from Gemini
bool Chess::checkWinCondition() {
    int playerOneKings = 0;
    int playerTwoKings = 0;

    for (const auto& pair : chess_piecePositions) {
        Chess_Piece* piece = pair.first;
        int owner = pair.second.second;
        
        if (piece != nullptr && (piece->getSymbol() == "K" || piece->getSymbol() == "k")) {
            if (owner == 1) playerOneKings++;
            if (owner == 2) playerTwoKings++;
        }
    }

    // Return true if either king is dead so your outer statement fires
    if (playerOneKings == 0 || playerTwoKings == 0) {
        return true;
    }
    return false;
}

int Chess::timePlayer(int playerNumber, int maxTime, bool isTime){
    if (!isTime || maxTime <= 0){
        return maxTime;
    }

    int timer = maxTime;

    while (timer >= 0) {
        std::cout << "\rPlayer " << playerNumber << " Timer: " << timer << "s " << std::flush;

        if (timer == 0) {
            return 0;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
        timer--;
    }
    return timer;
}
    
    
