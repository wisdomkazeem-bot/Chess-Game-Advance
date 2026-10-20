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
#include <cmath>
#include <thread>//thread and chrono are use for timer
#include <chrono>
#include <new>// Restarts a new match

//Wisdom Kazeem
//Ontario Tech University
//Started: September 20th, 2026

//CPU: Unlock patterns
//Let it to show a countdown going down using \r.
int main() {
    Chess chess;
    int numberOfPlayers = 2;
    std::vector<Player> players;
    
    //Default Colors
    std::string dynamicWhite = "\033[33m";
    std::string dynamicBlack = "\033[38;2;222;184;135m";

    //Default Time
    int time = 0;

    bool newMatch = false;
    auto setupGame = [&](){
        newMatch = true;
        int moveOpt = chess.getMovementOption();
        chess.~Chess();
        new (&chess) Chess(); //Reference from Claude
        chess.setMovementOption(moveOpt);
        players.clear();
        // Initialize players and their chess pieces
        for (int i = 0; i < numberOfPlayers; ++i) {
            Player player;
            players.push_back(player);
        }

        //Reference from Gemini for the p1 and p2.
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
    };
    setupGame();

    int choice;
    bool restarting;
    bool restarting_game = false;
    bool to_case = false;
    bool isTimer = false;
    bool isRandom = false;

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
        } else if (restarting_game){
            choice = 0;
            restarting_game = false;
            cin >> choice;
        } else {
            choice = 0;
            cin >> choice;
        }

        switch (choice){
            case 1: {
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

                        if (isRandom){
                            int roll = rand() % 2;
                            if (roll == 0){
                                chess.setMovementOption(1);
                                std::cout << "[Random Alert] Changing Input Mode: Direction Movement.\n";
                            } else {
                                chess.setMovementOption(2);
                                std::cout << "[Random Alert] Changing Input Mode: Coordinate Movement.\n";
                            }
                        }

                        chess.displayMap(dynamicWhite, dynamicBlack);
                        std::cout << "\n--- Player " << playerNumber << "'s Turn ---\n";
                        int leftoverTime = currentPool;

                        if (isTimer) {
                            std::cout << "Time Remaining: " << leftoverTime << "s\n";
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

                            //Reference by Gemini for steps
                            int steps;
                            if (chess.getMovementOption() == 1){
                                if (symbol == "R" || symbol == "Q" || symbol == "B"){
                                    std::cout << "How Many Steps: ";
                                    std::cin >> steps;
                                    std::cin.ignore();
                                    chess.current_move_steps = steps;
                                } else if (symbol == "P"){
                                    //Reference by Gemini
                                    std::string pawnKey = std::to_string(playerNumber) + "_" + std::to_string(selection);
                                    static std::vector<std::string> chosenPawnsLog;
                                    
                                    if (newMatch) {
                                        chosenPawnsLog.clear();
                                        newMatch = false;
                                    }

                                    bool hasMovedBefore = false;
                                    for (const auto& log : chosenPawnsLog) {
                                        if (log == pawnKey) {
                                            hasMovedBefore = true;
                                            break;
                                        }
                                    }

                                    if (!hasMovedBefore){
                                        std::cout << "How Many Steps (1 or 2): ";
                                        std::cin >> steps;
                                        std::cin.ignore();
                                        if (steps == 2) {
                                            chess.current_move_steps = 2;
                                        } else {
                                            chess.current_move_steps = 1;
                                        }
                                    }
                                    

                                    chosenPawnsLog.push_back(pawnKey);
                                } else {
                                    chess.current_move_steps = 1;
                                }
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

                        bool gameOver = false;
                        while (!gameOver){
                            for (size_t i = 0; i < players.size(); ++i) {
                                int currentPlayerNum = static_cast<int>(i) + 1;
                                int winningPlayerNumber = (currentPlayerNum == 1) ? 2 : 1;

                                if (chess.isKingDefeated(currentPlayerNum)){
                                    if (chess.checkWinCondition(currentPlayerNum)) {
                                        std::cout << "=========================================\n";
                                        std::cout << "PLAYER " << winningPlayerNumber << " Wins!\n";
                                        std::cout << "=========================================\n";
                                    
                                        gameOver = true;
                                        chess.displayMap(dynamicWhite, dynamicBlack);
                                        // Ask the user if they want to continue or quit the game
                                        std::cout << "Do you want to quit the match? (y/n): ";
                                        std::cin >> userChoice;
                                        if (userChoice == 'Y' || userChoice == 'y') userChoice = 'y';
                                        if (userChoice == 'n' || userChoice == 'N'){
                                            setupGame();
                                            player1Clock = time;
                                            player2Clock = time;
                                            restarting_game = true;
                                            gameOver = true;
                                            userChoice = 'n';
                                            break;
                                        } else {
                                            restarting = false;
                                            userChoice = 'y';
                                            gameOver = true;
                                            break;
                                        }
                                    } else {
                                        std::cout << "Player " << currentPlayerNum << " is in CHECK.\n";
                                        continue;
                                    }
                                } else if (isTimer) {
                                    int currentPool = (playerNumber == 1) ? player1Clock : player2Clock;

                                    leftoverTime = currentPool - secondsTaken;
                                    
                                    if (leftoverTime <= 0 && secondsTaken > time) {
                                        secondsTaken = 1;
                                        leftoverTime = currentPool - secondsTaken;
                                        if (playerNumber == 1) player1Clock = leftoverTime;
                                        else player2Clock = leftoverTime;
                                    }

                                    if (leftoverTime <= 0) {
                                        int winningPlayerNumber = (playerNumber == 1) ? 2 : 1;
                                        std::cout << "\n========================================\n";
                                        std::cout << "PLAYER " << winningPlayerNumber << " Wins!\n";
                                        std::cout << "========================================\n";
                                        std::cout << "Do you want to quit the match? (y/n): ";
                                        std::cin >> userChoice;
                                        if (userChoice == 'Y' || userChoice == 'y') userChoice = 'y';
                                        if (userChoice == 'n' || userChoice == 'N'){
                                            setupGame();
                                            player1Clock = time;
                                            player2Clock = time;
                                            restarting_game = true;
                                            gameOver = true;
                                            userChoice = 'n';
                                            break;
                                        } else {
                                            restarting = false;
                                            userChoice = 'y';
                                            gameOver = true;
                                            break;
                                        }
                                    } else {
                                        if (playerNumber == 1) player1Clock = leftoverTime;
                                        else player2Clock = leftoverTime;
                                        gameOver = true;
                                    }
                                } 
                            }
                            gameOver = true;
                        }
                        if (userChoice == 'y') break;
                        if (restarting_game){
                            restarting_game = false;
                            break;
                        }
                    }
                }
                restarting = true;
                break;
            } case 2: { //Descripition for the chess piece
                int x;
                std::string exit_choice;
                std::cout << "==================Chess Piece========================\n";
                std::cout << "Pawn: Only Moves forward once, but you can move twice from your original spot. You cannot attack forward but can attack diagonal if the enemy is one sqaure close to the pawn.\n";
                std::cout << "*Once the pawn goes to the other side of the board it will be promoted to any of the chess piece that have been remove from the game.\n"
                std::cout << "Knight: Can only make an L shape and the only unit that can go pass over other units if they are in front of them.\n";
                std::cout << "*Fun Fact: S is Knight and is also called Springer in German. So keep that in mind.\n";
                std::cout << "Bishop: Can only go diagonal from left diagonal and right diagonally(up and down diagonal)\n";
                std::cout << "Rook: Can only go forward, backwards, right and left. It also do a special move with King (Which your going find out)\n";
                std::cout << "Queen: The most powerful unit on the board. It has the Rook and Bishop own move set. Be wise of how to use it.\n";
                std::cout << "King: The king is the most important unit you need protect. It can move like the Queen but can only move one squre per turn.\n";
                std::cout << "*Other Units will be added soon...\n";
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
            } case 3: {//Instruction
                int x;
                std::string exit_choice;
                std::cout << "===============Instruction===============\n";
                std::cout << "1. Each player has 16 chess pieces. The goal is try to trap the king by getting a CHECK MATE.\n";
                std::cout << "2. You have to pick one Chess Piece and move the step of how many steps that you want the chess piece to move.\n";
                std::cout << "*Recommend you to check the Chess Description\n";
                std::cout << "3. Strategies your moves and think two steps ahead of your oppenet.\n";
                std::cout << "4. You have to enter a Number of which chest piece you want to move. If it is higher than 15 or other than a number, then you get an error and it will be given to next player (Please cautionous).\n";
                std::cout << "5. It will also show the status of each player of how many chess piece you have left and the total sight range each chess piece has in total.\n";
                std::cout << "6. Both players have a timer, when player has it turn, it will run down the clock, if there timer goes down to zero the player automatically loses.\n";
                std::cout << "7. One lasting, HAVE FUN or just be serious about the game.\n";
                std::cout << "*Recommed Check the Option: \n";
                std::cout << "You can change the time (since there is no timer as default).\n";
                std::cout << "You can change the game settings, to find what is comfortable for you to play.\n";
                std::cout << "You can even change the boards color.\n"
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
            } case 4: {
                int option;
                std::string decision;
                std::string exit_choice;
                std::cout << "\n---------Option---------\n";
                std::cout << "Colors (1):\n";
                std::cout << "Timer (2):\n";
                std::cout << "Game Setting (3):\n";
                std::cout << "-------------------------\n";
                std::cout << "Exit press 0.\n";
                std::cout << "Enter Your Choice: ";
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
                            isTimer = true;
                        } 
                    } else if (time_control == 2) {
                        std::cout << "Blitz: Which time, 5 minutes (1) or 10 minutes (2):\n";
                        std::cin >> control;
                        if (control == 1){
                            std::cout << "Do You Want To Pick This Time (y/n):\n";
                            std::cin >> decision;
                            if (decision == "y" || decision == "Y"){
                                time = 300;
                                std::cout << "Blitz Mode: Changing to 5 minutes\n\n";
                                to_case = true;
                                isTimer = true;
                            }
                        } else if (control == 2){
                             std::cout << "Do You Want To Pick This Time (y/n):\n";
                            std::cin >> decision;
                            if (decision == "y" || decision == "Y"){
                                time = 600;
                                std::cout << "Blitz Mode: Changing to 10 minutes\n\n";
                                to_case = true;
                                isTimer = true;
                            }
                        }
                    } else if (time_control == 3){
                        std::cout << "Rapid: Which time, 15 minutes (1) or 60 minutes (2):\n";
                        std::cin >> control;
                        if (control  == 1){
                             std::cout << "Do You Want To Pick This Time (y/n):\n";
                            std::cin >> decision;
                            if (decision == "y" || decision == "Y"){
                                time = 900;
                                std::cout << "Rapid Mode: Changing to 15 mintues\n\n";
                                to_case = true;
                                isTimer = true;
                            }
                        } else if (control == 2) {
                             std::cout << "Do You Want To Pick This Time (y/n):\n";
                            std::cin >> decision;
                            if (decision == "y" || decision == "Y"){
                                time = 3600;
                                std::cout << "Rapid Mode: Changing to 60 minutes\n\n";
                                to_case = true;
                                isTimer = true;
                            }
                        }
                    } else if (time_control == 4) {
                        std::cout << "Classical: Which time, 2 hours (1) or 6+ hours(2):\n";
                        std::cin >> control;
                        if (control == 1){
                            std::cout << "Do You Want To Pick This Time (y/n):\n";
                            std::cin >> decision;
                            if (decision == "y" || decision == "Y"){
                                time = 7200;
                                std::cout << "Classical Mode: Changing to 2 hours\n\n";
                                to_case = true;
                                isTimer = true;
                            }
                        } else if (control == 3){
                            std::cout << "Since You pick this, how many hours?\n";
                            std::cout << "Needs to be in seconds.\n";
                            std::cin >> time;
                            std::cout << "Do You Want To Pick This Time (y/n):\n";
                            std::cin >> decision;
                            if (decision == "y" || decision == "Y"){
                                int hours = time / 3600;
                                std::cout << "Classical Mode: Changing to " << hours << "hours\n\n";
                                to_case = true;
                                isTimer = true;
                            }
                        }
                    } else if (time == 5) {
                        time = 0;
                        std::cout << "Default Mode: Deactivating timer.\n\n";
                        to_case = true;
                        isTimer = false;
                    }
                } else if (option == 3){
                    int pick_moves;
                    std::cout << "What way do want to play in Direction Moves (1), Coordinate Moves (2), Random Moves(3):\n";
                    std::cin >> pick_moves;
                    if (pick_moves == 1 || pick_moves == 2){
                        std::cout << "Do You Want To Pick This Mode (y/n):\n";
                        std::cin >> decision;
                        if (decision == "y" || decision == "Y"){
                            std::cout << "Changing movement option input.\n";
                            chess.setMovementOption(pick_moves);
                            to_case = true;
                        }
                    } else if (pick_moves == 3){
                        std::cout << "Do You Want To Pick This Mode (y/n):\n";
                        std::cin >> decision;
                        if (decision == "y" || decision == "Y"){
                            std::cout << "Activating Random Mode.\n";
                            isRandom = true;
                            to_case = true;
                        }
                    }
                } else {
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
            } case 5: {
                cout << "Exiting, Have A Great Day!!!\n";
                break;
            } default:
                try{
                    if (choice != 1 || choice != 2 || choice != 3 ||choice != 4 || choice != 5){
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
