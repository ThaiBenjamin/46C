#include "BinaryTree.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include <set>
#include <iomanip>
#include <climits>

int main() {
    // Define a set of 15 values to insert into both trees
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55, 65, 75, 85};
    
    std::cout << "=== Testing with original order ===\n";
    std::cout << "Values to insert: ";
    for (int val : values) {
        std::cout << val << " ";
    }
    std::cout << "\n\n";
    
    // Create 2 trees with different types
    BSTTree bstTree;
    HeapTree heapTree;
    
    // Insert values in the same order into both trees
    for (int val : values) {
        bstTree.insert(val);
        heapTree.insert(val);
    }
    
    // Visualize both trees
    std::cout << "BST Tree (Original Order):\n";
    std::cout << "Tree Type: " << bstTree.typeName() << "\n";
    std::cout << "Size: " << bstTree.getSize() << ", Height: " << bstTree.getHeight() << "\n";
    std::cout << bstTree.visualizeTree() << "\n";
    
    std::cout << "Max Heap Tree (Original Order):\n";
    std::cout << "Tree Type: " << heapTree.typeName() << "\n";
    std::cout << "Size: " << heapTree.getSize() << ", Height: " << heapTree.getHeight() << "\n";
    std::cout << heapTree.visualizeTree() << "\n";
    
    // Use bstSort and heapSort instead of in-order traversal
    std::cout << "BST sorted values: ";
    try {
        std::vector<int> bstSorted = bstTree.bstSort();
        for (int val : bstSorted) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
    
    std::cout << "Heap sorted values: ";
    try {
        std::vector<int> heapSorted = heapTree.heapSort();
        for (int val : heapSorted) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
    std::cout << "\n";
    
    // Now randomize the order and test again
    std::cout << "=== Testing with randomized order ===\n";
    
    // Create a copy of values and shuffle it
    std::vector<int> randomizedValues = values;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(randomizedValues.begin(), randomizedValues.end(), gen);
    
    std::cout << "Randomized values: ";
    for (int val : randomizedValues) {
        std::cout << val << " ";
    }
    std::cout << "\n\n";
    
    // Create new trees with randomized insertion order
    BSTTree bstTreeRandom;
    HeapTree heapTreeRandom;
    
    // Insert values in randomized order into both trees
    for (int val : randomizedValues) {
        bstTreeRandom.insert(val);
        heapTreeRandom.insert(val);
    }
    
    // Visualize both trees
    std::cout << "BST Tree (Randomized Order):\n";
    std::cout << "Size: " << bstTreeRandom.getSize() << ", Height: " << bstTreeRandom.getHeight() << "\n";
    std::cout << bstTreeRandom.visualizeTree() << "\n";
    
    std::cout << "Max Heap Tree (Randomized Order):\n";
    std::cout << "Size: " << heapTreeRandom.getSize() << ", Height: " << heapTreeRandom.getHeight() << "\n";
    std::cout << heapTreeRandom.visualizeTree() << "\n";
    
    // Use bstSort and heapSort for randomized trees
    std::cout << "BST sorted values (Randomized): ";
    try {
        std::vector<int> bstSortedRandom = bstTreeRandom.bstSort();
        for (int val : bstSortedRandom) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
    
    std::cout << "Heap sorted values (Randomized): ";
    try {
        std::vector<int> heapSortedRandom = heapTreeRandom.heapSort();
        for (int val : heapSortedRandom) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
    std::cout << "\n";
    
    // Test insert and findNode for both BST and Heap
    std::cout << "=== Testing insert and findNode functionality ===\n";
    
    // Test BST
    std::cout << "BST Tests:\n";
    
    // Test finding existing values
    auto bstNode50 = bstTree.findNode(50);
    if (bstNode50 && bstNode50->item == 50) {
        std::cout << "  findNode(50) in BST: FOUND ✓\n";
    } else {
        std::cout << "  findNode(50) in BST: NOT FOUND ✗\n";
    }
    
    auto bstNode25 = bstTree.findNode(25);
    if (bstNode25 && bstNode25->item == 25) {
        std::cout << "  findNode(25) in BST: FOUND ✓\n";
    } else {
        std::cout << "  findNode(25) in BST: NOT FOUND ✗\n";
    }
    
    // Test finding non-existing value
    auto bstNode99 = bstTree.findNode(99);
    if (!bstNode99) {
        std::cout << "  findNode(99) in BST: NOT FOUND (correct) ✓\n";
    } else {
        std::cout << "  findNode(99) in BST: FOUND (error) ✗\n";
    }
    
    // Test inserting duplicate
    int originalSize = bstTree.getSize();
    bstTree.insert(50); // Duplicate
    if (bstTree.getSize() == originalSize) {
        std::cout << "  insert(50) duplicate in BST: IGNORED (correct) ✓\n";
    } else {
        std::cout << "  insert(50) duplicate in BST: ADDED (error) ✗\n";
    }
    
    // Test Heap
    std::cout << "\nHeap Tests:\n";
    
    // Test finding existing values
    auto heapNode50 = heapTree.findNode(50);
    if (heapNode50 && heapNode50->item == 50) {
        std::cout << "  findNode(50) in Heap: FOUND ✓\n";
    } else {
        std::cout << "  findNode(50) in Heap: NOT FOUND ✗\n";
    }
    
    auto heapNode25 = heapTree.findNode(25);
    if (heapNode25 && heapNode25->item == 25) {
        std::cout << "  findNode(25) in Heap: FOUND ✓\n";
    } else {
        std::cout << "  findNode(25) in Heap: NOT FOUND ✗\n";
    }
    
    // Test finding non-existing value
    auto heapNode99 = heapTree.findNode(99);
    if (!heapNode99) {
        std::cout << "  findNode(99) in Heap: NOT FOUND (correct) ✓\n";
    } else {
        std::cout << "  findNode(99) in Heap: FOUND (error) ✗\n";
    }
    
    // Test inserting new value
    heapTree.insert(90);
    auto heapNode90 = heapTree.findNode(90);
    if (heapNode90 && heapNode90->item == 90) {
        std::cout << "  insert(90) then findNode(90) in Heap: SUCCESS ✓\n";
    } else {
        std::cout << "  insert(90) then findNode(90) in Heap: FAILED ✗\n";
    }
    
    std::cout << "\n=== Testing Sorting Functions ===\n";
    
    // Create a new heap for sorting demonstration
    HeapTree heapForSorting;
    std::vector<int> testValues = {40, 30, 50, 20, 35, 45, 60, 10, 25, 33};
    
    std::cout << "Inserting values for sorting demonstration: ";
    for (int val : testValues) {
        std::cout << val << " ";
        heapForSorting.insert(val);
    }
    std::cout << "\n";
    
    std::cout << "Heap before sorting:\n" << heapForSorting.visualizeTree() << "\n";
    
    // Use the heapSort function
    try {
        std::vector<int> heapSortedValues = heapForSorting.heapSort();
        
        std::cout << "Heap sort complete! Values sorted in ascending order: ";
        for (int val : heapSortedValues) {
            std::cout << val << " ";
        }
        std::cout << "\n";
        
        // Show that original heap is preserved
        std::cout << "Original heap after sorting (preserved):\n" << heapForSorting.visualizeTree() << "\n";
        
    } catch (const std::runtime_error& e) {
        std::cout << "Error during heap sort: " << e.what() << "\n";
    }
    
    // Create a BST for sorting demonstration
    BSTTree bstForSorting;
    
    std::cout << "Creating BST with same values for comparison:\n";
    for (int val : testValues) {
        bstForSorting.insert(val);
    }
    
    std::cout << "BST visualization:\n" << bstForSorting.visualizeTree() << "\n";
    
    try {
        std::vector<int> bstSortedValues = bstForSorting.bstSort();
        
        std::cout << "BST sort complete! Values sorted in ascending order: ";
        for (int val : bstSortedValues) {
            std::cout << val << " ";
        }
        std::cout << "\n";
        
    } catch (const std::runtime_error& e) {
        std::cout << "Error during BST sort: " << e.what() << "\n";
    }

    // Using Static Functions for Random Tree Analysis ===
    std::cout << "\n=== Large Scale Random Tree Analysis ===\n";
    
    const int NUM_NODES = 1023;
    const int NUM_TRIALS = 100;
    
    // Theoretical height calculations
    double theoreticalMinHeightBST = std::log2(NUM_NODES + 1) - 1;  // Balanced BST
    int theoreticalMaxHeightBST = NUM_NODES - 1;                    // Degenerate BST
    double theoreticalMinHeightHeap = static_cast<int>(std::floor(std::log2(NUM_NODES)));        // Complete tree
    double theoreticalMaxHeightHeap = static_cast<int>(std::floor(std::log2(NUM_NODES)));   // Complete tree
    
    std::cout << "=== Theoretical Height Analysis for " << NUM_NODES << " nodes ===\n";
    std::cout << "BST Heights:\n";
    std::cout << "  Theoretical Min (balanced): " << static_cast<int>(theoreticalMinHeightBST) << "\n";
    std::cout << "  Theoretical Max (degenerate): " << theoreticalMaxHeightBST << "\n";
    std::cout << "Heap Heights:\n";
    std::cout << "  Theoretical Min (complete tree): " << static_cast<int>(theoreticalMinHeightHeap) << "\n";
    std::cout << "  Theoretical Max (complete tree): " << static_cast<int>(theoreticalMaxHeightHeap) << "\n\n";
    
    // Use the existing analyzeRandomTreeHeights function for BSTs
    std::cout << "=== BST Random Tree Height Analysis ===\n";
    BSTTree::analyzeRandomTreeHeights(NUM_NODES, NUM_TRIALS);
    
    // Manual analysis for heaps since we need to create heap trees specifically
    std::cout << "\n=== Heap Random Tree Height Analysis ===\n";
    
    int heapMinHeight = INT_MAX;
    int heapMaxHeight = 0;
    long long heapHeightSum = 0;
    
    // Generate random values for heap analysis
    std::set<int> uniqueNumbers;
    std::uniform_int_distribution<int> dist(1, 10000);
    
    while (static_cast<int>(uniqueNumbers.size()) < NUM_NODES) {
        uniqueNumbers.insert(dist(gen));
    }
    
    std::vector<int> randomNumbers(uniqueNumbers.begin(), uniqueNumbers.end());
    
    std::cout << "Running " << NUM_TRIALS << " trials with " << NUM_NODES << " random heap insertions:\n";
    
    for (int trial = 0; trial < NUM_TRIALS; trial++) {
        // Shuffle the numbers for this trial
        std::shuffle(randomNumbers.begin(), randomNumbers.end(), gen);
        
        // Create Heap
        HeapTree heapLarge;
        for (int num : randomNumbers) {
            heapLarge.insert(num);
        }
        
        int heapHeight = heapLarge.getHeight();
        
        // Update Heap statistics
        heapMinHeight = std::min(heapMinHeight, heapHeight);
        heapMaxHeight = std::max(heapMaxHeight, heapHeight);
        heapHeightSum += heapHeight;
        
        // std::cout << "Trial " << (trial + 1) << ": Heap height = " << heapHeight << "\n";
    }
    
    double heapAvgHeight = static_cast<double>(heapHeightSum) / NUM_TRIALS;
    
    std::cout << NUM_TRIALS << " " << NUM_NODES << "-node heap trees: "
              << "min_height=" << heapMinHeight
              << ", max_height=" << heapMaxHeight
              << ", avg_height=" << std::fixed << std::setprecision(1) << heapAvgHeight << "\n";

    // Sorted Insertion Test ===
    std::cout << "\n=== Sorted Insertion Test (1023 values) ===\n";
    
    const int SORTED_TEST_SIZE = 1023;
    
    // Generate sorted values 1, 2, 3, ..., 1023
    std::vector<int> sortedValues;
    for (int i = 1; i <= SORTED_TEST_SIZE; ++i) {
        sortedValues.push_back(i);
    }
    
    std::cout << "Inserting values 1 through " << SORTED_TEST_SIZE << " in sorted order...\n";
    
    // Create trees for sorted insertion
    BSTTree bstSortedLarge;
    HeapTree heapSortedLarge;
    
    // Insert sorted values
    for (int val : sortedValues) {
        bstSortedLarge.insert(val);
        heapSortedLarge.insert(val);
    }
    
    // Measure and report heights
    int bstSortedHeight = bstSortedLarge.getHeight();
    int heapSortedHeight = heapSortedLarge.getHeight();
    
    std::cout << "Results for " << SORTED_TEST_SIZE << " sorted insertions:\n";
    std::cout << "  BST Height: " << bstSortedHeight << " (worst case - degenerate tree)\n";
    std::cout << "  Heap Height: " << heapSortedHeight << " (optimal - complete tree)\n";
    
    // Calculate theoretical bounds
    double theoreticalOptimalHeight = std::log2(SORTED_TEST_SIZE + 1) - 1;
    int theoreticalWorstHeight = SORTED_TEST_SIZE - 1;
    
    std::cout << "\nComparison with theoretical bounds:\n";
    std::cout << "  Theoretical optimal height: " << static_cast<int>(theoreticalOptimalHeight) << "\n";
    std::cout << "  Theoretical worst height: " << theoreticalWorstHeight << "\n";
    std::cout << "  BST achieved: " << bstSortedHeight << " (matches worst case: " << (bstSortedHeight == theoreticalWorstHeight ? "YES" : "NO") << ")\n";
    std::cout << "  Heap achieved: " << heapSortedHeight << " (close to optimal: " << (heapSortedHeight <= static_cast<int>(theoreticalOptimalHeight) + 1 ? "YES" : "NO") << ")\n";
    
    return 0;
}