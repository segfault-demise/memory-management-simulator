#include "cache/SetAssociativeCache.h"
#include <iostream>

SetAssociativeCache::SetAssociativeCache(int totalBlocks,int blockSize,int associativity)
{
    this->totalBlocks = totalBlocks;
    this->blockSize = blockSize;
    this->associativity = associativity;

    numberOfSets = totalBlocks / associativity;

    sets.resize(numberOfSets);

    hits = 0;
    misses = 0;
}

bool SetAssociativeCache::contains(int address) const {

    int blockNumber = address / blockSize;
    int setIndex = blockNumber % numberOfSets;

    const std::list<int>& set = sets[setIndex];

    for (int b : set) {
        if (b == blockNumber) {
            return true;
        }
    }
    return false;
}

void SetAssociativeCache::recordHit() {
    hits++;
}

void SetAssociativeCache::recordMiss() {
    misses++;
}

void SetAssociativeCache::touch(int address) {

    int blockNumber = address / blockSize;
    int setIndex = blockNumber % numberOfSets;

    std::list<int>& set = sets[setIndex];

    // If present - promote to MRU
    for (auto it = set.begin(); it != set.end(); it++) {
        if (*it == blockNumber) {
            set.erase(it);
            set.push_front(blockNumber);
            return;
        }
    }

    // Evict LRU if set is full
    if ((int)set.size() == associativity) {
        set.pop_back();
    }

    set.push_front(blockNumber);
}

int SetAssociativeCache::getHits() const {
    return hits;
}

int SetAssociativeCache::getMisses() const {
    return misses;
}

double SetAssociativeCache::getHitRatio() const {
    int total = hits + misses;
    if (total == 0) return 0.0;
    return (double)hits / total;
}

void SetAssociativeCache::printCache(const char* name) const {

    std::cout << name << " Cache:\n";

    for (int i = 0; i < numberOfSets; i++) {
        std::cout << "  Set " << i << ": ";
        for (int b : sets[i]) {
            std::cout << b << " ";
        }
        std::cout << "\n";
    }
}
