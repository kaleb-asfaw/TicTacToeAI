#include <iostream>
#include <vector>
#include <string>
#include "functions.hpp"
#include "minimax.hpp"

const std::vector<std::string> COMMANDS = {"--help", "--exit"}; // Non-number inputs

std::vector<std::vector<char>> generateBoard() {
    return std::vector<std::vector<char>>(3, std::vector<char>(3, '_'));
}

int main() {
    std::cout << std::endl;
    int turn = printInstructions(); // Instructions for how to select squares + intro message
    std::vector<std::vector<char>> board = generateBoard();
    
    switch (turn){
        case 1:
            std::cout << "You\'ve opted to go first!" << std::endl << std::endl;
            break;
        case 2:
            std::cout << std::endl << "You\'ve opted to let the AI go first, how brave!" << std::endl << std::endl;
            break;

        default:
            std::cout << "I don't know wagwan, but there was an error. Fatal.";
            exit(0);};

    std::cout << "Select difficulty level (0 for easy, 1 for hard): ";
    int diff;
    while (true){
        std::cin >> diff;
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Remove bad input
            std::cout << "This application only accepts integer values. Please try again: ";}
        
        else if (diff != 0 && diff != 1){
            std::cout << "Invalid input. Please select 0 (easy) or 1 (hard): ";}
        else{
            break;
        }
        };
    
    std::cout << std::endl;

    if (turn == -1){
        exit(0);}
    
    bool playerTurn = (turn == 1); 
    bool difficulty = (diff == 1); // true is minimax, false is easy mode (random selection)
    
    while (true){
        if (playerTurn){ // If it's the player's turn
            playerMove(board);
            if (isWin(board, 'X')){
                printBoard(board);
                std::cout << std::endl << "You win! Run program to play again.";
                exit(0);
            }
            playerTurn = false;
        }
        else{ // If it's the AI's turn
            aiMove(board, difficulty);
            if (isWin(board, 'O')){
                printBoard(board);
                std::cout << std::endl << "The AI wins, run program to play again.";
                exit(0);
            }
            playerTurn = true;
        }

        if (boardFull(board)){
            printBoard(board);
            std::cout << std::endl << "You drew! Run program to play again.";
            exit(0);
        }

    }

}
