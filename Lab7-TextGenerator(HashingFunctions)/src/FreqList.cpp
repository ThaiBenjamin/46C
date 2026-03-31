#include "FreqList.hpp"
#include <stdexcept>
#include <sstream>

void FreqList::add(const std::string& word) {
    // TODO: implement add
    flist_[word]++;
    totalFreq_++;
}

std::string FreqList::get(double p) const {
    // TODO: implement get
    
    if (flist_.empty()) {
        return "";
    }

    if (p < 0.0 || p >= 1.0) {
        throw std::invalid_argument("p must be in the interval [0.0, 1.0)");
    }

    double landingSpot = p * totalFreq_;
    int sum = 0;

    for (const auto& pair : flist_) {
        sum += pair.second;
        if (landingSpot < (double)sum) {
            return pair.first;
        }
    }

    return flist_.rbegin()->first;

}

std::string FreqList::toString() const {
    std::ostringstream rep;
    rep << "Frequency List: ";
    for (const auto& kv : flist_) {
        rep << "<" << kv.first << "=" << kv.second << ">";
    }
    return rep.str();
}

size_t FreqList::size() const {
    return flist_.size();
}