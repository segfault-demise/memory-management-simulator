#ifndef SET_ASSOCIATIVE_CACHE_H
#define SET_ASSOCIATIVE_CACHE_H

#include <vector>
#include <list>

using namespace std;

class SetAssociativeCache {
private:
    int totalBlocks;
    int blockSize;
    int associativity;
    int numberOfSets;

    int hits;
    int misses;

    // Each set maintains blocks in MRU -> LRU order
    vector< list<int> > sets;

public:
    SetAssociativeCache(int totalBlocks,
                        int blockSize,
                        int associativity);

    // Access a memory address, returns true if HIT
    bool access(int address);

    int getHits() const;
    int getMisses() const;
    double getHitRatio() const;

    void printCache(const char* name) const;
};

#endif
