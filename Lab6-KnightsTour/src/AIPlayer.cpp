#include "AIPlayer.hpp"

#include <algorithm>

AIPlayer::AIPlayer() {
    resetStats();
}

AIPlayer::~AIPlayer() = default;

const char* AIPlayer::name() const {
    return "Warnsdorff AI";
}

void AIPlayer::resetStats() {
    Player::resetStats();
}

double AIPlayer::calculateWarnsdorffScore(const KnightTourBoard& board, int row, int col) const {
    // TODO: implement calculateWarnsdorffScore to return the number of legal moves from the given position
    return board.getLegalMoves(row, col).size();
}

std::vector<ScoredMove> AIPlayer::scoreMoves(
    const KnightTourBoard& board,
    const std::vector<std::pair<int, int>>& legalMoves) const {
    // TODO: implement scoreMoves to return a vector of ScoredMove objects 
    // for the legal moves at the current position
    std::vector<ScoredMove> scoredMoves;
    scoredMoves.reserve(legalMoves.size());

    for (const auto& move : legalMoves) {
        int row = move.first;
        int col = move.second;

        double score = board.getLegalMoves(row, col).size();

        scoredMoves.emplace_back(row, col, score);
    }

    return scoredMoves;
    
}

SolveSummary AIPlayer::solveTour(
    KnightTourBoard& board, int startRow, int startCol, int maxMoves) {
    SolveSummary summary{};
    resetStats();
    board.reset();

    int currRow = startRow;
    int currCol = startCol;

    if (!board.makeMove(currRow, currCol))
        return summary;

    int movesMade = 1;
    double bstHeightSum = 0;
    double llrbHeightSum = 0;
    int heightSamples = 0;

    while (movesMade < maxMoves) {
        auto legalMoves = board.getLegalMoves(currRow, currCol);

        if (legalMoves.empty())
            break;

        summary.maxPossibleMoves = std::max(summary.maxPossibleMoves, (int)legalMoves.size());

        auto scoredMoves = scoreMoves(board, legalMoves);

        BinaryTree<ScoredMove> bst(BinaryTree<ScoredMove>::TreeType::BST);
        BinaryTree<ScoredMove> llrb(BinaryTree<ScoredMove>::TreeType::LLRB);

        for (const auto& sm : scoredMoves) {
            bst.insert(sm);
            llrb.insert(sm);
        }

        int bstHeight = bst.getHeight();
        int llrbHeight = llrb.getHeight();
        bstHeightSum += bstHeight;
        llrbHeightSum += llrbHeight;
        heightSamples++;

        summary.bstMaxHeight = std::max(summary.bstMaxHeight, bstHeight);
        summary.llrbMaxHeight = std::max(summary.llrbMaxHeight, llrbHeight);

        const ScoredMove* bestMovePtr = bst.findMin();
        if (!bestMovePtr)
            break;

        currRow = bestMovePtr->row;
        currCol = bestMovePtr->col;

        if (!board.makeMove(currRow, currCol))
            break;

        movesMade++;
    }

    summary.solved = (movesMade == (board.getSize() * board.getSize()));
    if (heightSamples > 0) {
        summary.bstAverageHeight = bstHeightSum / heightSamples;
        summary.llrbAverageHeight = llrbHeightSum / heightSamples;
    }

    movesAttempted_ = movesMade;
    completed_ = summary.solved;
    return summary;
}