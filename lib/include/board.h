//
// Created by max on 04-01-22.
// https://github.com/denkspuren/BitboardC4/blob/master/BitboardDesign.md
//

#ifndef CONN4_BITSTRING_H
#define CONN4_BITSTRING_H

#include <vector>

namespace lib{
    class board{
    public:
        board();
        ~board() = default;

        void makeMove(int column);
        void undoMove();

        [[nodiscard]] std::vector<int> listMoves() const;
        [[nodiscard]] long get0() const{ return bitboards[0]; }
        [[nodiscard]] long get1() const{ return bitboards[1]; }

        [[nodiscard]] bool isWin(long bitboard) const;
        [[nodiscard]] bool isConnect3(long bitboard) const;
        [[nodiscard]] bool isConnect2(long bitboard) const;
        [[nodiscard]] bool isDraw() const{ return listMoves().empty(); }
        [[nodiscard]] bool gameOver() const { return (isWin(bitboards[0]) || isWin(bitboards[1]) || isDraw()); }
        [[nodiscard]] bool getTurn() const{ return (counter & 1); };
        std::vector<int> moves; //stores all moves made
        long counter; //counts the number of moves made

        void print() const;
    private:
        long bitboards[2]{}; //stores both players bitboards
        int height[7]{0,7,14,21,28,35,42}; //stores the current height of each column

    };
}

#endif //CONN4_BITSTRING_H
