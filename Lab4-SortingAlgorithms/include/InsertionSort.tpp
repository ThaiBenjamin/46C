#include "InsertionSort.hpp"

template<typename T>
void InsertionSort<T>::sort(std::vector<T>& data) {
    // TODO: implement insertion sort
    for(size_t i = 1; i < data.size(); ++i){
        size_t j = i;
        T temp = data[j];
        while(j > 0 && temp < data[j-1]){
            data[j] = data[j-1];
            j--;
        }

        data[j] = temp;
    }
}
