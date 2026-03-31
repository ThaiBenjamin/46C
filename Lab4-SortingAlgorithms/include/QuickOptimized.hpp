#ifndef QUICKOPTIMIZED_HPP
#define QUICKOPTIMIZED_HPP

#include <vector>
#include <string>
#include <random>
#include "Sorter.hpp"

// An optimized implementation of the Quicksort algorithm
template<typename T>
class QuickOptimized : public Sorter<T> {
public:

    QuickOptimized(const std::string& choice = "LO") // Constructor with default pivot choice
        : pivotChoice{choice} {}
    void sort(std::vector<T>& data) override;
    std::string name() const override { return "QuickSort: " + pivotChoice; }
    T choosePivot(std::vector<T>& data, int lo, int hi); // Helper to choose pivot based on strategy
    int partition(std::vector<T>& data, int lo, int hi);

    T medianOfThree(std::vector<T>& data, int lo, int hi);
    T randomPivot(std::vector<T>& data, int lo, int hi); 

private:
    std::string pivotChoice; // Instance variable for pivot selection strategy
    void quicksortHelper(std::vector<T>& data, int lo, int hi);

    std::mt19937 rng{std::random_device{}()};
};

#include "QuickOptimized.tpp"
#endif // QUICKOPTIMIZED_HPP