#include <iostream>
#include <vector>
#include <random>
#include <memory>
#include <iomanip>
#include <algorithm>

#include "Sorter.hpp"
#include "Stopwatch.hpp"
#include "InsertionSort.hpp"
#include "SelectionSort.hpp"
#include "QuickOptimized.hpp"
#include "MergeOptimized.hpp"

class SortTimer {
public:
    SortTimer() : rng(std::random_device{}()) {}

    void printTimesRandom(const std::vector<std::unique_ptr<Sorter<int>>>& sorters,
                          const std::vector<int>& sizes) {
        constexpr int sizeWidth = 8;
        constexpr int colWidth = 15;
        const std::string bar = " | ";
        std::cout << "\nSorting time versus size (random data)\n\n";
        std::cout << std::setw(sizeWidth) << "size";
        for (const auto& s : sorters) {
            std::cout << bar << std::setw(colWidth) << s->name();
        }
        std::cout << "\n";
        const size_t totalWidth = sizeWidth + (bar.size() + colWidth) * sorters.size();
        std::cout << std::string(totalWidth, '-') << "\n";

        for (int size : sizes) {
            std::cout << std::setw(sizeWidth) << size;

            // Generate random data once for this size
            std::vector<int> originalData = getRandom(size);

            for (const auto& s : sorters) {
                // Make a copy of the original data for each sorter
                std::vector<int> data = originalData;

                // Time the sorting algorithm
                double ms = time(*s, data) * 1000.0;
                std::cout << bar << std::setw(colWidth) << std::fixed << std::setprecision(6) << ms;

                if (!isSorted(data)) {
                    std::cerr << "Data wasn't sorted correctly by: " << s->name() << "\n";
                }
            }
            std::cout << "\n";
        }
    }

    void printTimesSorted(const std::vector<std::unique_ptr<Sorter<int>>>& sorters,
                          const std::vector<int>& sizes) {
        constexpr int sizeWidth = 8;
        constexpr int colWidth = 15;
        const std::string bar = " | ";
        std::cout << "\nSorting time versus size (already sorted data)\n\n";
        std::cout << std::setw(sizeWidth) << "size";
        for (const auto& s : sorters) {
            std::cout << bar << std::setw(colWidth) << s->name();
        }
        std::cout << "\n";
        const size_t totalWidth = sizeWidth + (bar.size() + colWidth) * sorters.size();
        std::cout << std::string(totalWidth, '-') << "\n";

        for (int size : sizes) {
            std::cout << std::setw(sizeWidth) << size;

            // Generate sorted data once for this size
            std::vector<int> originalData = getSorted(size);

            for (const auto& s : sorters) {
                // Make a copy of the original data for each sorter
                std::vector<int> data = originalData;

                // Time the sorting algorithm
                double ms = time(*s, data) * 1000.0;
                std::cout << bar << std::setw(colWidth) << std::fixed << std::setprecision(6) << ms;

                if (!isSorted(data)) {
                    std::cerr << "Data wasn't sorted correctly by: " << s->name() << "\n";
                }
            }
            std::cout << "\n";
        }
    }

private:
    std::mt19937 rng;

    std::vector<int> getRandom(int size) {
        std::vector<int> v;
        v.reserve(static_cast<size_t>(size));
        std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        for (int i = 0; i < size; ++i) {
            v.push_back(dist(rng));
        }
        return v;
    }

    std::vector<int> getSorted(int size) {
        std::vector<int> v(size);
        std::iota(v.begin(), v.end(), 0); // Fill with 0, 1, 2, ..., size-1
        return v;
    }

    bool isSorted(const std::vector<int>& data) {
        return std::is_sorted(data.begin(), data.end());
    }

    double time(Sorter<int>& s, std::vector<int>& nums) {
        Stopwatch timer;
        timer.start();
        s.sort(nums);
        timer.stop();
        return timer.elapsed();
    }
};

int main() {
    std::vector<std::unique_ptr<Sorter<int>>> sorters;

    // Add sorting algorithms in the requested order
    sorters.emplace_back(std::unique_ptr<Sorter<int>>(new SelectionSort<int>()));
    sorters.emplace_back(std::unique_ptr<Sorter<int>>(new InsertionSort<int>()));
    sorters.emplace_back(std::unique_ptr<Sorter<int>>(new MergeOptimized<int>()));
    sorters.emplace_back(std::unique_ptr<Sorter<int>>(new MergeOptimized<int>(32)));
    sorters.emplace_back(std::unique_ptr<Sorter<int>>(new MergeOptimized<int>(64)));
    sorters.emplace_back(std::unique_ptr<Sorter<int>>(new QuickOptimized<int>()));
    sorters.emplace_back(std::unique_ptr<Sorter<int>>(new QuickOptimized<int>(std::string("MEDIAN"))));
    sorters.emplace_back(std::unique_ptr<Sorter<int>>(new QuickOptimized<int>(std::string("RANDOM"))));

  
    // Generate sizes for testing
    std::vector<int> sizes;
    int dataSize = 1000;
    for (int i = 0; i < 7; ++i) { 
        sizes.push_back(dataSize);
        dataSize *= 2;
    }

    // Run the timer for random and sorted data
    SortTimer timer;
    timer.printTimesRandom(sorters, sizes);
    timer.printTimesSorted(sorters, sizes);

    return 0;
}