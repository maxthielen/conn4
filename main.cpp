#include <iostream>
#include <climits>
#include <cassert>
#include "board.h"




int negamax(lib::board node, int alpha, int beta, int depth) {
    assert(alpha < beta);

    if(node.gameOver() || depth==0) {
        if (node.isDraw() || depth == 0) {
            // check for draw game
//            std::cout << "Player: " << node.getTurn() <<
//            " Draw" << '\n';
            return 0;
        }
        if (!node.getTurn()) {
            if (node.isWin(node.get0())) {
//                std::cout << "Score: " << ((42 - node.counter) / 2) <<
//                " Player: " << node.getTurn() <<
//                " Win!" << '\n';
                return (42 - node.counter) / 2;
            }
        } else {
            if (node.isWin(node.get1())) {
//                std::cout << "Score: " << ((42 - node.counter) / 2) <<
//                " Player: " << node.getTurn() <<
//                " Win!" << '\n';
                return (42 - node.counter) / 2;
            }
        }
    }

    int max = (42 - node.counter) / 2;

    if(beta > max) {
        beta = max;                     // there is no need to keep beta above our max possible score.
        if(alpha >= beta) return beta;  // prune the exploration if the [alpha;beta] window is empty.
    }

    for(int move : node.listMoves()) {

        node.makeMove(move);              // It's opponent turn in P2 position after current player plays x column.

        int score = -negamax(node, -beta, -alpha, depth -1); // If current player plays col x, his score will be the opposite of opponent's score after playing col x

//        std::cout << " Depth: " << depth <<
//        " Move: " << move <<
//        " Score: " << score <<
//        " Alpha: " << alpha <<
//        " Beta: " << beta <<
//        " Player: " << node.getTurn() << std::endl;

        node.undoMove();
        if(score >= beta){/* std::cout << "Pruned" << '\n';*/ return score; } // prune the exploration if we find a possible move better than what we were looking for.
        if(score > alpha) alpha = score; // reduce the [alpha;beta] window for next exploration, as we only
    }

    return alpha;

}

int m_negamax(lib::board node, int alpha, int beta, int depth, int color) {
    // check for terminal node (exit case)
    if(node.gameOver() || depth==0) {
        if (node.isDraw() || depth == 0) {
            return 0;
        }
        if (!node.getTurn()) {
            if (node.isWin(node.get0())) {
                return ((42 - (int)node.counter) / 2)*color;
            }
        } else {
            if (node.isWin(node.get1())) {
                return ((42 - (int)node.counter) / 2)*color;
            }
        }
    }

    int max = (42 - (int)node.counter) / 2;
    if(beta > max) {
        beta = max;                     // there is no need to keep beta above our max possible score.
        if(alpha >= beta) return beta;  // prune the exploration if the [alpha;beta] window is empty.
    }
    int score = -INT_MAX;
    for(int move : node.listMoves()) {
        node.makeMove(move);
        score = std::max(score,-m_negamax(node, -beta, -alpha, depth - 1, -color));
        node.undoMove();
        alpha = std::max(alpha,score);
        if(alpha >= beta) return alpha;
    }
    return score;
}

int t_negamax(lib::board node, int alpha, int beta, int depth, int color) {
    int alphaOrig = alpha;

    // check for terminal node (exit case)
    if(node.gameOver() || depth==0) {
        if (node.isDraw() || depth == 0) {
            return 0;
        }
        if (!node.getTurn()) {
            if (node.isWin(node.get0())) {
                return ((42 - (int)node.counter) / 2);
            }
        } else {
            if (node.isWin(node.get1())) {
                return ((42 - (int)node.counter) / 2);
            }
        }
    }
    int score = -INT_MAX;
    for(int move : node.listMoves()) {
        node.makeMove(move);
        score = std::max(score,-m_negamax(node, -beta, -alpha, depth - 1, -color));
        node.undoMove();
        alpha = std::max(alpha,score);
        if(alpha >= beta) return alpha;
    }
    return alpha;
}

