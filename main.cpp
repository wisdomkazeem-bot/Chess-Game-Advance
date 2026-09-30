#include "Chess.hpp"
#include "Player.hpp"
#include "Board_Black.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>
#include <ctime>
#include <thread>
#include <chrono>

//Wisdom Kazeem
//Ontario Tech University
//Started: September 20th, 2026

//Reminder add colour for the board and the chess piece.
//2D array and in each value, that never change. Character array, Direction (like B3, C4), Add possible position.
//CPU: Unlock patters
int main() {
    Chess chess;
    int numberOfPlayers = 2;
    std::vector<Player> players;
    
    //Default Colors
    std::string dynamicWhite = "\033[33m";
    std::string dynamicBlack = "\033[38;2;222;184;135m";

    //Default Time
    int time = 0;

    // Initialize players and their scouts
    for (int i = 0; i < numberOfPlayers; ++i) {
        Player player;
        players.push_back(player);
    }

    //Reference from Gemini
    int p1 = 1;
    for (int i = 0; i < 8; i++) { Pawn* p = new Pawn(); players[0].addChess_Piece(p); chess.placeChess_Piece(p, p1); }
    for (int i = 0; i < 2; i++) { Rook* r = new Rook(); players[0].addChess_Piece(r); chess.placeChess_Piece(r, p1); }
    for (int i = 0; i < 2; i++) { Knight* k = new Knight(); players[0].addChess_Piece(k); chess.placeChess_Piece(k, p1); }
    for (int i = 0; i < 2; i++) { Bishop* b = new Bishop(); players[0].addChess_Piece(b); chess.placeChess_Piece(b, p1); }
    King* k1 = new King(); players[0].addChess_Piece(k1); chess.placeChess_Piece(k1, p1);
    Queen* q1 = new Queen(); players[0].addChess_Piece(q1); chess.placeChess_Piece(q1, p1);

    int p2 = 2;
    for (int i = 0; i < 8; i++) { Pawn* p = new Pawn(); players[1].addChess_Piece(p); chess.placeChess_Piece(p, p2); }
    for (int i = 0; i < 2; i++) { Rook* r = new Rook(); players[1].addChess_Piece(r); chess.placeChess_Piece(r, p2); }
    for (int i = 0; i < 2; i++) { Knight* k = new Knight(); players[1].addChess_Piece(k); chess.placeChess_Piece(k, p2); }
    for (int i = 0; i < 2; i++) { Bishop* b = new Bishop(); players[1].addChess_Piece(b); chess.placeChess_Piece(b, p2); }
    King* k2 = new King(); players[1].addChess_Piece(k2); chess.placeChess_Piece(k2, p2);
    Queen* q2 = new Queen(); players[1].addChess_Piece(q2); chess.placeChess_Piece(q2, p2);

    int choice;
    bool restarting;
    bool to_case = false;
    bool isTimer = false;

    do{
        //Title Logo Reference by Gemini
        std::cout << "██████╗██╗  ██╗███████╗███████╗███████╗    ██████╗  █████╗ ███╗   ███╗███████╗\n";
        std::cout << "██╔════╝██║  ██║██╔════╝██╔════╝██╔════╝    ██╔════╝ ██╔══██╗████╗ ████║██╔════╝\n";
        std::cout << "██║     ███████║█████╗  ███████╗███████╗    ██║  ███╗███████║██╔████╔██║█████╗  \n";
        std::cout << "██║     ██╔══██║██╔══╝  ╚════██║╚════██║    ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  \n";
        std::cout << "╚██████╗██║  ██║███████╗███████║███████║    ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗\n";
        std::cout << " ╚═════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝     ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝\n";
        std::cout << "                                                                                \n";
        std::cout << "                █████╗ ██████╗ ██╗   ██╗ █████╗ ███╗   ██╗ ██████╗███████╗      \n";
        std::cout << "               ██╔══██╗██╔══██╗██║   ██║██╔══██╗████╗  ██║██╔════╝██╔════╝      \n";
        std::cout << "               ███████║██║  ██║██║   ██║███████║██╔██╗ ██║██║     █████╗        \n";
        std::cout << "               ██╔══██║██║  ██║╚██╗ ██╔╝██╔══██║██║╚██╗██║██║     ██╔══╝        \n";
        std::cout << "               ██║  ██║██████╔╝ ╚████╔╝ ██║  ██║██║ ╚████║╚██████╗███████╗      \n";
        std::cout << "               ╚═╝  ╚═╝╚═════╝   ╚═══╝  ╚═╝  ╚═╝╚═╝  ╚═══╝ ╚═════╝╚══════╝      \n\n";
        std::cout << "2 Player Chess Game (1):\n";
        std::cout << "Chess Pieces Description (2):\n";
        std::cout << "Chess Game Instruction (3):\n";
        std::cout << "Options (4):\n";
        std::cout << "Exiting the Game (5):\n";
        std::cout << "Enter Choice: ";
        restarting = false;
        
        //Reference by Gemini for IF Statement
        if (to_case){
            choice = 4;
            to_case = false;
        } else {
            choice = 0;
            cin >> choice;
        }

        switch (choice){
            case 1:{
                // Main game loop
                int turnCount = 0;
                char userChoice = 'n'; // Default choice to start the game
                int player1Clock = time;
                int player2Clock = time;

                while (userChoice != 'y') {
                    for (int i = 0; i < numberOfPlayers; ++i) {
                        turnCount++;
                        
                        Player& currentPlayer = players[i]; 
                        int playerNumber = i + 1;
                        
                        auto starttime = std::chrono::steady_clock::now();

                        int currentPool = (playerNumber == 1) ? player1Clock : player2Clock;

                        chess.displayMap(dynamicWhite, dynamicBlack);
                        std::cout << "\n--- Player " << playerNumber << "'s Turn ---\n";
                        
                        int leftoverTime = chess.timePlayer(currentPool, playerNumber, isTimer);

                        if (isTimer) {
                            std::cout << "Time Remaining:" <<leftoverTime << std::endl;
                        }

                        currentPlayer.printStatus();
                        //currentPlayer.printInventory();
            
                        //int research_cost = 10;
            
                        // std::string decision;
                        // std::cout << "Do you want to research? (y/n): ";
                        // std::cin >> decision;

                        // if (decision == "Y" || decision == "y") {
                        //     if(research_cost <= players[i].getWood()){
                        //         Technology* tech = currentPlayer.getTechnology(0);
                        //         if (!tech->isResearched()) {
                        //             currentPlayer.removeWood(research_cost);
                        //             std::cout << "Researching " << tech->getName()
                        //                       << "... " << tech->getTurnsLeft() << " turns left.\n";
                        //             currentPlayer.progressTechnology();
                        //         } else if (!currentPlayer.hasRangerSpawned()) {
                        //             std::cout << "Advanced Scout researched! Ranger unlocked!\n";
                        //             Ranger* ranger = new Ranger();
                        //             currentPlayer.addUnit(ranger);
                        //             world.placeUnitRandomly(ranger, playerNumber);
                        //             currentPlayer.setRangerSpawned();
                        //         } else {
                        //             std::cout << "Already fully researched!\n";
                        //         }
                        //     } else {
                        //         std::cout<< "You do not have enough wood to research (Costs 10 Wood)\n"; 
                        //     }
                        // } else {
                        //     std::cout << "Skipping research.\n";
                        // }
            
                        const std::vector<Chess_Piece*> playerChess_Piece = currentPlayer.getChess_Pieces();
                        std::cout << "Avalilable Piece to Moves:\n";
                        for (size_t i = 0; i < playerChess_Piece.size(); i++){
                            if (playerChess_Piece[i] != nullptr) {
                                std::cout << i << ": " << playerChess_Piece[i]->getSymbol() << "  ";
                                if ((i + 1) % 4 == 0) std::cout << "\n";
                            }
                        }

                        int selection;
                        std::cout << "\n\nEnter the number of the piece you want to move: ";
                        
                        //Reference from Gemini for this if statement
                        if (!(std::cin >> selection)) {
                            std::cin.clear();
                            std::cin.ignore();
                            try {
                                throw std::runtime_error("Invalid selection! Please enter a number instead of letters. Next Players.\n");
                            } catch (const std::runtime_error& e) {
                                std::cerr << "ERROR - " << e.what() << std::endl;
                            }
                            continue;
                        }
    
                        if (selection >= 0 && selection < static_cast<int>(playerChess_Piece.size())) {
                            std::string symbol = playerChess_Piece[selection]->getSymbol();

                            //Reference by Gemini
                            int steps;
                            if (symbol == "R" || symbol == "Q" || symbol == "B"){
                                std::cout << "How Many Steps: ";
                                std::cin >> steps;
                                std::cin.ignore();
                                chess.current_move_steps = steps;
                            } else {
                                chess.current_move_steps = 1;
                            }

                            playerChess_Piece[selection]->action(playerNumber, chess);
                        }

                        // if (turnCount % 3 == 0) {
                        //     Scout* newScout = world.spawnBarrack(playerNumber);
                        //     if (newScout != nullptr) {
                        //         currentPlayer.addUnit(newScout);
                        //         std::cout << "Player " << playerNumber << "'s Barracks spawned a new Scout!\n";
                        //     }
                        // }

                        auto endtime = std::chrono::steady_clock::now();
                        int secondsTaken = std::chrono::duration_cast<std::chrono::seconds>(endtime - starttime).count();
                        leftoverTime = currentPool - secondsTaken;

                        bool gameOver = false;
                        while (!gameOver){
                            for (size_t i = 0; i < players.size(); ++i) {
                                Player& player = players[i];

                                const std::vector<Chess_Piece*> playerChess_Piece = player.getChess_Pieces();

                                if (chess.isKingDefeated(playerChess_Piece)){
                                    if (chess.checkWinCondition()) {
                                        std::cout << "=========================================\n";
                                        int winningPlayerNumber = (i == 0) ? 2 : 1;
                                        std::cout << "PLAYER " << winningPlayerNumber << " Wins!\n";
                                        std::cout << "=========================================\n";
                                    }
                                    gameOver = true;
                                    chess.displayMap(dynamicWhite, dynamicBlack);
                                    // Ask the user if they want to continue or quit the game
                                    std::cout << "Do you want to quit the game? (y/n): ";
                                    std::cin >> userChoice;
                                    if(userChoice == 'y' || userChoice == 'Y') {
                                        break; // Exit the game loop
                                    }
                                } else {
                                    if (isTimer) {
                                        int currentPool = (playerNumber == 1) ? player1Clock : player2Clock;
                                        leftoverTime = chess.timePlayer(playerNumber, currentPool, isTimer);

                                        if (leftoverTime <= 0) {
                                            int winningPlayerNumber = (playerNumber == 1) ? 2 : 1;
                                            std::cout << "\n========================================\n";
                                            std::cout << "Player " << playerNumber << " ran out of time!\n";
                                            std::cout << "Player " << winningPlayerNumber << " Wins!\n";
                                            std::cout << "========================================\n";
                                            
                                            userChoice = 'y';
                                            gameOver = true;
                                            break;
                                        } else {
                                            if (playerNumber == 1) player1Clock = leftoverTime;
                                            else player2Clock = leftoverTime;
                                        }
                                    }

                                    gameOver = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                restarting = true;
                break;
            }
            case 2: {//Descripition for the chess piece
                int x;
                std::string exit_choice;
                std::cout << "==================Chess Piece========================\n";
                std::cout << "Pawn: Only Moves forward once, cannot attack forward but can attack diagonal if the enemy is one sqaure close to the pawn.\n";
                std::cout << "Knight: Can only make an L shape and the only unit that can go pass over other units if they are in front of them.\n";
                std::cout << "*Fun Fact: S is Knight and is also called Springer in German. So keep that in mind.\n";
                std::cout << "Bishop: Can only go diagonal from left diagonal and right diagonally(up and down diagonal)\n";
                std::cout << "Rook: Can only go forward, backwards, right and left. It also do a special move with King (Which your going find out)\n";
                std::cout << "Queen: The most powerful unit on the board. It has the Rook and Bishop own move set. Be wise of how to use it.\n";
                std::cout << "King: The king is the most important unit you need protect. It can move like the Queen but can only move one squre per turn.\n";
                std::cout << "Other Units will be added soon...\n";
                std::cout << "=====================================================\n";
                std::cout << "Exit press 0.\n";
                std::cin >> x;
                if (x == 0){
                    std::cout << "You want to exit (y/n):\n";
                    std::cin >> exit_choice;
                    if (exit_choice == "y" || exit_choice == "Y"){
                        restarting = true;
                        break;
                    }
                }
                break;
            }
            case 3:{//Instruction
                int x;
                std::string exit_choice;
                std::cout << "===============Instruction===============\n";
                std::cout << "1. Each player has 16 chess pieces. The goal is try to trap the king by getting a CHECK MATE.\n";
                std::cout << "2. You have to pick one Chess Piece and move the step of how many steps that you want the chess piece to move.\n";
                std::cout << "*Recommend you to check the Chess Description\n";
                std::cout << "3. Strategies your moves and think two steps ahead of your oppenet.\n";
                std::cout << "4. You have to enter a Number of which chest piece you want to move. If it is higher than 15 or other than a number, then you get an error and it will be given to next player (Please cautionous).\n";
                std::cout << "5. It will also show the status of each player of how many chess piece you have left and many other more that your going to find out.\n";
                std::cout << "6. one lasting, HAVE FUN or just be serious about the game.\n";
                std::cout << "=========================================\n";
                std::cout << "Exit press 0.\n";
                std::cin >> x;
                if (x == 0){
                    std::cout << "You want to exit (y/n):\n";
                    std::cin >> exit_choice;
                    if (exit_choice == "y" || exit_choice == "Y"){
                        restarting = true;
                        break;
                    }
                }
                break;
            }
            case 4: {
                int option;
                std::string decision;
                std::string exit_choice;
                std::cout << "---------Option---------\n";
                std::cout << "Colors (1)\n";
                std::cout << "Timer (2)\n";
                std::cout << "-------------------------\n";
                std::cout << "Exit press 0.\n";
                std::cin >> option;
                if (option == 0){
                    std::cout << "You want to exit (y/n):\n";
                    std::cin >> exit_choice;
                    if (exit_choice == "y" || exit_choice == "Y"){
                        restarting = true;
                        break;
                    }
                }

                if (option == 1){
                    std::string pick;
                    std::string decision;
                    std::cout << "What color do you want (Classic (C), Traditional (T), or Modern (M))\n";
                    std::cin >> pick;
                    if (pick == "C" || pick == "c"){
                        std::cout << "Do You Want To Pick This Color (y/n):\n";
                        std::cin >> decision;
                        if (decision == "y" || decision == "Y"){
                            dynamicWhite = "\033[30m";
                            dynamicBlack = "\033[37m";
                            std::cout << "Changing Theme on Board into Classic.\n";
                            to_case = true;
                        }
                    } else if (pick == "T" || pick == "t"){
                        std::cout << "Do You Want To Pick This Color (y/n):\n";
                        std::cin >> decision;
                        if (decision == "y" || decision == "Y"){
                            dynamicWhite = "\033[33m";
                            dynamicBlack = "\033[38;2;222;184;135m";
                            std::cout << "Changing Theme on Board into Traditional.\n";
                            to_case = true;
                        }
                    } else if (pick == "M" || pick == "m"){
                        std::cout << "Do You Want To Pick This Color (y/n):\n";
                        std::cin >> decision;
                        if (decision == "y" || decision == "Y"){
                            dynamicWhite = "\033[92m";
                            dynamicBlack = "\033[97m";
                            std::cout << "Changing Theme on Board into Modern.\n";
                            to_case = true;
                        }
                    }
                } else if (option == 2){
                    int time_control;
                    int control;
                    std::cout << "What time do want (Bullet (1), Blitz(2), Rapid(3), Classical(4), None(5))\n";
                    std::cin >> time_control;
                    if (time_control == 1){
                        std::cout << "Do You Want To Pick This Time (y/n):\n";
                        std::cin >> decision;
                        if (decision == "y" || decision == "Y"){
                            time = 180;
                            std::cout << "Changing Time for the match.\n\n";
                            to_case = true;
                        } else if (time_control == 2) {
                            std::cout << "Blitz: Which time, 5 minutes (1) or 10 minutes (2):\n";
                            std::cin >> control;
                            if (control == 1){
                                time = 300;
                                std::cout << "Blitz Mode: Changing to 5 minutes\n\n";
                                to_case = true;
                            } else if (control == 2){
                                time = 600;
                                std::cout << "Blitz Mode: Changing to 10 minutes\n\n";
                                to_case = true;
                            }
                        } else if (time_control == 3){
                            std::cout << "Rapid: Which time, 15 minutes (1) or 60 minutes (2):\n";
                            std::cin >> control;
                            if (control  == 1){
                                time = 900;
                                std::cout << "Rapid Mode: Changing to 15 mintues\n\n";
                                to_case = true;
                            } else if (control == 2) {
                                time = 3600;
                                std::cout << "Rapid Mode: Changing to 60 minutes\n\n";
                                to_case = true;
                            }
                        } else if (time_control == 4) {
                            std::cout << "Classical: Which time, 2 hours (1) or 6+ hours(2):\n";
                            std::cin >> control;
                            if (control == 1){
                                time = 7200;
                                std::cout << "Classical Mode: Changing to 2 hours\n\n";
                                to_case = true;
                            } else if (control == 3){
                                std::cout << "Since You pick this, how many hours?\n";
                                std::cout << "Needs to be in seconds.\n";
                                std::cin >> time;
                                int hours = time / 3600;
                                std::cout << "Classical Mode: Changing to " << hours << "hours\n\n";
                                to_case = true;
                            }
                        } else if (time == 5) {
                            time = 0;
                            std::cout << "Default Mode: Deactivating timer.\n\n";
                            to_case = true;
                        }
                    }
                } 
                    //else if (option == 3){
                    //} 
                else {
                    try{
                        if (option != 1 || option != 2 || option != 3){
                            throw std::runtime_error("Exeception: Wrong Number or Unknown Input.");
                        }    
                    } catch (const runtime_error& e) {
                        std::cerr << "ERROR - " << e.what() << "\n" << std::endl;
                    }
                }
                restarting = true;
                break;
            }

            case 5: {
                cout << "Exiting, Have A Great Day!!!\n";
                break;
            }

            default:
                try{
                    if (choice != 1 || choice != 2 || choice != 3){
                        throw std::runtime_error("Execption: Wrong Number of picking an option.");
                    }
                } catch(const runtime_error& e) {
                    std::cerr << "ERROR - " << e.what() << "\n" << std::endl;
                }
                restarting = true;
                break;
        }
    } while (restarting);
    return 0;
}
