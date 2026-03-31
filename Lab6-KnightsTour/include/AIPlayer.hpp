#ifndef AI_PLAYER_HPP
#define AI_PLAYER_HPP

#include "BinaryTree.hpp"
#include "KnightTourBoard.hpp"
#include "Player.hpp"
#include "ScoredMove.hpp"

#include <vector>

// AI-controlled knight’s tour player implementing Warnsdorff-inspired scoring.
class AIPlayer : public Player {
public:
    AIPlayer();
    ~AIPlayer() override;

    const char* name() const override;
    // Runs the automated tour search starting at (startRow,startCol).
    SolveSummary solveTour(KnightTourBoard& board, int startRow, int startCol, int maxMoves) override;

protected:
    void resetStats() override;

private:
    // Uses Warnsdorff heuristic to score candidate moves.
    // Score should reflect the number of legal moves available from the candidate position.
    double calculateWarnsdorffScore(const KnightTourBoard& board, int row, int col) const;

    /// Builds scored move list (lower score == better move).
    std::vector<ScoredMove> scoreMoves(const KnightTourBoard& board,
                                       const std::vector<std::pair<int, int>>& legalMoves) const;
};

#endif // AI_PLAYER_HPP