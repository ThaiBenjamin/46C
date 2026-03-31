#ifndef SELECTIONSORT_HPP
#define SELECTIONSORT_HPP

#include <vector>
#include <string>

#include "Sorter.hpp"

// Simple in-place selection sort (ascending)
template<typename T>
class SelectionSort : public Sorter<T> {
public:
    SelectionSort() = default; // Default constructor
    void sort(std::vector<T>& data) override;
    std::string name() const override { return "SelectionSort"; }
};

#include "SelectionSort.tpp"
#endif // SELECTIONSORT_HPP
