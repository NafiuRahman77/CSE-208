# Data Structures and Algorithms 2 Sessional

## Overview
This repository contains implementations of various advanced data structures and algorithms covered in the Data Structures and Algorithms 2 Sessional course. Each offline task focuses on a specific topic, ranging from graph algorithms to hashing and specialized data structures.

---

## Contents

### Offline-1: Minimum Spanning Tree (MST)
- **Description**: Implements Prim's and Kruskal's algorithms to find the minimum spanning tree of a graph.

### Offline-2: Single-Source Shortest Path (Dijkstra's Algorithm)
- **Description**: Implements Dijkstra's algorithm to compute the shortest path from a single source node to all other nodes in a graph.

### Offline-3: All-Pairs Shortest Path (Floyd-Warshall Algorithm)
- **Description**: Implements the Floyd-Warshall algorithm to compute shortest paths between all pairs of nodes in a graph.

### Offline-4: Max Flow (Baseball Elimination Problem)
- **Description**: Solves the Baseball Elimination problem using the Max Flow algorithm.

### Offline-5: Fibonacci Heap
- **Description**: Implements the Fibonacci Heap data structure, commonly used for priority queues and Dijkstra’s algorithm optimizations.

### Offline-6: Red-Black Tree
- **Description**: Implements a Red-Black Tree data structure with insertion and balancing operations.

### Offline-7: Hashing
- **Description**: Implements the following hashing techniques:
1. **Separate Chaining**:  
   - Uses linked lists to resolve collisions in hash tables.

2. **Linear Probing**:  
   - Resolves collisions using a linear probing hash function:  
     ```
     h(k, i) = (h1(k) + i) mod N
     ```

3. **Quadratic Probing**:  
   - Resolves collisions using a quadratic probing hash function:  
     ```
     h(k, i) = (h1(k) + c1 * i + c2 * i^2) mod N
     ```
     - Where `c1` and `c2` are positive constants.

4. **Double Hashing**:  
   - Resolves collisions using a double hashing function:  
     ```
     h(k, i) = (h1(k) + i * h2(k)) mod N
     ```


---

## Requirements
- **C++ Compiler**: GCC or equivalent.
  
---

## How to Use
1. Clone the repository:
   ```bash
   git clone <repository_url>
   cd <repository_directory>
2. Navigate to the respective folder for the offline task you want to execute.
3. Compile the C++ file:
   ```bash
   g++ 1905077.cpp -o output
   ./output
   
## References
- **Graph Algorithms**: [Introduction to Graph Theory](https://en.wikipedia.org/wiki/Graph_theory)
- **Data Structures**: [CLRS - Introduction to Algorithms](https://mitpress.mit.edu/9780262046305/introduction-to-algorithms/)
- **Hashing**: [Hash Functions](https://en.wikipedia.org/wiki/Hash_function)

