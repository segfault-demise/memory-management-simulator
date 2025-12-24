#include <iostream>
#include "vmm/VirtualMemoryManager.h"

int main() {

    VirtualMemoryManager vmm(100, 10, 4);

    int accesses[] = {
        10, 120, 250, 330,   // pages 0,1,2,3
        410,                // page 4 → eviction
        120,                // page 1
        10                  // page 0 → likely fault
    };

    for (int va : accesses) {
        int pa = vmm.translate(va);
        std::cout << "VA " << va << " -> PA " << pa << "\n";

    }

    std::cout << "\nPage Faults: " << vmm.getPageFaults() << "\n";
    std::cout << "Page Fault Rate: " << vmm.getPageFaultRate() << "\n";

    return 0;
}
