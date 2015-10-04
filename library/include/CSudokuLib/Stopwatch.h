#ifndef CSUDOKU_TIMER_H
#define CSUDOKU_TIMER_H

#include <chrono>

namespace cr = std::chrono;

class Stopwatch {
public:
    typedef cr::milliseconds milliseconds;
    typedef cr::microseconds microseconds;
    typedef cr::high_resolution_clock watch_clock;

public:
    Stopwatch() {
        stopped = false;
        start();
    }

    void start() {
        start_time = watch_clock::now();
    }

    double stop() {
        if (!stopped) {
            storedMS = get_elapsed_ms();
            storedUS = get_elapsed_us();
            stopped = true;
        }

        return get_elapsed();
    }

    double get_elapsed() {
        long us = get_elapsed_us();
        return (us / 1000.0);
    }

    long get_elapsed_ms() {
        if (!stopped) {
            return cr::duration_cast<milliseconds>(watch_clock::now() - start_time).count();
        } else {
            return storedMS;
        }
    }

    long get_elapsed_us() {
        if (!stopped) {
            return cr::duration_cast<microseconds>(watch_clock::now() - start_time).count();
        } else {
            return storedUS;
        }
    }

private:
    watch_clock::time_point start_time;

    bool stopped;
    long storedMS, storedUS;
};

#endif //CSUDOKU_TIMER_H
