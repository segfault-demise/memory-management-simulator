#include "../../include/cache/SetAssociativeCache.h"
#include <iostream>

using namespace std;

SetAssociativeCache::SetAssociativeCache(int totalBlocks,
                                         int blockSize,
                                         int associativity) {
    this->totalBlocks = totalBlocks;
    this->blockSize = blockSize;
    this->associativity = associativity;

    numberOfSets = totalBlocks / associativity;
    sets.resize(numberOfSets);

    hits = 0;
    misses = 0;
}

bool SetAssociativeCache::access(int address) {
    int blockNumber = address / blockSize;
    int setIndex = blockNumber % numberOfSets;

    list<int>& set = sets[setIndex];

    // HIT: block found in set
    for (auto it = set.begin(); it != set.end(); it++) {
        if (*it == blockNumber) {
            hits++;

            // Promote to MRU
            set.erase(it);
            set.push_front(blockNumber);
            return true;
        }
    }

    // MISS
    misses++;

    // Evict LRU if set is full
    if ((int)set.size() == associativity) {
        set.pop_back();
    }

    // Insert as MRU
    set.push_front(blockNumber);
    return false;
}

int SetAssociativeCache::getHits() const {
    return hits;
}

int SetAssociativeCache::getMisses() const {
    return misses;
}

double SetAssociativeCache::getHitRatio() const {
    int total = hits + misses;
    if (total == 0)
        return 0.0;
    return (double)hits / total;
}

void SetAssociativeCache::printCache(const char* name) const {
    cout << name << " Cache:\n";

    for (int i = 0; i < numberOfSets; i++) {
        cout << "  Set " << i << ": ";
        for (int b : sets[i]) {
            cout << b << " ";
        }
        cout << endl;
    }
}
