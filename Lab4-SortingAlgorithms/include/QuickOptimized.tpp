#include "QuickOptimized.hpp"
#include "InsertionSort.hpp" // Include the InsertionSort header
#include <utility>
#include <algorithm>
#include <random>
#include <cassert>

template<typename T>
void QuickOptimized<T>::sort(std::vector<T>& data) {
    if (!data.empty()) {
        quicksortHelper(data, 0, static_cast<int>(data.size()) - 1);
    }
}

template<typename T>
void QuickOptimized<T>::quicksortHelper(std::vector<T>& data, int lo, int hi) {
    // TODO: implement quicksort recursive helper
    
    // TODO: choose pivot based on pivotChoice

    // Partition using Hoare's method
    if(lo < hi){
        int par = partition(data, lo, hi);

        quicksortHelper(data, lo, par);
        quicksortHelper(data, par+1, hi);
    }

    // Recursively sort the partitions

}

template<typename T>
int QuickOptimized<T>::partition(std::vector<T>& data, int lo, int hi) {
    // TODO: implement Hoare's partitioning scheme
    T pivot = choosePivot(data, lo, hi);

    int i = lo;
    int j = hi;

    while(true){
        while(data[i] < pivot){
            i++;
        }
        while(data[j] > pivot){
            j--;
        }

        if(i >= j){
            return j;
        }

        std::swap(data[i], data[j]);

        i++;
        j--;
    }
}

template<typename T>
T QuickOptimized<T>::medianOfThree(std::vector<T>& data, int lo, int hi) {
    // TODO: implement median-of-three pivot selection
    int mid = lo + (hi-lo)/2;

    if(data[mid] < data[lo]){
        std::swap(data[mid], data[lo]);
    }
    if(data[hi] < data[lo]){
        std::swap(data[hi], data[lo]);
    }
    if(data[hi] < data[mid]){
        std::swap(data[hi], data[mid]);
    }

    std::swap(data[lo], data[mid]);
    return data[lo];
}

template<typename T>
T QuickOptimized<T>::randomPivot(std::vector<T>& data, int lo, int hi) {
    // TODO: implement random pivot selection
    static std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<int> dist(lo, hi);
    int idx = dist(engine);
    std::swap(data[lo], data[idx]);
    return data[lo];

}   

template<typename T>
T QuickOptimized<T>::choosePivot(std::vector<T>& data, int lo, int hi) {
    // TODO: choose pivot based on pivotChoice
    // default to "LO" if unrecognized or empty
    if(pivotChoice == "MEDIAN"){
        return medianOfThree(data, lo, hi);
    }
    else if(pivotChoice == "RANDOM"){
        return randomPivot(data, lo, hi);
    }
    else{
        return data[lo];
    }

}
