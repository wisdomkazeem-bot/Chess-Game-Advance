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
    std::cout << "   "; // Reference from Gemini
    for (int j = 0; j < size; ++j) {
        char colLabel = 'A' + j;
        std::cout << colLabel << "  "; 
    }
    std::cout << "\n";


    for (int i = 0; i < size; ++i) {
        int rowLabel = 8 - i; 
        std::cout << rowLabel << "  ";
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
        std::cout << " " << rowLabel << "\n";;
    }
    std::cout << "   "; 
    for (int j = 0; j < size; ++j) {
        char colLabel = 'A' + j;
        std::cout << colLabel << "  "; 
    }
    std::cout << "\n\n";
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
    if (this->getMovementOption() == 2) {
        return moveChess_Piece_To_Coordinate(chess_piece, direction, playerNumber);
    }

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
        if (chess_piece->getSymbol() == "P" && steps == 2){
            int startRow = (playerNumber ==  1) ? 6 : 1;
            if (oldX != startRow){
                std::cout << "Pawns can only move 2 steps from their starting position!\n";
                return false;
            }
        }
        
        for (const auto& pair : chess_piecePositions) {
            if (pair.first != chess_piece && pair.second.first.first == newX && pair.second.first.second == newY) {
                target_piece = pair.first;
                target_player = pair.second.second;
                break;
            }
        }
        
        if (target_piece != nullptr) {
            if (target_player == playerNumber) {
                std::cout << "Can't move there: Your own piece occupies that square!\n";
                return false; 
            } else {
                if (chess_piece->getSymbol() == "P" && isDiagonalMove) {
                    if (target_piece == nullptr) {
                        std::cout << "Pawns can only move diagonally to attack an enemy!\n";
                        return false;
                    }
                }
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

bool Chess::moveChess_Piece_To_Coordinate(Chess_Piece* chess_piece, std::string coord, int playerNumber){
    auto it = chess_piecePositions.find(chess_piece);
    if (it == chess_piecePositions.end() || it->second.second != playerNumber) return false;

    auto& pos = it->second.first;
    int oldX = pos.first; 
    int oldY = pos.second;

    if (coord.length() != 2) {
        std::cout << "Invalid coordinate format! Use formats like A3 or E4.\n";
        return false;
    }

    char colChar = toupper(coord[0]);
    char rowChar = coord[1];

    int newY = colChar - 'A';
    int newX = 8 - (rowChar - '0'); 

    if (newX < 0 || newX >= size || newY < 0 || newY >= size) {
        std::cout << "Destination out of bounds!\n";
        return false; 
    }

    Chess_Piece* target_piece = nullptr;
    int target_player = 0;
    for (const auto& pair : chess_piecePositions) {
        if (pair.first != chess_piece && pair.second.first.first == newX && pair.second.first.second == newY) {
            target_piece = pair.first;
            target_player = pair.second.second;
            break;
        }
    }

    std::string symbol = chess_piece->getSymbol();

    int diffX = newX - oldX;
    int diffY = newY - oldY;
    int absX = std::abs(diffX);
    int absY = std::abs(diffY);

    if (symbol == "S") { // Knight (Springer)
        if (!((absX == 2 && absY == 1) || (absX == 1 && absY == 2))) {
            std::cout << "Knights can only move in an L-shape!\n";
            return false;
        }
    } 
    else if (symbol == "P") {
        int direction = (playerNumber == 1) ? -1 : 1;
        int startRow = (playerNumber == 1) ? 6 : 1;

        if (diffY == 0) {
            if (target_piece != nullptr) {
                std::cout << "Pawns cannot move forward into occupied squares!\n";
                return false;
            }
            if (diffX == direction) {
            } else if (oldX == startRow && diffX == 2 * direction) {
                int midX = oldX + direction;
                for (const auto& pair : chess_piecePositions) {
                    if (pair.second.first.first == midX && pair.second.first.second == oldY) {
                        std::cout << "Path is blocked!\n";
                        return false;
                    }
                }
            } else {
                std::cout << "Invalid Pawn move distance!\n";
                return false;
            }
        } else if (absY == 1 && diffX == direction) {
            if (target_piece == nullptr) {
                std::cout << "Pawns can only move diagonally to capture an opponent!\n";
                return false;
            }
        } else {
            std::cout << "Invalid Pawn move!\n";
            return false;
        }
    } 
    else if (symbol == "R" || symbol == "B" || symbol == "Q") {
        if (symbol == "R" && (diffX != 0 && diffY != 0)) {
            std::cout << "Rooks can only move horizontally or vertically!\n";
            return false;
        }
        if (symbol == "B" && (absX != absY)) {
            std::cout << "Bishops can only move diagonally!\n";
            return false;
        }
        if (symbol == "Q" && (diffX != 0 && diffY != 0 && absX != absY)) {
            std::cout << "Queens can only move in straight lines or diagonals!\n";
            return false;
        }

        int stepX = (diffX > 0) ? 1 : ((diffX < 0) ? -1 : 0);
        int stepY = (diffY > 0) ? 1 : ((diffY < 0) ? -1 : 0);

        int checkX = oldX + stepX;
        int checkY = oldY + stepY;

        while (checkX != newX || checkY != newY) {
            for (const auto& pair : chess_piecePositions) {
                if (pair.second.first.first == checkX && pair.second.first.second == checkY) {
                    std::cout << "Path is blocked by another piece!\n";
                    return false;
                }
            }
            checkX += stepX;
            checkY += stepY;
        }
    } 
    else if (symbol == "K") {
        if (absX > 1 || absY > 1) {
            std::cout << "Kings can only move 1 square in any direction!\n";
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

    pos.first = newX;
    pos.second = newY;

    return true;
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
bool Chess::isKingDefeated(int kingPlayerNum) {
    int kingX = -1, kingY = -1;

    for (const auto& pair : chess_piecePositions) {
        Chess_Piece* piece = pair.first;
        int owner = pair.second.second; 
        
        if (piece != nullptr && owner == kingPlayerNum) {
            std::string sym = piece->getSymbol();
            if (sym == "K" || sym == "k") {
                kingX = pair.second.first.first;  
                kingY = pair.second.first.second; 
                break;
            }
        }
    }

      if (kingX == -1 || kingY == -1) {
        kingX = 4; // Column E
        kingY = (kingPlayerNum == 1) ? 7 : 0; // Row 1 or 8
    }

    for (const auto& pair : chess_piecePositions) {
        Chess_Piece* enemy = pair.first;
        int owner = pair.second.second;

        if (enemy != nullptr && owner != kingPlayerNum) {
            int enemyX = pair.second.first.first;
            int enemyY = pair.second.first.second;

            int diffX = abs(kingX - enemyX);
            int diffY = abs(kingY - enemyY);
            std::string sym = enemy->getSymbol();

            bool hasPath = false;

            if ((sym == "R" || sym == "Q") && (enemyX == kingX || enemyY == kingY)) {
                hasPath = true;
                int stepX = (kingX == enemyX) ? 0 : ((kingX > enemyX) ? 1 : -1);
                int stepY = (kingY == enemyY) ? 0 : ((kingY > enemyY) ? 1 : -1);
                
                int currX = enemyX + stepX;
                int currY = enemyY + stepY;
                
                while (currX != kingX || currY != kingY) {
                    for (const auto& checkObstacle : chess_piecePositions) {
                        if (checkObstacle.second.first.first == currX && checkObstacle.second.first.second == currY) {
                            hasPath = false;
                            break;
                        }
                    }
                    if (!hasPath) break;
                    currX += stepX;
                    currY += stepY;
                }
            }

            else if ((sym == "B" || sym == "Q") && (diffX == diffY)) {
                hasPath = true;
                int stepX = (kingX > enemyX) ? 1 : -1;
                int stepY = (kingY > enemyY) ? 1 : -1;
                
                int currX = enemyX + stepX;
                int currY = enemyY + stepY;
                
                while (currX != kingX && currY != kingY) {
                    for (const auto& checkObstacle : chess_piecePositions) {
                        if (checkObstacle.second.first.first == currX && checkObstacle.second.first.second == currY) {
                            hasPath = false;
                            break;
                        }
                    }
                    if (!hasPath) break;
                    currX += stepX;
                    currY += stepY;
                }
            }

            else if ((sym == "N" || sym == "n" || sym == "S" || sym == "s") && (diffX * diffY == 2)) {
                hasPath = true;
            }

            else if ((sym == "K" || sym == "k") && (diffX <= 1 && diffY <= 1)) {
                hasPath = true;
            }

            else if (sym == "P") {
                int dir = (owner == 1) ? -1 : 1; 
                if (kingY - enemyY == dir && diffX == 1) {
                    hasPath = true;
                }
            }

            if (hasPath) return true;
        }
    }
    return false;
}

//Reference from Gemini
bool Chess::checkWinCondition(int kingPlayerNum) {
        if (!isKingDefeated(kingPlayerNum)) {
        return false;
    }

    int kingX = -1, kingY = -1;

    for (const auto& pair : chess_piecePositions) {
        Chess_Piece* piece = pair.first;
        int owner = pair.second.second; 
        if (piece != nullptr && owner == kingPlayerNum && (piece->getSymbol() == "K" || piece->getSymbol() == "k")) {
            kingX = pair.second.first.first;  
            kingY = pair.second.first.second; 
            break;
        }
    }

    if (kingX == -1 || kingY == -1) return false;

    int dx[] = {-1, -1, -1,  0, 0,  1, 1, 1};
    int dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; ++i) {
        int targetX = kingX + dx[i];
        int targetY = kingY + dy[i];

        if (targetX >= 0 && targetX < 8 && targetY >= 0 && targetY < 8) {
            bool friendlyFire = false;
            Chess_Piece* pieceAtTarget = nullptr;
            for (const auto& p : chess_piecePositions) {
                if (p.second.first.first == targetX && p.second.first.second == targetY) {
                    if (p.second.second == kingPlayerNum) friendlyFire = true;
                    else pieceAtTarget = p.first;
                    break;
                }
            }
            
            if (friendlyFire) continue;
            
            for (auto& pair : chess_piecePositions) {
                Chess_Piece* piece = pair.first;
                if (piece != nullptr && pair.second.second == kingPlayerNum && (piece->getSymbol() == "K" || piece->getSymbol() == "k")) {
                    
                    pair.second.first.first = targetX;
                    pair.second.first.second = targetY;
                    if (pieceAtTarget != nullptr) chess_piecePositions.erase(pieceAtTarget);

                    bool stillInCheck = isKingDefeated(kingPlayerNum);

                    pair.second.first.first = kingX;
                    pair.second.first.second = kingY;
                    if (pieceAtTarget != nullptr) {
                        chess_piecePositions[pieceAtTarget] = std::make_pair(std::make_pair(targetX, targetY), (kingPlayerNum == 1 ? 2 : 1));
                    }

                    if (!stillInCheck) {
                        return false; 
                    }
                    break;
                }
            }
        }
    }

    for (const auto& pair : chess_piecePositions) {
        Chess_Piece* attacker = pair.first;
        if (attacker != nullptr && pair.second.second != kingPlayerNum) {
            std::string sym = attacker->getSymbol();
            int atkX = pair.second.first.first;
            int atkY = pair.second.first.second;
            if ((sym == "Q" || sym == "R" || sym == "B") && abs(kingX - atkX) <= 1 && abs(kingY - atkY) <= 1) {
                return true; 
           }
        }
    }

    return true; 
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
    
    
