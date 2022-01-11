//
// Created by max on 06-01-22.
//

#ifndef CONN4_MINIMAX_H
#define CONN4_MINIMAX_H
#include "board.h"

namespace lib{
    class minimax{
    public:
        minimax(board board): m_board{board} {};
        ~minimax() = default;

        bool terminalNode() { return m_board.isWin(m_board.getPlayer() || m_board.isWin(m_board.getPlayer(); }
        int evaluateMove(int depth, bool maxPlayer);


    private:
        board m_board;
    };
}

#endif //CONN4_MINIMAX_H
