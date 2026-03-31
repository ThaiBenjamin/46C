#include "BinaryTree.hpp"

#include <gtest/gtest.h>

// 3) Best- and worst-case height patterns (smaller N for a quick check)
TEST(BinaryTreePerf, BestWorstCaseHeights) {
    const int nodes = 32; // small and quick

    // Worst case: ascending inserts -> a chain of nodes => height == nodes - 1
    BSTTree worst;
    for (int i = 0; i < nodes; ++i) worst.insert(i);
    EXPECT_EQ(worst.getHeight(), nodes - 1);

    // Near-best: balanced insertion pattern used in the Java solution
    BSTTree best;
    for (int divisor = nodes / 2; divisor >= 1; divisor /= 2) {
        for (int value = divisor; value < nodes; value += divisor) best.insert(value);
    }
    int expected_best = -1;
    for (int n = nodes; n > 1; n /= 2) expected_best++;
    EXPECT_EQ(best.getHeight(), expected_best);
}