# Memory Management Simulator

A C++-based simulator that models how an operating system manages memory, including physical memory allocation, cache hierarchy, and virtual memory with paging. The project focuses on core OS concepts, correctness, and performance metrics.

---

## Features

### Physical Memory Management
- Simulates contiguous physical memory
- Dynamic allocation using First Fit, Best Fit, and Worst Fit
- Block splitting and coalescing on allocation and deallocation
- Tracks memory utilization, external fragmentation, and allocation success rate

### Cache Simulation
- FIFO Cache
- LRU Cache
- Set-Associative Cache with LRU replacement per set
- Multi-level cache hierarchy (L1 and L2)
- Tracks cache hits, misses, and hit ratios

### Virtual Memory Management
- Paging-based virtual memory simulation
- Page table with valid bits and frame mapping
- LRU-based page replacement
- Virtual to physical address translation
- Tracks page faults, memory accesses, and page fault rate

---

## Project Structure

```
include/
  ├── cache/
  │   ├── FIFOCache.h
  │   ├── LRUCache.h
  │   └── SetAssociativeCache.h
  │
  ├── memory/
  │   └── PhysicalMemory.h
  │
  └── vmm/
      └── VirtualMemoryManager.h

src/
  ├── cache/
  │   ├── FIFOCache.cpp
  │   ├── LRUCache.cpp
  │   └── SetAssociativeCache.cpp
  │
  ├── memory/
  │   └── PhysicalMemory.cpp
  │
  └── vmm/
      └── VirtualMemoryManager.cpp

tests/
  └── (test files)

main.cpp
README.md
.gitignore
```

---

## How It Works

1. A virtual address is generated from an access trace.
2. The Virtual Memory Manager translates the virtual address to a physical address using paging and LRU replacement.
3. The physical address is accessed through a two-level cache hierarchy (L1 followed by L2).
4. Cache blocks are promoted based on access behavior.
5. Performance statistics are collected and displayed.

Access flow:
```
Virtual Address → Page Table → Physical Address → L1 Cache → L2 Cache → Main Memory
```

---

## Build and Run

### Compile
```bash
g++ main.cpp \
    src/cache/SetAssociativeCache.cpp \
    src/cache/LRUCache.cpp \
    src/cache/FIFOCache.cpp \
    src/memory/PhysicalMemory.cpp \
    src/vmm/VirtualMemoryManager.cpp \
    -Iinclude \
    -o simulator
```

### Run
```bash
./simulator
```

---

## Metrics Collected
- Page faults and page fault rate
- L1 and L2 cache hit ratios
- Memory utilization
- External fragmentation
- Allocation success rate

---

## Learning Outcomes
- Understanding of OS memory allocation strategies
- Cache organizations and replacement policies
- Paging and virtual memory translation
- Performance trade-offs in memory systems
- Modular C++ design using header/source separation

---

## Possible Extensions
- Add LFU or Clock replacement policies
- Add direct-mapped cache
- Add configurable cache latencies
- Add command-line interface for custom memory traces
- Add visualization of memory layout

---

## Author
Developed as an Operating Systems / Systems Programming project to explore memory management concepts through simulation.
