//
// Created by max on 04-01-22.
//

#include <iostream>
#include "../include/board.h"

namespace lib{
    void board::makeMove(int col) {
        //move stores the next available height in the specified column and height is incremented
        long move = 1L << height[col]++;
        //(counter & 1) checks if the counter is even or odd
        // xor operation notes the change the move made on the player's bitboard
        bitboards[(counter & 1)] ^= move;
        //move is stored and counter incremented
        if(counter == moves.size()) moves.resize(counter*2);
        moves[counter++] = col;
    }

    void board::undoMove() {
        //last played column is recalled from moves array
        int col = moves[--counter];
        //the previous height of the column is stored in move
        long move = 1L << --height[col];
        //the bit is unset on the corresponding bitboard with another xor operation
        bitboards[(counter & 1)] ^= move;
    }

    bool board::isWin(long bitboard) const{
        int directions[] = {1, 7, 6, 8};
        long bb;
        for(int dir : directions){
            bb = bitboard & (bitboard >> dir);
            if((bb & (bb >> (2*dir))) != 0) return true;
        }
        return false;
    }

    bool board::isConnect3(long bitboard, int col) const{
        long move = 1L << height[col];
        if(bitboard & (move >> 6))
        return false;
    }
    bool board::isConnect2(long bitboard) const{
        if ((bitboard & (bitboard >> 6)) != 0) return true; // diagonal \.
        if ((bitboard & (bitboard >> 8)) != 0) return true; // diagonal /.
        if ((bitboard & (bitboard >> 7)) != 0) return true; // horizontal
        if ((bitboard & (bitboard >> 1)) != 0) return true; // vertical
        return false;
    }

    std::vector<int> board::listMoves() const {
        std::vector<int> valid_moves;
        long TOP = 0b1000000100000010000001000000100000010000001000000L;
//        for(int col{0}; col<=6; col++){
//            if((TOP & (1L << height[col])) == 0) valid_moves.push_back(col);
//        }
        for (int i = 0; i < 7; i++){
            int pos = 7 / 2 + (1 - 2 * (i % 2)) * (i + 1) / 2; // initialize the column exploration order,
            if((TOP & (1L << height[pos])) == 0) valid_moves.push_back(pos);
        }
        return valid_moves;
    }

    void board::print() const{
        int newCol = 6;
        int buffer = 5;
        for(int i{0}; i<42; i++){
            if((bitboards[0] >> buffer) & 1) std::cout << "X ";
            else if((bitboards[1] >> buffer) & 1) std::cout << "0 ";
            else std::cout << ". ";
            if(i == newCol){
                std::cout << '\n';
                newCol += 7;
                buffer -= 43;
            } else buffer += 7;
        }
        std::cout << "-------------\n0 1 2 3 4 5 6\n\n";
    }

    board::board() {
        bitboards[0] = 0L;
        bitboards[1] = 0L;
        counter = 0;
        moves.resize(1);
    }
}
