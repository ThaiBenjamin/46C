#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

#include "InsertionSort.hpp"
#include "SelectionSort.hpp"
#include "QuickOptimized.hpp"
#include "MergeOptimized.hpp"

namespace {
    bool is_sorted(const std::vector<int>& v) {
        return std::is_sorted(v.begin(), v.end());
    }
}

// Test for InsertionSort
TEST(InsertionSort, SortsCorrectly) {
    InsertionSort<int> sorter;

    std::vector<int> data{5, 2, 4, 6, 1, 3};
    sorter.sort(data);
    EXPECT_TRUE(is_sorted(data));
    EXPECT_EQ(data, (std::vector<int>{1, 2, 3, 4, 5, 6}));

    std::vector<int> empty;
    sorter.sort(empty);
    EXPECT_TRUE(is_sorted(empty));

    std::vector<int> single{42};
    sorter.sort(single);
    EXPECT_TRUE(is_sorted(single));
}

TEST(InsertionSort, HandlesAlreadySorted) {
    InsertionSort<int> sorter;
    std::vector<int> data{1, 2, 3, 4, 5};
    sorter.sort(data);
    EXPECT_TRUE(is_sorted(data));
}

TEST(InsertionSort, HandlesReverseSorted) {
    InsertionSort<int> sorter;
    std::vector<int> data{5, 4, 3, 2, 1};
    sorter.sort(data);
    EXPECT_EQ(data, (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(InsertionSort, HandlesDuplicates) {
    InsertionSort<int> sorter;
    std::vector<int> data{3, 1, 2, 3, 1};
    sorter.sort(data);
    EXPECT_EQ(data, (std::vector<int>{1, 1, 2, 3, 3}));
}

TEST(InsertionSort, HandlesNegativeNumbers) {
    InsertionSort<int> sorter;
    std::vector<int> data{-5, -1, -3, 0, 2};
    sorter.sort(data);
    EXPECT_EQ(data, (std::vector<int>{-5, -3, -1, 0, 2}));
}
// Test for SelectionSort
TEST(SelectionSort, SortsCorrectly) {
    SelectionSort<int> sorter;

    std::vector<int> data{64, 25, 12, 22, 11};
    sorter.sort(data);
    EXPECT_TRUE(is_sorted(data));
    EXPECT_EQ(data, (std::vector<int>{11, 12, 22, 25, 64}));

    std::vector<int> empty;
    sorter.sort(empty);
    EXPECT_TRUE(is_sorted(empty));

    std::vector<int> single{42};
    sorter.sort(single);
    EXPECT_TRUE(is_sorted(single));
}

TEST(SelectionSort, HandlesAlreadySorted) {
    SelectionSort<int> sorter;
    std::vector<int> data{1, 2, 3, 4, 5};
    sorter.sort(data);
    EXPECT_TRUE(is_sorted(data));
}

TEST(SelectionSort, HandlesReverseSorted) {
    SelectionSort<int> sorter;
    std::vector<int> data{5, 4, 3, 2, 1};
    sorter.sort(data);
    EXPECT_EQ(data, (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(SelectionSort, HandlesDuplicates) {
    SelectionSort<int> sorter;
    std::vector<int> data{4, 2, 4, 1, 2};
    sorter.sort(data);
    EXPECT_EQ(data, (std::vector<int>{1, 2, 2, 4, 4}));
}

TEST(SelectionSort, HandlesNegativeNumbers) {
    SelectionSort<int> sorter;
    std::vector<int> data{-2, -5, 0, 3, -1};
    sorter.sort(data);
    EXPECT_EQ(data, (std::vector<int>{-5, -2, -1, 0, 3}));
}
// Test for MergeOptimized: merge function
TEST(MergeOptimized, MergeWorksCorrectly) {
    MergeOptimized<int> sorter;

    std::vector<int> data{1, 3, 5, 7, 0, 2, 4, 6};
    std::vector<int> aux(data.size());
    sorter.merge(data, aux, 0, 3, 7);
    EXPECT_TRUE(is_sorted(data));
    EXPECT_EQ(data, (std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7}));
}

// Test for MergeOptimized: sort function
TEST(MergeOptimized, SortsCorrectly) {
    MergeOptimized<int> sorter;

    std::vector<int> data{38, 27, 43, 3, 9, 82, 10};
    sorter.sort(data);
    EXPECT_TRUE(is_sorted(data));
    EXPECT_EQ(data, (std::vector<int>{3, 9, 10, 27, 38, 43, 82}));

    std::vector<int> empty;
    sorter.sort(empty);
    EXPECT_TRUE(is_sorted(empty));

    std::vector<int> single{42};
    sorter.sort(single);
    EXPECT_TRUE(is_sorted(single));
}

TEST(MergeOptimized, HandlesAlreadySorted) {
    MergeOptimized<int> sorter;
    std::vector<int> data{1, 2, 3, 4, 5};
    sorter.sort(data);
    EXPECT_TRUE(is_sorted(data));
}

TEST(MergeOptimized, HandlesReverseSorted) {
    MergeOptimized<int> sorter;
    std::vector<int> data{5, 4, 3, 2, 1};
    sorter.sort(data);
    EXPECT_EQ(data, (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(MergeOptimized, HandlesDuplicates) {
    MergeOptimized<int> sorter;
    std::vector<int> data{2, 1, 2, 1, 2};
    sorter.sort(data);
    EXPECT_EQ(data, (std::vector<int>{1, 1, 2, 2, 2}));
}

TEST(MergeOptimized, HandlesNegativeNumbers) {
    MergeOptimized<int> sorter;
    std::vector<int> data{-10, 5, -3, 0};
    sorter.sort(data);
    EXPECT_EQ(data, (std::vector<int>{-10, -3, 0, 5}));
}

// Test for QuickOptimized: final state on varied inputs
TEST(QuickOptimized, SortsCorrectly) {
    QuickOptimized<int> sorter;

    std::vector<int> data{3, 7, 8, 5, 2, 1, 9, 5, 4};
    sorter.sort(data);
    EXPECT_TRUE(is_sorted(data));
    EXPECT_EQ(data, (std::vector<int>{1, 2, 3, 4, 5, 5, 7, 8, 9}));

    std::vector<int> empty;
    sorter.sort(empty);
    EXPECT_TRUE(is_sorted(empty));

    std::vector<int> single{42};
    sorter.sort(single);
    EXPECT_TRUE(is_sorted(single));
}

TEST(QuickOptimized, HandlesAlreadySorted) {
    QuickOptimized<int> sorter;
    std::vector<int> data{1, 2, 3, 4, 5};
    sorter.sort(data);
    EXPECT_TRUE(is_sorted(data));
}

TEST(QuickOptimized, HandlesReverseSorted) {
    QuickOptimized<int> sorter;
    std::vector<int> data{9, 7, 5, 3, 1};
    sorter.sort(data);
    EXPECT_EQ(data, (std::vector<int>{1, 3, 5, 7, 9}));
}

TEST(QuickOptimized, HandlesDuplicates) {
    QuickOptimized<int> sorter;
    std::vector<int> data{4, 4, 4, 2, 2, 1};
    sorter.sort(data);
    EXPECT_EQ(data, (std::vector<int>{1, 2, 2, 4, 4, 4}));
}

TEST(QuickOptimized, HandlesLargeRandomInput) {
    QuickOptimized<int> sorter;
    std::vector<int> data(1000);

    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(-1000, 1000);
    for (int& x : data) {
        x = dist(rng);
    }

    sorter.sort(data);
    EXPECT_TRUE(is_sorted(data));
}

// Performance tests

