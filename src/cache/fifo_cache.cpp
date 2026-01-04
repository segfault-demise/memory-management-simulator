#include "../../include/cache/fifo_cache.h"
#include <iostream>

FIFOCache::FIFOCache(int cap) : capacity(cap), hits(0), misses(0) {}

void FIFOCache::accessBlock(int blockId) {
    // HIT
    if (storage.count(blockId)) {
        hits++;
        return;
    }

    // MISS
    misses++;

    // Evict if full
    if ((int)storage.size() == capacity) {
        int victim = order.front();
        order.pop_front();
        storage.erase(victim);
    }

    // Insert new block
    storage.insert(blockId);
    order.push_back(blockId);
}

int FIFOCache::hitCount() const {
    return hits;
}

int FIFOCache::missCount() const {
    return misses;
}

double FIFOCache::hitRatio() const {
    int total = hits + misses;
    return total == 0 ? 0.0 : (double)hits / total;
}

void FIFOCache::dump() const {
    std::cout << "Cache blocks: ";
    for (int b : order)
        std::cout << b << " ";
    std::cout << "\n";
}
