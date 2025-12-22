#include <iostream>
#include "memory/PhysicalMemory.h"

void testStrategy(AllocationStrategy strategy, const std::string& name) {

    std::cout << "\n" << name << "\n";

    PhysicalMemory memory(1000, strategy);

    // Step 1: Create fragmentation
    int a = memory.allocate(100);   // Block A
    int b = memory.allocate(300);   // Block B
    int c = memory.allocate(200);   // Block C

    // Memory now:
    // [100 A][300 B][200 C][400 Free]

    // Step 2: Free middle block to create hole
    memory.freeBlock(b);

    // Memory now:
    // [100 A][300 Free][200 C][400 Free]

    // Step 3: Allocate 250 bytes
    // This fits in BOTH 300 and 400 blocks
    memory.dumpMemory();
    
    memory.allocate(250);

    memory.dumpMemory();
}

int main() {

    testStrategy(FIRST_FIT, "FIRST FIT");
    testStrategy(BEST_FIT, "BEST FIT");
    testStrategy(WORST_FIT, "WORST FIT");

    return 0;
}
