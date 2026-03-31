#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <vector>

#define private public
#include "BinaryTree.hpp"
#undef private
#include "KnightTourBoard.hpp"
#include "ScoredMove.hpp"
#include "AIPlayer.hpp"
#include <sstream>

TEST(KnightTourBoardTest, LegalMovesFromCenterIncludeAllOffsets) {
    KnightTourBoard board(5);
    ASSERT_TRUE(board.makeMove(2, 2));

    auto moves = board.getLegalMoves(2, 2);
    std::sort(moves.begin(), moves.end());

    std::vector<std::pair<int, int>> expected = {
        {0, 1}, {0, 3}, {1, 0}, {1, 4},
        {3, 0}, {3, 4}, {4, 1}, {4, 3}
    };
    std::sort(expected.begin(), expected.end());

    EXPECT_EQ(expected, moves);
}

TEST(KnightTourBoardTest, LegalMovesFromCornerStayInBounds) {
    KnightTourBoard board(5);
    ASSERT_TRUE(board.makeMove(0, 0));

    auto moves = board.getLegalMoves(0, 0);
    std::sort(moves.begin(), moves.end());
    std::vector<std::pair<int, int>> expected = {{1, 2}, {2, 1}};

    EXPECT_EQ(expected, moves);
}

TEST(KnightTourBoardTest, MakeMoveRejectsVisitedSquares) {
    KnightTourBoard board(5);
    EXPECT_TRUE(board.makeMove(0, 0));
    EXPECT_FALSE(board.makeMove(0, 0));
}

TEST(KnightTourBoardTest, LegalMovesExcludeVisitedSquares) {
    KnightTourBoard board(5);
    ASSERT_TRUE(board.makeMove(2, 2));
    ASSERT_TRUE(board.makeMove(0, 1));

    auto moves = board.getLegalMoves(0, 1);
    auto visited = std::make_pair(2, 2);

    EXPECT_TRUE(std::none_of(moves.begin(), moves.end(),
                             [&](const auto& move) { return move == visited; }));
    for (const auto& move : moves) {
        EXPECT_GE(move.first, 0);
        EXPECT_LT(move.first, board.getSize());
        EXPECT_GE(move.second, 0);
        EXPECT_LT(move.second, board.getSize());
    }
}

TEST(KnightTourBoardTest, CountLegalMovesMatchesMoveVector) {
    KnightTourBoard board(5);
    ASSERT_TRUE(board.makeMove(2, 2));
    auto moves = board.getLegalMoves(2, 2);
    EXPECT_EQ(static_cast<int>(moves.size()), board.countLegalMoves(2, 2));
}

TEST(ScoredMoveTest, ComparisonOperatorsRespectScoreAndCoords) {
    ScoredMove a(1, 2, 0.5);
    ScoredMove b(3, 4, 1.5);
    ScoredMove c(1, 2, 0.5);

    EXPECT_LT(a, b);
    EXPECT_GT(b, a);
    EXPECT_TRUE(a == c);
    EXPECT_FALSE(a == b);
}

TEST(BinaryTreeTest, EmptyTreeHasZeroHeightAndNoMin) {
    BinaryTree<int> tree(BinaryTree<int>::TreeType::BST);
    EXPECT_EQ(-1, tree.getHeight());
    EXPECT_EQ(nullptr, tree.findMin());
}