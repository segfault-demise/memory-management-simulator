#include "cache/Cache.h"
#include <iostream>

// Constructor
Cache::Cache(int cap) {
    capacity = cap;
    hits = 0;
    misses = 0;
}

// Access a memory block
void Cache::access(int blockNumber) {

    // Check if block is already in cache (HIT)
    for (int block : cacheLines) {
        if (block == blockNumber) {
            hits++;
            return;
        }
    }

    // MISS
    misses++;

    // If cache is full, evict oldest block (FIFO)
    if ((int)cacheLines.size() == capacity) {
        int victim = fifoQueue.front();
        fifoQueue.pop();

        // Remove victim from cacheLines
        for (auto it = cacheLines.begin(); it != cacheLines.end(); it++) {
            if (*it == victim) {
                cacheLines.erase(it);
                break;
            }
        }
    }

    // Insert new block
    cacheLines.push_back(blockNumber);
    fifoQueue.push(blockNumber);
}

// Metric functions
int Cache::getHits() const {
    return hits;
}

int Cache::getMisses() const {
    return misses;
}

double Cache::getHitRatio() const {
    int total = hits + misses;
    if (total == 0) return 0.0;
    return (double)hits / total;
}

void Cache::printCache() const {
    std::cout << "Cache content: ";
    for (int block : cacheLines) {
        std::cout << block << " ";
    }
    std::cout << "\n";
}