int findBestMove(lib::board board){
    int bestValue = -INT_MAX;
    int bestMove{};
    auto moves = board.listMoves();
    for(int move : moves) {
        board.makeMove(move);
        int value = std::max(bestValue, -m_negamax(board,-INT_MAX,INT_MAX,12,1));
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

    m_board.print();
    if(m_board.isConnect2(m_board.get0())) std::cout << "Connect 2 found for Player 0\n";
    if(m_board.isConnect2(m_board.get1())) std::cout << "Connect 2 found for Player 1\n";
    if(m_board.isConnect3(m_board.get0())) std::cout << "Connect 3 found for Player 0\n";
    if(m_board.isConnect3(m_board.get1())) std::cout << "Connect 3 found for Player 1\n";

    m_board.makeMove(3);
    m_board.makeMove(2);
    m_board.print();
    if(m_board.isConnect2(m_board.get0())) std::cout << "Connect 2 found for Player 0\n";
    if(m_board.isConnect2(m_board.get1())) std::cout << "Connect 2 found for Player 1\n";
    if(m_board.isConnect3(m_board.get0())) std::cout << "Connect 3 found for Player 0\n";
    if(m_board.isConnect3(m_board.get1())) std::cout << "Connect 3 found for Player 1\n";

    m_board.makeMove(3);
    m_board.makeMove(2);
    m_board.print();
    if(m_board.isConnect2(m_board.get0())) std::cout << "Connect 2 found for Player 0\n";
    if(m_board.isConnect2(m_board.get1())) std::cout << "Connect 2 found for Player 1\n";
    if(m_board.isConnect3(m_board.get0())) std::cout << "Connect 3 found for Player 0\n";
    if(m_board.isConnect3(m_board.get1())) std::cout << "Connect 3 found for Player 1\n";

    m_board.makeMove(3);
    m_board.makeMove(2);
    m_board.print();
    if(m_board.isConnect2(m_board.get0())) std::cout << "Connect 2 found for Player 0\n";
    if(m_board.isConnect2(m_board.get1())) std::cout << "Connect 2 found for Player 1\n";
    if(m_board.isConnect3(m_board.get0())) std::cout << "Connect 3 found for Player 0\n";
    if(m_board.isConnect3(m_board.get1())) std::cout << "Connect 3 found for Player 1\n";

    m_board.makeMove(4);
    m_board.makeMove(1);
    m_board.print();
    if(m_board.isConnect2(m_board.get0())) std::cout << "Connect 2 found for Player 0\n";
    if(m_board.isConnect2(m_board.get1())) std::cout << "Connect 2 found for Player 1\n";
    if(m_board.isConnect3(m_board.get0())) std::cout << "Connect 3 found for Player 0\n";
    if(m_board.isConnect3(m_board.get1())) std::cout << "Connect 3 found for Player 1\n";


//    auto m_board = lib::board();
//    bool menu{true};
//    while(menu){
//        if(m_board.getTurn()) {
//            m_board.print();
//            int input{-1};
//            do {
//                std::cout << "Please choose a column: ";
//                std::cin >> input;
//                std::cout << std::endl;
//            } while (![m_board, input](){
//                        for(int move:m_board.listMoves()){
//                            if(move==input) return true;
//                        }
//                        return false;
//                    }());
//            m_board.makeMove(input);
//
//            if(m_board.isWin(m_board.get1())){
//                menu = false;
//                m_board.print();
//                std::cout << "Congratulations! Nice match." << std::endl;
//            }
//        }
//        else {
//            std::cout << "STARTING search for move: " << m_board.counter << std::endl;
//            int move{findBestMove(m_board)};
//            m_board.makeMove(move);
//            std::cout << "FOUND Best Move: " << move << std::endl;
//            if(m_board.isWin(m_board.get0())){
//                menu = false;
//                m_board.print();
//                std::cout << "Nice Match. Better luck next time." << std::endl;
//            }
//        }
//    }
    return 0;
}


