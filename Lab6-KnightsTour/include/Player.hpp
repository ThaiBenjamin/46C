#ifndef PLAYER_HPP
#define PLAYER_HPP

class KnightTourBoard;

struct SolveSummary {
    bool solved = false;
    int maxPossibleMoves = 0;
    double bstAverageHeight = 0.0;
    int bstMaxHeight = 0;
    double llrbAverageHeight = 0.0;
    int llrbMaxHeight = 0;
};

class Player {
public:
    virtual ~Player() = default;

    virtual const char* name() const = 0;
    virtual SolveSummary solveTour(KnightTourBoard& board, int startRow, int startCol, int maxMoves) = 0;

    virtual void resetStats() {
        movesAttempted_ = 0;
        completed_ = false;
        finalPosition_ = 0;
    }

    int getMovesAttempted() const { return movesAttempted_; }
    bool completedTour() const { return completed_; }
    int getFinalPosition() const { return finalPosition_; }

protected:
    int movesAttempted_ = 0;
    bool completed_ = false;
    int finalPosition_ = 0;
};

#endif // PLAYER_HPP