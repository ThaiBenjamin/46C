#ifndef MERGEOPTIMIZED_HPP
#define MERGEOPTIMIZED_HPP

#include <vector>
#include "Sorter.hpp"
#include "InsertionSort.hpp" // Include InsertionSort for small subarrays

template<typename T>
class MergeOptimized : public Sorter<T> {
public:
    MergeOptimized(int threshold = -1) // Constructor with threshold for InsertionSort
        : insertionSortThreshold{threshold} {}

    void sort(std::vector<T>& data) override;
    std::string name() const override { 
        if (insertionSortThreshold > 0) {
            return "MergeSort: " + std::to_string(insertionSortThreshold);
        }
        return "MergeSort";
    }
    void merge(std::vector<T>& data, std::vector<T>& aux, int lo, int mid, int hi);

private:
    int insertionSortThreshold; // Threshold for switching to InsertionSort

    void mergeSortHelper(std::vector<T>& data, std::vector<T>& aux, int lo, int hi);

};

#include "MergeOptimized.tpp"
#endif // MERGEOPTIMIZED_HPP