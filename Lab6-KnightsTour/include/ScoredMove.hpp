#ifndef SCOREDMOVE_HPP
#define SCOREDMOVE_HPP

struct ScoredMove {
    int row;
    int col;
    double score;

    ScoredMove() : row(-1), col(-1), score(0.0) {}
    ScoredMove(int r, int c, double s) : row(r), col(c), score(s) {}

    // TODO: implement comparison operators for sorting
    // If score is the same, break ties by row and then column
    bool operator<(const ScoredMove& other) const {  
        if (score != other.score) {
            return score < other.score;
        }
        if (row != other.row) {
            return row < other.row;
        }
        return col < other.col;
    }
    bool operator>(const ScoredMove& other) const {
        return other < *this;
    }
    bool operator==(const ScoredMove& other) const {
        return score == other.score && 
               row == other.row && 
               col == other.col;
    }
    bool operator!=(const ScoredMove& other) const { return !(*this == other); }
};

#endif // SCOREDMOVE_HPP