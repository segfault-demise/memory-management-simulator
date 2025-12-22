#ifndef SET_ASSOCIATIVE_CACHE_H
#define SET_ASSOCIATIVE_CACHE_H

#include <vector>
#include <list>

class SetAssociativeCache {
private:
    int totalBlocks;
    int blockSize;
    int associativity;
    int numberOfSets;

    // Each set has its own LRU list
    std::vector<std::list<int>> sets;

    int hits;
    int misses;

public:
    SetAssociativeCache(int totalBlocks,int blockSize,int associativity);

    //  Pure check
    bool contains(int address) const;

    //  Accounting
    void recordHit();
    void recordMiss();

    //  Structural update
    void touch(int address);

    // Metrics
    int getHits() const;
    int getMisses() const;
    double getHitRatio() const;

    void printCache(const char* name) const;
};

#endif
