#ifndef FIFO_CACHE_H
#define FIFO_CACHE_H

#include <unordered_set>
#include <deque>

class FIFOCache {
private:
    int capacity;
    int hits;
    int misses;

    std::unordered_set<int> storage;
    std::deque<int> order;

public:
    explicit FIFOCache(int cap);

    void accessBlock(int blockId);

    int hitCount() const;
    int missCount() const;
    double hitRatio() const;

    void dump() const;
};

#endif
