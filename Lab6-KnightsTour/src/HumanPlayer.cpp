#include "HumanPlayer.hpp"

#include "KnightTourBoard.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

HumanPlayer::HumanPlayer() {
    resetStats();
}

HumanPlayer::~HumanPlayer() = default;

const char* HumanPlayer::name() const {
    return "Human Player";
}

SolveSummary HumanPlayer::solveTour(KnightTourBoard& board, int startRow, int startCol, int maxMoves) {
    resetStats();
    SolveSummary summary;
    board.reset();

    if (!board.makeMove(startRow, startCol)) {
        std::cout << "Invalid starting position.\n";
        return summary;
    }

    movesAttempted_ = 1;
    finalPosition_ = board.getMoveNumber(startRow, startCol);
    completed_ = false;

    int currentRow = startRow;
    int currentCol = startCol;
    const int totalSquares = board.getSize() * board.getSize();

    int maxObservedMoves = static_cast<int>(board.getLegalMoves(currentRow, currentCol).size());
    std::string line;

    while (movesAttempted_ < maxMoves && movesAttempted_ < totalSquares) {
        board.display();
        std::cout << "\nCurrent position: (" << currentRow << ", " << currentCol << ")\n";

        auto legalMoves = board.getLegalMoves(currentRow, currentCol);
        if (legalMoves.empty()) {
            std::cout << "No more legal moves available. Tour ended.\n";
            break;
        }

        maxObservedMoves = std::max(maxObservedMoves, static_cast<int>(legalMoves.size()));

        std::cout << "Possible moves:\n";
        for (std::size_t i = 0; i < legalMoves.size(); ++i) {
            std::cout << "  [" << i + 1 << "] (" << legalMoves[i].first << ", " << legalMoves[i].second << ")\n";
        }
        std::cout << "Enter next move as 'row col' (or type 'q' to stop): ";

        if (!std::getline(std::cin, line)) {
            std::cout << "\nInput stream closed. Ending play.\n";
            break;
        }
        if (line.empty()) {
            continue;
        }
        if (line == "q" || line == "Q") {
            std::cout << "Ending manual play.\n";
            break;
        }

        std::istringstream iss(line);
        int nextRow = 0;
        int nextCol = 0;
        if (!(iss >> nextRow >> nextCol)) {
            std::cout << "Invalid input. Please enter two integers.\n";
            continue;
        }

        const bool isLegal = std::find_if(
            legalMoves.begin(), legalMoves.end(),
            [nextRow, nextCol](const auto& move) { return move.first == nextRow && move.second == nextCol; }
        ) != legalMoves.end();

        if (!isLegal) {
            std::cout << "That square is not a legal knight move from the current position.\n";
            continue;
        }

        if (!board.makeMove(nextRow, nextCol)) {
            std::cout << "That square has already been visited. Try again.\n";
            continue;
        }

        currentRow = nextRow;
        currentCol = nextCol;
        ++movesAttempted_;
        finalPosition_ = board.getMoveNumber(currentRow, currentCol);
    }

    if (movesAttempted_ >= maxMoves && movesAttempted_ < totalSquares) {
        std::cout << "Reached move limit (" << maxMoves << "). Tour ended.\n";
    }

    board.display();

    summary.maxPossibleMoves = maxObservedMoves;
    summary.solved = (movesAttempted_ == totalSquares);
    completed_ = summary.solved;

    return summary;
}