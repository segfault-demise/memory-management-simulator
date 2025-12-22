#include <iostream>
#include "memory/PhysicalMemory.h"
#include "cache/SetAssociativeCache.h"

int main() {

    PhysicalMemory memory(1000, FIRST_FIT);

    // Configurable caches
    SetAssociativeCache L1(4, 100, 2);  // 4 blocks, 2-way
    SetAssociativeCache L2(8, 100, 4);  // 8 blocks, 4-way

    int addresses[] = {
        memory.allocate(100),
        memory.allocate(100),
        memory.allocate(100),
        memory.allocate(100),
        memory.allocate(100)
    };

    int accessPattern[] = {0,1,2,0,3,1,4,0};

    for (int idx : accessPattern) {

        int addr = addresses[idx];

        // L1
        if (L1.contains(addr)) {
            L1.recordHit();
            L1.touch(addr);
            continue;
        }

        L1.recordMiss();

        // L2
        if (L2.contains(addr)) {
            L2.recordHit();
            L2.touch(addr);
            L1.touch(addr);   // promote
        }
        else {
            L2.recordMiss();
            L2.touch(addr);
            L1.touch(addr);
        }
    }

    std::cout << "\nFinal State:\n";
    L1.printCache("L1");
    L2.printCache("L2");

    std::cout << "\nMetrics:\n";
    std::cout << "L1 Hit Ratio: " << L1.getHitRatio() << "\n";
    std::cout << "L2 Hit Ratio: " << L2.getHitRatio() << "\n";

    return 0;
}
