#ifndef MINIMAX_HPP
#define MINIMAX_HPP

#include "functions.hpp"
#include <iostream>
#include <vector>

inline int evaluate(const std::vector<std::vector<char>>&board){
    int n = countOpenSlots(board) + 1;
    // For the sake of consistency, X will always be maximizing, regardless of turn order
    if (isWin(board, 'X')){ 
        return n;
    }
    if (isWin(board, 'O')){
        return -1*n;
    }
    return 0;

}

inline int minimax(const std::vector<std::vector<char>>& board, int alpha, int beta, bool isMaximizing) {
    if (isWin(board, 'X') || isWin(board, 'O') || boardFull(board)){
        return evaluate(board);
    }
    
    if (isMaximizing) { // This is always 'X' (regardless of who went first)
        int maxEval = INT_MIN;

        for (auto& coordinates : getOpenSlots(board)){
            std::vector<std::vector<char>> newBoard = board; // Deep copy
            int r = coordinates.first, c = coordinates.second; 
            newBoard[r][c] = 'X'; // newBoard is now a "child" of board

            int eval = minimax(newBoard, alpha, beta, false);
            maxEval = std::max(eval, maxEval);
            // Prune irrelevant game states
            alpha = std::max(eval, alpha);
            if (beta <= alpha){
                break;}}
        
        return maxEval;
    } 
    
    else {
        int minEval = INT_MAX;
        
        for (auto& coordinates : getOpenSlots(board)){
            std::vector<std::vector<char>> newBoard = board; // Deep copy
            int r = coordinates.first, c = coordinates.second; 
            newBoard[r][c] = 'O'; // newBoard is now a "child" of board
            
            int eval = minimax(newBoard, alpha, beta, true);
            minEval = std::min(eval, minEval);
            // Prune irrelevant game states
            beta = std::min(eval, beta);
            if (beta <= alpha){
                break;}}
        
        return minEval;
    }
}
#endif 
