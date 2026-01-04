#include <iostream>
#include "include/vmm/VirtualMemoryManager.h"
#include "include/cache/SetAssociativeCache.h"

using namespace std;

int main() {
    // -------- Virtual Memory Configuration --------
    VirtualMemoryManager vmm(64,  // page size (bytes)
                             16,  // number of virtual pages
                             6    // number of physical frames
    );

    // -------- Cache Hierarchy --------
    // L1 Cache: smaller, faster
    SetAssociativeCache L1(6,   // total blocks
                           64,  // block size
                           2    // 2-way set associative
    );

    // L2 Cache: larger, slower
    SetAssociativeCache L2(12,  // total blocks
                           64,  // block size
                           3    // 3-way set associative
    );

    // Virtual address trace
    int virtualAddresses[] = {20, 80,  140, 220, 20,  300,
                              80, 400, 140, 20,  500, 300};

    int n = sizeof(virtualAddresses) / sizeof(int);

    for (int i = 0; i < n; i++) {
        int va = virtualAddresses[i];

        // Virtual -> Physical address translation
        int pa = vmm.translate(va);

        // -------- Cache Access --------
        bool hitL1 = L1.access(pa);

        if (!hitL1) {
            bool hitL2 = L2.access(pa);

            // Promote to L1 on L2 hit or miss
            L1.access(pa);
        }

        cout << "VA " << va << " -> PA " << pa << endl;
    }

    // -------- Metrics --------
    cout << "\n--- Metrics ---\n";

    cout << "Page Faults: " << vmm.getPageFaults() << endl;
    cout << "Page Fault Rate: " << vmm.getPageFaultRate() << endl;

    cout << "\nL1 Hit Ratio: " << L1.getHitRatio() << endl;
    cout << "L2 Hit Ratio: " << L2.getHitRatio() << endl;

    return 0;
}
