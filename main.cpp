#include <iostream>
#include "memory/PhysicalMemory.h"
#include "cache/Cache.h"

int main() {

    PhysicalMemory memory(1000, FIRST_FIT);

    // Cache with 3 lines
    Cache cache(3);

    // Simulated memory accesses
    int a = memory.allocate(100);  // address 0
    int b = memory.allocate(200);  // address 100
    int c = memory.allocate(150);  // address 300
    int d = memory.allocate(100);  // address 450

    int blockSize = 100;

    // Access pattern
    cache.access(a / blockSize);
    cache.printCache();
    cache.access(b / blockSize);
    cache.printCache();
    cache.access(c / blockSize);
    cache.printCache();
    cache.access(a / blockSize);  // hit
    cache.printCache();
    cache.access(d / blockSize);  // eviction
    cache.printCache();
    cache.access(b / blockSize);  // may be miss

    cache.printCache();

    std::cout << "Cache Hits: " << cache.getHits() << "\n";
    std::cout << "Cache Misses: " << cache.getMisses() << "\n";
    std::cout << "Hit Ratio: " << cache.getHitRatio() << "\n";

    return 0;
}
