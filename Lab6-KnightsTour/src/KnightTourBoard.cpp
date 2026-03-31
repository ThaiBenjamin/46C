#include "KnightTourBoard.hpp"

#include <iomanip>
#include <iostream>

// TODO: Identify all Knight move offsets
const int KnightTourBoard::KNIGHT_MOVES[8][2] = {
    {2,1}, {1,2}, {-1,2}, {-2,1},{-2,-1}, {-1,-2}, {1,-2}, {2,-1}
};

KnightTourBoard::KnightTourBoard(int size)
    : size_(size), board_(size, std::vector<int>(size, 0)), currentMoveNumber_(0) {}

KnightTourBoard::~KnightTourBoard() = default;

bool KnightTourBoard::makeMove(int row, int col) {
    // TODO: implement makeMove to update the board state with the knight's move
    if(isValidMove(row, col)){
        currentMoveNumber_++;
        board_[row][col] = currentMoveNumber_;
        return true;
    }
    return false;
}

bool KnightTourBoard::isValidMove(int row, int col) const {
    // TODO: implement isValidMove to check if the move is valid
    if (row < 0 || row >= size_ || col < 0 || col >= size_) {
        return false;
    }
    if(isVisited(row, col)){
        return false;
    }
    return true;
}

std::vector<std::pair<int, int>> KnightTourBoard::getLegalMoves(int currentRow, int currentCol) const {
    // TODO: implement getLegalMoves to return a vector of legal moves from the current position
    std::vector<std::pair<int, int>> legalMoves;
    
    for (int i = 0; i < 8; ++i) {
        int newRow = currentRow + KNIGHT_MOVES[i][0];
        int newCol = currentCol + KNIGHT_MOVES[i][1];
        
        if (isValidMove(newRow, newCol)){
            legalMoves.push_back({newRow, newCol});
        }
    }
    return legalMoves;
}

int KnightTourBoard::countLegalMoves(int row, int col) const {
    // TODO: implement countLegalMoves to return the number of legal moves from the given position
    int count = 0;

    for (int i = 0; i < 8; i++) {
        int rowCount = row + KNIGHT_MOVES[i][0];
        int colCount = col + KNIGHT_MOVES[i][1];

        if (isValidMove(rowCount, colCount))
            count++;
    }

    return count;
}

void KnightTourBoard::reset() {
    currentMoveNumber_ = 0;
    for (auto& row : board_) {
        std::fill(row.begin(), row.end(), 0);
    }
}

void KnightTourBoard::display() const {
    const int maxVal = size_ * size_;
    const int cellWidth = std::max<int>(2, std::to_string(maxVal).size());

    std::cout << "\n     ";
    for (int col = 0; col < size_; ++col) {
        std::cout << std::setw(cellWidth + 1) << col;
    }
    std::cout << '\n';

    const int borderWidth = (cellWidth + 2) * size_;
    std::cout << "   +" << std::string(borderWidth, '-') << "+\n";

    for (int row = 0; row < size_; ++row) {
        std::cout << std::setw(3) << row << " |";
        for (int col = 0; col < size_; ++col) {
            std::string cellRep;
            if (board_[row][col] == 0) {
                cellRep = ".";
            } else if (board_[row][col] == currentMoveNumber_) {
                cellRep = "K";
            } else {
                cellRep = std::to_string(board_[row][col]);
            }
            std::cout << " " << std::setw(cellWidth) << cellRep;
        }
        std::cout << " |\n";
    }

    std::cout << "   +" << std::string(borderWidth, '-') << "+\n";
}

bool KnightTourBoard::isVisited(int row, int col) const {
    // TODO: implement isVisited to check if the given position has been visited
    return board_[row][col] > 0;
}

int KnightTourBoard::getMoveNumber(int row, int col) const {
    return board_[row][col];
}