// Tests for Introduction Lab (C++) mirroring the provided Java autograder

#include <gtest/gtest.h>

// Access Bag::contents for deterministic setup like the Java tests
#define private public
#include "Bag.hpp"
#undef private
#include "Token.hpp"

#include <string>
#include <vector>

namespace {

// Helper to set up a Bag with deterministic contents and compute expectations
struct BagSetupResult {
    int sum{};
    int num_high{};
    int first_green{-1};
};

BagSetupResult setupBagWithKnownContents(Bag& bag) {
    static const int NUM_TOKENS = 16;
    static const std::vector<std::string> colors = {
        "Red", "Yellow", "Green", "Cyan", "Green",
        "Blue", "Violet", "Green"
    };

    BagSetupResult r;
    // The bag was constructed with NUM_TOKENS size; fill deterministically
    for (int i = 0; i < NUM_TOKENS; ++i) {
        int value = i % Token::MAX_VALUE; // MAX_VALUE is 10
        const std::string& color = colors[static_cast<size_t>(i) % colors.size()];

        bag.contents[static_cast<size_t>(i)].setValue(value);
        bag.contents[static_cast<size_t>(i)].setColor(color);

        r.sum += value;
        if (value > Token::MAX_VALUE / 2)
            r.num_high++;
        if (color == "Green" && r.first_green < 0)
            r.first_green = i;
    }
    return r;
}

} // namespace

// --- Token tests ---

TEST(TokenTests, GetValueReturnsAsConstructed) {
    Token t1{"None", 1};
    Token t10{"None", 10};
    EXPECT_EQ(1, t1.getValue());
    EXPECT_EQ(10, t10.getValue());
}

TEST(TokenTests, SetValueChangesValue) {
    Token t{"None", 1};
    t.setValue(6);
    EXPECT_EQ(6, t.getValue());
}

// TODO: Add additional tests for the Token class
TEST(TokenTests, GetColorReturnsAsConstructed) {
    Token t{"Green", 5};
    EXPECT_EQ("Green", t.getColor());
}

TEST(TokenTests, SetColorChangesColor) {
    Token t{"Red", 3};
    t.setColor("Blue");
    EXPECT_EQ("Blue", t.getColor());
}

TEST(TokenTests, ToStringIsNonEmpty) {
    Token t{"Yellow", 7};
    EXPECT_FALSE(t.toString().empty());
}
// --- Bag tests ---
// TODO: Add your own tests for the Bag class
TEST(BagTests, SumMatchesExpected) {
    Bag bag(16);
    auto expected = setupBagWithKnownContents(bag);
    EXPECT_EQ(expected.sum, bag.addTokens());
}
TEST(BagTests, NumHighTokensMatchesExpected) {
    Bag bag(16);
    auto expected = setupBagWithKnownContents(bag);
    EXPECT_EQ(expected.num_high, bag.highValueTokens());
}
TEST(BagTests, FirstGreenIndexMatchesExpected) {
    Bag bag(16);
    auto expected = setupBagWithKnownContents(bag);
    EXPECT_EQ(expected.first_green, bag.firstGreen());
}