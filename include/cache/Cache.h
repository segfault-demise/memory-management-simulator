#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <queue>

class Cache {
private:
    int capacity;                   // number of cache lines
    std::queue<int> fifoQueue;      // FIFO order
    std::vector<int> cacheLines;    // stored block numbers

    int hits;
    int misses;

public:
    Cache(int capacity);

    // Simulate access to a memory block
    void access(int blockNumber);

    // Metrics
    int getHits() const;
    int getMisses() const;
    double getHitRatio() const;

    void printCache() const;
};

#endif
