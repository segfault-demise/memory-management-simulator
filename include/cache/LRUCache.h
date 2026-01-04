#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
private:
    int capacity;
    int hits;
    int misses;

    list<int> order;   // MRU at front
    unordered_map<int, list<int>::iterator> pos;

public:
    LRUCache(int cap);

    // Access block: returns true if HIT
    bool access(int blockNumber);

    int getHits() const;
    int getMisses() const;
    double getHitRatio() const;

    void printCache(const char* name) const;
};

#endif
