#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <chrono>

class Stopwatch {
public:
    void start() {
        startTime = std::chrono::high_resolution_clock::now();
        running = true;
    }

    void stop() {
        endTime = std::chrono::high_resolution_clock::now();
        running = false;
    }

    double elapsed() const {
        if (running) {
            // If still running, calculate elapsed time up to now
            auto now = std::chrono::high_resolution_clock::now();
            return std::chrono::duration<double>(now - startTime).count();
        } else {
            // If stopped, calculate elapsed time between start and stop
            return std::chrono::duration<double>(endTime - startTime).count();
        }
    }

private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;
    bool running = false;
};

#endif // STOPWATCH_HPP