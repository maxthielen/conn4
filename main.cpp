#include <iostream>
#include <climits>
#include <cassert>
#include "board.h"
#include <ctime>


int negamax(lib::board node, int alpha, int beta, int depth) {
    assert(alpha < beta);

    // Checking if the current board position results in win/loss/draw and returning the heuristic value
    // Heuristic value is determined on how fast win/loss can be achieved
    // If depth reaches 0, return 0
    if (node.gameOver() || depth == 0) {

        if (node.isDraw()) {

            return 0;

        } else if (node.isWin()){

            return ((42 - node.counter) / 2);

        } else if (node.isLoss()){

            return -((42 - node.counter) / 2);

        } else {
            return 0;
        }
    }


    int max = (42 - node.counter) / 2; // setting an upper bound of the score

    if (beta > max) {
        beta = max;                     // there is no need to keep beta above our max possible score.
        if (alpha >= beta) return beta;  // prune the exploration if the [alpha;beta] window is empty.
    }

    for(int move : node.listMoves()) {
        node.makeMove(move);

        int score = -negamax(node, -beta, -alpha, depth - 1);  // explore opponents score

        node.undoMove();
        if (score >= beta) {return score; } // prune the exploration if we find a possible move better than what we were looking for.
        if (score > alpha) {
            alpha = score;
        } // reduce the [alpha;beta] window for next exploration, as we only need to search for a position that is better than the best so far.

    }
    return alpha;

}

int findBestMove(lib::board board, int depth){ // set-up of the ai move

    int bestValue = -INT_MAX;
    int bestMove{};
    auto moves = board.listMoves();
    for(int move : moves) {
        board.makeMove(move);
        int value = -negamax(board, -INT_MAX, INT_MAX, depth - 1);
        if(bestValue < value){
            bestMove = move;
            bestValue = value;
        }
        board.undoMove();
        std::cout << "Move: " << move << " Score: " << value << " Best Score: " << bestValue << '\n';
    }
    return bestMove;
}

int main() {
    auto m_board = lib::board();
    bool menu{true};
    int depth;
    std::srand(std::time(nullptr));

    std::cout << "Please enter the depth\n[2-5] - Easy, [5-8] - Medium, [8+] - Hard\nP.S: The higher the depth, the longer it will take (below 14 recommended): ";
    std::cin >> depth;
    int rng = std::rand(); // random number to choose who goes first

    while(menu){
        if((m_board.getTurn() + rng) % 2) {
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

            if(m_board.isLoss()){
                menu = false;
                m_board.print();
                std::cout << "Congratulations! Nice match." << std::endl;
            }
        }
        else {
            std::cout << "STARTING search for move: " << m_board.counter << std::endl;
            int move{findBestMove(m_board, depth)};
            m_board.makeMove(move);
            std::cout << "FOUND Best Move: " << move << std::endl;
            if(m_board.isLoss()){
                menu = false;
                m_board.print();
                std::cout << "Nice Match. Better luck next time." << std::endl;
            }
        }
    }
    return 0;
}