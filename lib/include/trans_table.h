// Inspired by http://blog.gamesolver.org/solving-connect-four/07-transposition-table/

#ifndef CONN4_TRANS_TABLE_H
#define CONN4_TRANS_TABLE_H

#include<vector>
#include<cstring>
#include<cassert>

typedef uint64_t key_t;
typedef int8_t val_t;

/**
 * Transposition Table is a simple hash map with fixed storage size.
 * In case of collision we keep the last entry and override the previous one.
 */
class TranspositionTable {
private:

    struct Entry {
        lib::board key;
        int flag;
        int depth;
    };

    std::vector<Entry> T;

    unsigned int index(lib::board key) const {
        long both = key.get0() | key.get1();
        return both%T.size();
    }

public:

    TranspositionTable(unsigned int size): T(size) {
        assert(size > 0);
    }

    /*
    * Empty the Transition Table.
    */
    void reset() { // fill everything with 0, because 0 value means missing data
        memset(&T[0], 0, T.size()*sizeof(Entry));
    }

    void put(lib::board key, val_t low, val_t up) {
        unsigned int i = index(key); // compute the index position
        T[i].key = key;              // and overide any existing value.
        //if (up != 127)
        T[i].upper = up;
        //if (low != 127)
        T[i].lower = low;
    }

    val_t getLower(key_t key) const {
        unsigned int i = index(key);  // compute the index position
        if(T[i].key == key)
            return T[i].lower;          // and return value if key matches
        else
            return 127;                //  signal missing entry
    }

    val_t getUpper(key_t key) const {
        unsigned int i = index(key);  // compute the index position
        if(T[i].key == key)
            return T[i].upper;          // and return value if key matches
        else
            return 127;                //  signal missing entry
    }

};

#endif //CONN4_TRANS_TABLE_H
