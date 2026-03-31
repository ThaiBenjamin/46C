#include "MergeOptimized.hpp"
#include <algorithm> // For std::copy

template<typename T>
void MergeOptimized<T>::sort(std::vector<T>& data) {
    if (data.empty()) {
        return;
    }

    std::vector<T> aux(data.size()); // Auxiliary array for merging
    mergeSortHelper(data, aux, 0, static_cast<int>(data.size()) - 1);
}

template<typename T>
void MergeOptimized<T>::mergeSortHelper(std::vector<T>& data, std::vector<T>& aux, int lo, int hi) {
    // TODO: implement merge sort
    // TODO: Use InsertionSort for small subarrays
    if(hi - lo < 10){
        InsertionSort<int> sorter;
        sorter.sort(data); 
        return;
    }
        

    int mid = lo+(hi-lo)/2;
    // Sort left half
    mergeSortHelper(data, aux, lo, mid);
    // Sort right half
    mergeSortHelper(data, aux, mid+1, hi);
    // Merge the two halves
    merge(data, aux, lo, mid, hi);
}

template<typename T>
void MergeOptimized<T>::merge(std::vector<T>& data, std::vector<T>& aux, int lo, int mid, int hi) {
    // TODO: implement merge
    // Copy data to auxiliary array
    for(int i = lo; i <= hi; ++i){
        aux[i] = data[i];
    }

    int i = lo;
    int j = mid+1;  

    for(int k = lo; k <= hi;++k){
        // Left half exhausted 
        if(i > mid){
            data[k] = aux[j];
            j++;
        }
        // Right half exhausted
        else if(j > hi){
            data[k] = aux[i];
            i++;
        }
        // Right element is smaller
        else if(aux[j] < aux[i]){
            data[k] = aux[j];
            j++;
        }
        // Left element is smaller
        else{
            data[k] = aux[i];
            i++;
        }
    }
    
        
    
}

