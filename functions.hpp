#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>
#include <iostream>
#include <random>
#include <cmath>
#include <utility>

// Forward declaration (rather than inclusion via header to avoid circular definitions)
int minimax(const std::vector<std::vector<char>>& board, int alpha, int beta, bool isMaximizing);


/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// PRINTER FUNCTIONS ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

inline void printBoard(const std::vector<std::vector<char>>& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << board[i][j];
            if (j < 2) {
                std::cout << " | ";
            }
        }
        std::cout << std::endl;
        if (i < 2) {
            for (int j = 0; j < 3; j++){
            if(j < 2){
            std::cout << "----";
            }
            if (j == 2){
                std::cout << "-" << std::endl;
            }
        }
    }
};
std::cout << std::endl;
};

inline void helpMessage(){
    std::cout << "Here is the numbering system for placing your tokens." << std::endl << std::endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << 3*i + j + 1;
            if (j < 2) {
                std::cout << " | ";
            }
        }
        std::cout << std::endl;
        if (i < 2) {
            for (int j = 0; j < 3; j++){
            if(j < 2){
            std::cout << "----";
            }
            if (j == 2){
                std::cout << "-" << std::endl;
            }
        }
    }};
    std::cout << std::endl;
}


inline int printInstructions() {

    std::cout << std::endl;
    std::cout << "___________________________" << std::endl << std::endl;
    std::cout << "Welcome to Tic-tac-toe vs AI!"<< std::endl;
    std::cout << "Below is the input system: entering a number will place" << std::endl;
    std::cout << "your token in the corresponding square." << std::endl << std::endl << std::endl;
    
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << 3*i + j + 1;
            if (j < 2) {
                std::cout << " | ";
            }
        }
        std::cout << std::endl;
        if (i < 2) {
            for (int j = 0; j < 3; j++){
            if(j < 2){
            std::cout << "----";
            }
            if (j == 2){
                std::cout << "-" << std::endl;
            }
        }
    }};
    std::cout << std::endl;

    std::cout << "Enter commands \"help\" (by entering 0) or \"exit\" (enter -1) at any time while playing." << std::endl;
    int turn;
    std::cout << std::endl;
    std::cout << "Do you want to go first or second? Enter 1 (first) or 2 (second): ";
    while (true){
        std::cin >> turn;
        // Check if the input operation failed
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Remove bad input
            std::cout << "This application only accepts integer values. Please try again: ";} 
        
        else if (turn == -1) { // Exit game functionality
            std::cout << "Sad to see you leave. Until next time!" << std::endl;
            return -1;
        }

        else if (turn == 0){
            std::cout << "I can help you once you're playing. Please Please select 1 (first) or 2 (second): ";
}
        else if (turn > 2 || turn < -1) {
            std::cout << "Invalid input. Please select 1 (first) or 2 (second): ";}
        
        else {
            return turn;} // Input is valid
    };


};

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// CHECKER FUNCTIONS ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

inline bool isWin(const std::vector<std::vector<char>>& board, char token){
    if (token != 'X' && token != 'O'){
        std::cout << "You have an error in the isWin function";
        return false;};
    
    // Did <token> win on any of the columns or rows?
    for (int i = 0; i < 3; i++){
        if ((board[i][0] == token && board[i][1] == token && board[i][2] == token) || 
            (board[0][i] == token && board[1][i] == token && board[2][i] == token))
            return true;};

    // Did <token> win on any of the diagonals?
    if ((board[0][0] == token && board[1][1] == token && board[2][2] == token) ||
        (board[2][0] == token && board[1][1] == token && board[0][2] == token)){
            return true;};
        
    // If either clause wasn't true, then <token> hasn't won the game.
    return false;}

inline bool boardFull(const std::vector<std::vector<char>>& board){
    for (const auto& row : board){ // auto == std::vector<char>
        for (char token : row){
            if (token == '_'){
                return false;};};};
    
    // If there isn't a single '_', then the board is full
    return true;};

inline std::vector<std::pair<int, int>> getOpenSlots(const std::vector<std::vector<char>>& board) {
    std::vector<std::pair<int, int>> openSpots;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (board[r][c] == '_') {
                openSpots.emplace_back(r, c);}}}
    return openSpots;
    }

inline int countOpenSlots(const std::vector<std::vector<char>>& board){
    int count = 0;
    for (int r = 0; r < 3; r++){
        for (int c = 0; c < 3; c++){
            if (board[r][c] == '_'){
                count++;}}}
    return count;
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// PLAYER FUNCTIONS ////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void playerMove(std::vector<std::vector<char>>& board){
    int move;
    printBoard(board);
    std::cout << "Enter your move (1-9): ";
    while(true){
        std::cin >> move;
        // Check if the input operation failed
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Remove bad input
            std::cout << "This application only accepts integer values. Enter your move (1-9): ";}
        
        else if (move < -1 || move > 9){
            std::cout << "Not a valid move. Enter your move (1-9): ";}

        else if (move == 0){
            helpMessage();
            std::cout << "Please enter your selection: ";
        }
        else if (move == -1){
            std::cout << "Sad to see you leave. Until next time!" << std::endl;
            exit(0);
        }
        else if (board[floor((move-1)/3)][(move-1)%3] != '_'){
            std::cout << "This slot has already been selected. Enter your move (1-9): ";}

        else {
            break;};};


    int r = floor((move-1)/3), c = (move-1)%3; // so that we can directly insert board[r][c]
    board[r][c] = 'X';
};

void aiMove(std::vector<std::vector<char>>& board, bool difficulty){
    std::vector<std::pair<int, int>> spots = getOpenSlots(board); // Spots which the AI randomly chooses from
    
    if (!difficulty){ // Easy mode
        if (!spots.empty()){
            int options = spots.size();
            std::random_device rd;
            std::uniform_int_distribution<int> dist(0, options-1);
            int index = dist(rd);
            
            std::pair<int, int> coordinates = spots[index];
            int r = coordinates.first, c = coordinates.second;
            board[r][c] = 'O';}
        
        else {
            std::cout << "The game is over, why are you calling the AI move function?";
            exit(0);}}
    
    else{ // Minimax mode :)
        int bestScore = INT_MAX;
        std::pair<int, int> bestMove;

        for (const auto& spot : getOpenSlots(board)){
            std::vector<std::vector<char>> newBoard = board;
            newBoard[spot.first][spot.second] = 'O';

            int score = minimax(newBoard, INT_MIN, INT_MAX, true);
            if (score < bestScore){
                bestScore = score;
                bestMove = spot;}}
        
        int r = bestMove.first, c = bestMove.second;
        board[r][c] = 'O';}
    
}
#endif
