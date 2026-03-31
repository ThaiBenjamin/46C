#ifndef KNIGHTMOVE_HPP
#define KNIGHTMOVE_HPP

#include <string>

struct KnightMove {
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;

    KnightMove() : fromRow(-1), fromCol(-1), toRow(-1), toCol(-1) {}
    KnightMove(int fr, int fc, int tr, int tc) 
        : fromRow(fr), fromCol(fc), toRow(tr), toCol(tc) {}

    std::string toString() const;
    bool isValid() const;
    
    bool operator==(const KnightMove& other) const;
};

#endif