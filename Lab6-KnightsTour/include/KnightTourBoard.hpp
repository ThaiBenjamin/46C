#ifndef KNIGHTTOUR_BOARD_HPP
#define KNIGHTTOUR_BOARD_HPP

#include <sstream>
#include <string>
#include <vector>

struct Position {
    int row;
    int col;

    Position() : row(0), col(0) {}
    Position(int r, int c) : row(r), col(c) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << "(" << row << ", " << col << ")";
        return oss.str();
    }

    bool isValid(int boardSize) const {
        return row >= 0 && row < boardSize && col >= 0 && col < boardSize;
    }
};

class KnightTourBoard {
public:
    explicit KnightTourBoard(int size = 8);
    ~KnightTourBoard();

    bool makeMove(int row, int col);
    bool isValidMove(int row, int col) const;
    std::vector<std::pair<int, int>> getLegalMoves(int currentRow, int currentCol) const;
    int countLegalMoves(int row, int col) const;

    void reset();
    void display() const;
    int getSize() const { return size_; }
    bool isVisited(int row, int col) const;
    int getMoveNumber(int row, int col) const;

private:
    int size_;
    std::vector<std::vector<int>> board_;
    int currentMoveNumber_;
    static const int KNIGHT_MOVES[8][2];
};

#endif // KNIGHTTOUR_BOARD_HPP