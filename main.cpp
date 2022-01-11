#include <iostream>
#include <climits>
#include "board.h"

int minimax(lib::board node, int depth, bool maximizing){
    if(depth==0 || node.gameOver()){
        int value;
        if(node.isWin(node.get0())) value = 1; // win
        else if(node.isWin(node.get1())) value = 2; // loss
        else if(node.isDraw()) value = 0; // tie
        else value = -2; // max depth reached
        std::cout << "000 Depth: " << depth << " Score: " << value << std::endl;
        return value;
    }
    if(maximizing){
        int value = -INT_MAX;
        auto moves = node.listMoves();
        for(int move : moves) {
            node.makeMove(move);
            value = std::max(value, minimax(node, depth-1, false));
            std::cout << "+++ Previously: ";
            for(auto m:node.moves) std::cout << m << " ";
            std::cout << std::endl;
            std::cout << "+++ Depth: " << depth << " Move: " << move << " Score: " << value << std::endl;
            if(node.isWin(node.get0())) {
                std::cout << "+++ I win. :P" << std::endl;
                std::cout << "Game Over: " << node.gameOver() << std::endl;
            }
            if(node.isWin(node.get1())) {
                std::cout << "+++ Player wins. :(" << std::endl;
                std::cout << "Game Over: " << node.gameOver() << std::endl;
            }
            node.undoMove();
        }

        return value;
    }
    else{
        int value = -INT_MAX;
        auto moves = node.listMoves();
        for(int move : moves) {
            node.makeMove(move);
            value = std::max(value, minimax(node, depth-1, true));
            std::cout << "--- Previously: ";
            for(auto m:node.moves) std::cout << m << " ";
            std::cout << std::endl;
            std::cout << "--- Depth: " << depth << " Move: " << move << " Score: " << value << std::endl;
            if(node.isWin(node.get0())) {
                std::cout << "+++ I win. :P" << std::endl;
                std::cout << "Game Over: " << node.gameOver() << std::endl;
            }
            if(node.isWin(node.get1())) {
                std::cout << "+++ Player wins. :(" << std::endl;
                std::cout << "Game Over: " << node.gameOver() << std::endl;
            }
            node.undoMove();
        }
        return value;
    }
}

int findBestMove(lib::board board){
    int bestValue = -INT_MAX;
    int bestMove{};
    auto moves = board.listMoves();
    for(int move : moves) {
        board.makeMove(move);
        int value = std::max(bestValue, minimax(board, 2, false));
        if(bestValue < value){
            bestMove = move;
            bestValue = value;
        }
        board.undoMove();
        std::cout << "Move: " << move << " Score: " << value << " Best Score: " << bestValue << std::endl;
    }
    return bestMove;
}

int main() {
    auto m_board = lib::board();
    bool menu{true};
    while(menu){
        if(m_board.getTurn()) {
            m_board.print();
            int input{-1};
            do {
                std::cout << "Please choose a column: ";
                std::cin >> input;
                std::cout << std::endl;
            } while (![m_board, input](){
                        for(int move:m_board.listMoves()){
                            if(move==input) return true;
                        }
                        return false;
                    }());
            m_board.makeMove(input);

            if(m_board.isWin(m_board.get1())){
                menu = false;
                m_board.print();
                std::cout << "Congratulations! Nice match." << std::endl;
            }
        }
        else {
            std::cout << "STARTING search for move: " << m_board.counter << std::endl;
            int move{findBestMove(m_board)};
            m_board.makeMove(move);
            std::cout << "FOUND Best Move: " << move << std::endl;
            if(m_board.isWin(m_board.get0())){
                menu = false;
                m_board.print();
                std::cout << "Nice Match. Better luck next time." << std::endl;
            }
        }
    }
    return 0;
}