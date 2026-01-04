#include "../../include/cache/LRUCache.h"
#include <iostream>

LRUCache::LRUCache(int cap) {
    capacity = cap;
    hits = 0;
    misses = 0;
}

bool LRUCache::access(int blockNumber) {
    // HIT
    if (pos.count(blockNumber)) {
        hits++;

        // Move block to MRU
        order.erase(pos[blockNumber]);
        order.push_front(blockNumber);
        pos[blockNumber] = order.begin();
        return true;
    }

    // MISS
    misses++;

    // Evict LRU if full
    if ((int)order.size() == capacity) {
        int victim = order.back();
        order.pop_back();
        pos.erase(victim);
    }

    // Insert new block
    order.push_front(blockNumber);
    pos[blockNumber] = order.begin();

    return false;
}

int LRUCache::getHits() const {
    return hits;
}

int LRUCache::getMisses() const {
    return misses;
}

double LRUCache::getHitRatio() const {
    int total = hits + misses;
    if (total == 0)
        return 0.0;
    return (double)hits / total;
}

void LRUCache::printCache(const char* name) const {
    std::cout << name << " Cache (MRU → LRU): ";
    for (int b : order) {
        std::cout << b << " ";
    }
    std::cout << std::endl;
}
