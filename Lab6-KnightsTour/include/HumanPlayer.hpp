#ifndef HUMANPLAYER_HPP
#define HUMANPLAYER_HPP

#include "Player.hpp"

class HumanPlayer : public Player {
public:
    HumanPlayer();
    ~HumanPlayer() override;

    const char* name() const override;
    SolveSummary solveTour(KnightTourBoard& board, int startRow, int startCol, int maxMoves) override;
};

#endif // HUMANPLAYER_HPP