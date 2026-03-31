#include "KnightTourGame.hpp"

#include "AIPlayer.hpp"
#include "HumanPlayer.hpp"

#include <iomanip>
#include <iostream>
#include <limits>

KnightTourGame::KnightTourGame(int boardSize) : boardSize_(boardSize) {
    setBoardSize(boardSize);
}

void KnightTourGame::playHumanMode() {
    std::cout << "\n=== INTERACTIVE KNIGHT'S TOUR (SIMPLIFIED) ===\n";
    std::cout << "Enter desired board size (5 - 16): ";

    int size = boardSize_;
    while (!(std::cin >> size) || size < 5 || size > 16) {
        std::cout << "Enter a valid size between 5 and 16: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    setBoardSize(size);

    // Position start = getStartingPosition();
    Position start = getOptimalStartingPosition(boardSize_);
    HumanPlayer humanPlayer;
    TourResult result = testPlayer(&humanPlayer, start);

    std::cout << "\n--- HUMAN RUN SUMMARY ---\n";
    std::cout << "Player: " << result.playerName << '\n';
    std::cout << "Start : " << start.toString() << '\n';
    std::cout << "Solved: " << (result.summary.solved ? "YES" : "NO") << '\n';
    std::cout << "Max possible moves from any step: " << result.summary.maxPossibleMoves << '\n';
}

void KnightTourGame::compareBSTPerformanceAcrossSizes() {
    std::cout << "\n=== BST VS LLRB PERFORMANCE ===\n";
    std::cout << "Collecting solveTour stats across multiple board sizes.\n";

    const std::vector<int> boardSizes = {8, 16, 32, 64, 128, 256, 512, 1024};
    std::vector<SummaryMetrics> summaries;
    summaries.reserve(boardSizes.size());

    const int originalSize = boardSize_;

    for (int size : boardSizes) {
        setBoardSize(size);
        AIPlayer aiPlayer;
        Position startPos = getOptimalStartingPosition(size);

        std::cout << "\nRunning " << size << "x" << size << " board...\n";
        TourResult result = testPlayer(&aiPlayer, startPos);
        summaries.push_back(SummaryMetrics{size, result.summary});
        std::cout << "Completed: " << (result.summary.solved ? "YES" : "NO") << '\n';
    }

    setBoardSize(originalSize);
    printSummaryTable(summaries);
}

void KnightTourGame::setBoardSize(int size) {
    boardSize_ = std::max(5, size);
    maxMoves_ = boardSize_ * boardSize_ * 2;
}

KnightTourGame::TourResult KnightTourGame::testPlayer(Player* player, const Position& startPos) {
    TourResult result;
    result.playerName = player->name();

    KnightTourBoard board(boardSize_);
    SolveSummary summary = player->solveTour(board, startPos.row, startPos.col, maxMoves_);

    result.summary = summary;
    result.movesTaken = player->getMovesAttempted();
    result.finalPosition = player->getFinalPosition();

    return result;
}

Position KnightTourGame::getStartingPosition() const {
    return Position(0, 0);
}

Position KnightTourGame::getOptimalStartingPosition(int size) const {
    const int center = size / 2;
    return Position(center, center);
}

void KnightTourGame::printSummaryTable(const std::vector<SummaryMetrics>& summaries) const {
    if (summaries.empty()) {
        std::cout << "\nNo results to display.\n";
        return;
    }

    std::cout << "\n=== SOLVETOUR METRICS ===\n";
    std::cout << std::left << std::setw(10) << "Board"
              << std::setw(10) << "Solved"
              << std::setw(15) << "Max Moves"
              << std::setw(15) << "BST Avg"
              << std::setw(12) << "BST Max"
              << std::setw(15) << "LLRB Avg"
              << std::setw(12) << "LLRB Max"
              << '\n';
    std::cout << std::string(89, '-') << '\n';

    for (const auto& entry : summaries) {
        const SolveSummary& s = entry.summary;
        std::cout << std::left << std::setw(10) << (std::to_string(entry.boardSize) + "x" + std::to_string(entry.boardSize))
                  << std::setw(10) << (s.solved ? "YES" : "NO")
                  << std::setw(15) << s.maxPossibleMoves
                  << std::setw(15) << std::fixed << std::setprecision(2) << s.bstAverageHeight
                  << std::setw(12) << s.bstMaxHeight
                  << std::setw(15) << s.llrbAverageHeight
                  << std::setw(12) << s.llrbMaxHeight
                  << std::defaultfloat << std::setprecision(6) << '\n';
    }
}