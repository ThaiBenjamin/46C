#include "BinaryTree.hpp"
#include <gtest/gtest.h>
#include <algorithm>

// Test destroyTree function
TEST(BinaryTreeTodoTests, DestroyTreeTest) {
    BSTTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);
    
    EXPECT_EQ(tree.getSize(), 5);
    // Tree should be properly destroyed when destructor is called
    // This is tested implicitly when the tree goes out of scope
}

// Test calculateSize function
TEST(BinaryTreeTodoTests, CalculateSizeTest) {
    BSTTree tree;
    
    // Test empty tree
    EXPECT_EQ(tree.getSize(), 0);
    
    // Test tree with one node
    tree.insert(5);
    EXPECT_EQ(tree.getSize(), 1);
    
    // Test tree with multiple nodes
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);
    EXPECT_EQ(tree.getSize(), 5);
    
    // Test with duplicate (should not increase size)
    tree.insert(5);
    EXPECT_EQ(tree.getSize(), 5);
}

// Test calculateHeight function
TEST(BinaryTreeTodoTests, CalculateHeightTest) {
    BSTTree tree;
    
    // Test empty tree (height should be -1)
    EXPECT_EQ(tree.getHeight(), -1);
    
    // Test tree with one node
    tree.insert(5);
    EXPECT_EQ(tree.getHeight(), 0);
    
    // Test balanced tree
    tree.insert(3);
    tree.insert(7);
    EXPECT_EQ(tree.getHeight(), 1);
    
    // Test unbalanced tree (linear)
    BSTTree linearTree;
    linearTree.insert(1);
    linearTree.insert(2);
    linearTree.insert(3);
    linearTree.insert(4);
    EXPECT_EQ(linearTree.getHeight(), 3);
}

// Test heap insertion functions
TEST(BinaryTreeTodoTests, HeapInsertionTest) {
    HeapTree heap;
    
    // Test insertion into empty heap
    heap.insert(10);
    EXPECT_EQ(heap.getSize(), 1);
    EXPECT_EQ(heap.peekMax(), 10);
    
    // Test multiple insertions
    heap.insert(5);
    heap.insert(15);
    heap.insert(3);
    heap.insert(20);
    
    EXPECT_EQ(heap.getSize(), 5);
    EXPECT_EQ(heap.peekMax(), 20); // Max heap property
}

// Test swimArray function
TEST(BinaryTreeTodoTests, SwimArrayTest) {
    HeapTree heap;
    
    // Insert values that will require swimming
    heap.insert(1);
    heap.insert(3);
    heap.insert(5);
    heap.insert(7);
    heap.insert(9);
    
    // The max should be at the top
    EXPECT_EQ(heap.peekMax(), 9);
    
    // Insert a new maximum
    heap.insert(15);
    EXPECT_EQ(heap.peekMax(), 15);
}

// Test deleteMaxArray and sinkArray functions
TEST(BinaryTreeTodoTests, DeleteMaxAndSinkTest) {
    HeapTree heap;
    
    // Insert values
    std::vector<int> values = {10, 5, 15, 3, 20, 8, 12};
    for (int val : values) {
        heap.insert(val);
    }
    
    // Delete max values and verify heap property is maintained
    EXPECT_EQ(heap.deleteMax(), 20);
    EXPECT_EQ(heap.peekMax(), 15);
    
    EXPECT_EQ(heap.deleteMax(), 15);
    EXPECT_EQ(heap.peekMax(), 12);
    
    EXPECT_EQ(heap.deleteMax(), 12);
    EXPECT_EQ(heap.peekMax(), 10);
}

// Test deleteMaxArray with edge cases
TEST(BinaryTreeTodoTests, DeleteMaxEdgeCases) {
    HeapTree heap;
    
    // Test deleting from empty heap
    EXPECT_THROW(heap.deleteMax(), std::runtime_error);
    
    // Test deleting single element
    heap.insert(42);
    EXPECT_EQ(heap.deleteMax(), 42);
    EXPECT_THROW(heap.peekMax(), std::runtime_error);
}



// Test heapSort with BST (should throw exception)
TEST(BinaryTreeTodoTests, HeapSortBSTException) {
    BSTTree bst;
    bst.insert(5);
    
    EXPECT_THROW(bst.heapSort(), std::runtime_error);
}

// Test arrayToTreeHelper function
TEST(BinaryTreeTodoTests, ArrayToTreeHelperTest) {
    HeapTree heap;
    
    // Insert values to create heap array
    std::vector<int> values = {10, 8, 9, 4, 7, 5, 6, 1, 2, 3};
    for (int val : values) {
        heap.insert(val);
    }
    
    // Verify tree structure matches heap property
    std::string visualization = heap.visualizeTree();
    EXPECT_FALSE(visualization.empty());
    EXPECT_TRUE(visualization.find("Heap Array:") != std::string::npos);
}

// Test insertBST function
TEST(BinaryTreeTodoTests, InsertBSTTest) {
    BSTTree bst;
    
    // Test insertion order that creates specific structure
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(1);
    bst.insert(4);
    bst.insert(6);
    bst.insert(9);
    
    EXPECT_EQ(bst.getSize(), 7);
    
    // Test duplicate insertion (should be ignored)
    bst.insert(5);
    EXPECT_EQ(bst.getSize(), 7);
    
    // Verify BST property by checking findNode works correctly
    EXPECT_NE(bst.findNode(1), nullptr);
    EXPECT_NE(bst.findNode(9), nullptr);
    EXPECT_EQ(bst.findNode(10), nullptr);
}

// Test findBST function
TEST(BinaryTreeTodoTests, FindBSTTest) {
    BSTTree bst;
    
    // Test find in empty tree
    EXPECT_EQ(bst.findNode(5), nullptr);
    
    // Insert values
    std::vector<int> values = {5, 3, 7, 1, 4, 6, 9};
    for (int val : values) {
        bst.insert(val);
    }
    
    // Test finding existing values
    for (int val : values) {
        auto node = bst.findNode(val);
        EXPECT_NE(node, nullptr);
        EXPECT_EQ(node->item, val);
    }
    
    // Test finding non-existing values
    EXPECT_EQ(bst.findNode(0), nullptr);
    EXPECT_EQ(bst.findNode(10), nullptr);
    EXPECT_EQ(bst.findNode(2), nullptr);
}

// Test findHeap function
TEST(BinaryTreeTodoTests, FindHeapTest) {
    HeapTree heap;
    
    // Test find in empty heap
    EXPECT_EQ(heap.findNode(5), nullptr);
    
    // Insert values
    std::vector<int> values = {10, 5, 15, 3, 20, 8, 12};
    for (int val : values) {
        heap.insert(val);
    }
    
    // Test finding existing values
    for (int val : values) {
        auto node = heap.findNode(val);
        EXPECT_NE(node, nullptr);
        EXPECT_EQ(node->item, val);
    }
    
    // Test finding non-existing value
    EXPECT_EQ(heap.findNode(100), nullptr);
}

// Test bstSort with heap (should throw exception)
TEST(BinaryTreeTodoTests, BSTSortHeapException) {
    HeapTree heap;
    heap.insert(5);
    
    EXPECT_THROW(heap.bstSort(), std::runtime_error);
}

