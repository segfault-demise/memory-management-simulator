#include <iostream>
#include <string>

#include "include/memory/PhysicalMemory.h"
#include "include/cache/SetAssociativeCache.h"
#include "include/vmm/VirtualMemoryManager.h"

using namespace std;

/* ---------------- STEP 1–4 ---------------- */
void demoAllocator() {
    cout << "\n--------------------------------\n";
    cout << "STEP 1 TO 4 : MEMORY ALLOCATION\n";
    cout << "--------------------------------\n";

    int totalMemory;
    cout << "Enter total memory size: ";
    cin >> totalMemory;

    string strategy;
    cout << "Enter allocation strategy (FIRST_FIT / BEST_FIT / WORST_FIT): ";
    cin >> strategy;

    AllocationStrategy strat;
    if (strategy == "FIRST_FIT")
        strat = FIRST_FIT;
    else if (strategy == "BEST_FIT")
        strat = BEST_FIT;
    else
        strat = WORST_FIT;

    PhysicalMemory mem(totalMemory, strat);

    int ops;
    cout << "Enter number of operations: ";
    cin >> ops;

    cout << "Enter operations (malloc <size> / free <address>):\n";

    for (int i = 0; i < ops; i++) {
        string command;
        cin >> command;

        if (command == "malloc") {
            int sz;
            cin >> sz;
            int addr = mem.allocate(sz);

            if (addr == -1)
                cout << "malloc(" << sz << ") -> FAILED\n";
            else
                cout << "malloc(" << sz << ") -> address " << addr << "\n";
        } else if (command == "free") {
            int addr;
            cin >> addr;
            mem.freeBlock(addr);
            cout << "free(" << addr << ")\n";
        }

        mem.dumpMemory();
        cout << "External Fragmentation: " << mem.getExternalFragmentation()
             << "\n";
        cout << "Memory Utilization: " << mem.getMemoryUtilization() << "\n\n";
    }
}

/* ---------------- STEP 5 ---------------- */
void demoCache() {
    cout << "\n--------------------------------\n";
    cout << "STEP 5 : CACHE (L1)\n";
    cout << "--------------------------------\n";

    SetAssociativeCache* L1 = nullptr;

    int commands;
    cout << "Enter number of cache commands: ";
    cin >> commands;

    cout << "Commands:\n";
    cout << "INIT_CACHE <cacheSize> <blockSize> <associativity>\n";
    cout << "CACHE_ACCESS <address>\n";
    cout << "CACHE_STATS\n\n";

    for (int i = 0; i < commands; i++) {
        string cmd;
        cin >> cmd;

        if (cmd == "INIT_CACHE") {
            int cacheSize, blockSize, assoc;
            cin >> cacheSize >> blockSize >> assoc;

            delete L1;
            L1 = new SetAssociativeCache(cacheSize, blockSize, assoc);

            cout << "\nCache Initialized\n";
            cout << "Cache Size      : " << cacheSize << "\n";
            cout << "Block Size      : " << blockSize << "\n";
            cout << "Associativity   : " << assoc << "\n\n";
        } else if (cmd == "CACHE_ACCESS") {
            int addr;
            cin >> addr;

            bool hit = L1->access(addr);

            if (hit)
                cout << "Address " << addr << " -> L1 HIT\n";
            else
                cout << "Address " << addr << " -> L1 MISS\n";
        } else if (cmd == "CACHE_STATS") {
            cout << "\nL1 Cache Statistics:\n";
            cout << "Hits      : " << L1->getHits() << "\n";
            cout << "Misses    : " << L1->getMisses() << "\n";
            cout << "Hit Ratio : " << L1->getHitRatio() << "\n\n";
        }
    }

    delete L1;
}

/* ---------------- STEP 6 ---------------- */
void demoVirtualMemory() {
    cout << "\n--------------------------------\n";
    cout << "STEP 6 : VIRTUAL MEMORY\n";
    cout << "--------------------------------\n";

    int pageSize, virtualPages, physicalFrames;
    cout << "Enter page size, number of virtual pages, number of physical "
            "frames: ";
    cin >> pageSize >> virtualPages >> physicalFrames;

    VirtualMemoryManager vmm(pageSize, virtualPages, physicalFrames);

    int n;
    cout << "Enter number of virtual addresses: ";
    cin >> n;

    cout << "Enter virtual addresses:\n";

    for (int i = 0; i < n; i++) {
        int va;
        cin >> va;
        int pa = vmm.translate(va);
        cout << "VA " << va << " -> PA " << pa << "\n";
    }

    cout << "\nPage Faults    : " << vmm.getPageFaults() << "\n";
    cout << "Page Fault Rate: " << vmm.getPageFaultRate() << "\n";
}

int main() {
    demoAllocator();
    demoCache();
    demoVirtualMemory();
    return 0;
}
