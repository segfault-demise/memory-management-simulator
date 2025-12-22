#include <iostream>
#include "memory/PhysicalMemory.h"

int main() {
    PhysicalMemory memory(1024); // 1024 bytes of RAM
    memory.dumpMemory();
    return 0;
}
