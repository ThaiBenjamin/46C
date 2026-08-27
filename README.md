# ICS 46C — Data Structures and Algorithms in C++

Lab assignments from UC Irvine's data structures course. Each structure is implemented from
scratch in C++ rather than pulled from the standard library, with Google Test suites
alongside, built with CMake.

## Labs

| Lab | Topic |
|---|---|
| 1 | Warm-up — random number generation, basic C++ |
| 2 | ArrayList and LinkedList |
| 3 | Stacks and queues |
| 4 | Sorting algorithms |
| 5 | Binary tree and left-leaning red-black tree |
| 6 | Knight's Tour — backtracking and tree search |
| 7 | Text generator using hashing |

## What I took from it

Building these by hand instead of reaching for `std::vector` or `std::map` gave me an
intuition for what's happening underneath in any language. You can use a hash map for years
without thinking about it; you only really understand the cost of a collision after writing
the code that resolves one.

The hashing lab made that concrete. Chaining against open addressing is a paragraph in a
textbook and a genuinely different set of trade-offs once you've implemented both and
watched what happens to lookup times as the table fills.

The Knight's Tour was the most fun. Backtracking is easy to describe — try a move, recurse,
undo it if the branch dies — and much more interesting to watch actually work on a board,
where a bad heuristic means the search wanders for a very long time before giving up.

I also got comfortable here with CMake and with writing tests that are worth having, rather
than tests that restate the implementation.
