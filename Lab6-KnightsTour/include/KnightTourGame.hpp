#ifndef KNIGHTTOUR_GAME_HPP
#define KNIGHTTOUR_GAME_HPP

#include "KnightTourBoard.hpp"
#include "Player.hpp"

#include <vector>

class KnightTourGame {
public:
    explicit KnightTourGame(int boardSize = 8);
    ~KnightTourGame() = default;

    void playHumanMode();
    void compareBSTPerformanceAcrossSizes();

    void setBoardSize(int size);
    int getBoardSize() const { return boardSize_; }

    struct TourResult {
        std::string playerName;
        SolveSummary summary;
        int movesTaken = 0;
        int finalPosition = 0;
        double solveTime = 0.0;
    };

    TourResult testPlayer(Player* player, const Position& startPos);

private:
    struct SummaryMetrics {
        int boardSize = 0;
        SolveSummary summary{};
    };

    int boardSize_;
    int maxMoves_;

    Position getStartingPosition() const;
    Position getOptimalStartingPosition(int size) const;
    void printSummaryTable(const std::vector<SummaryMetrics>& summaries) const;
};

#endif // KNIGHTTOUR_GAME_HPP