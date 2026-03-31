#include "SelectionSort.hpp"

template<typename T>
void SelectionSort<T>::sort(std::vector<T>& data) {
    // TODO: implement selection sort
    if(data.size()< 2){
        return;
    }
    for(size_t i = 0; i < data.size()-1; ++i){
        size_t min = i;

        for(size_t j = i+1; j < data.size(); ++j){
            if(data[j] < data[min]){
                min = j;
            }
        }

        std::swap(data[i], data[min]);
    }
}
