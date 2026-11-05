# Heap Analysis Laboratory

## Required data structure
Students must implement a priority queue as a max-heap using a dynamic array/vector. The heap must satisfy the max-heap property:

- every parent node is greater than or equal to its children;
- the root contains the maximum value;
- the left and right child indices follow the formulas:
  - left child index = 2 * i + 1
  - right child index = 2 * i + 2
  - parent index = (i - 1) / 2

## Required operations
Students must implement and analyze:

- `push(value)`
- `pop()`
- `top()`
- `contains(value)`
- `buildHeap(values)`
- `heapSort()`
- `heapifyUp(index)`
- `heapifyDown(index)`

## Analysis requirements
Students should discuss the complexity of the following operations:

- insertion into a heap;
- deletion of the maximum;
- building a heap from an array;
- searching for an item in an array-backed heap;
- heap sort;
- memory usage.

Students should provide Big-Oh analysis for:

- push
- pop
- top
- buildHeap
- heapSort
- contains

## Expected complexity summary
- push: O(log n)
- pop: O(log n)
- top: O(1)
- buildHeap: O(n)
- heapSort: O(n log n)
- contains: O(n) in a standard heap

Students should also compare a heap to:

- a binary search tree;
- a sorted array;
- a priority queue abstraction.

## Analysis

### Heap property and index formulas

A max-heap is a complete binary tree where every parent is greater than or equal to its children. "Complete" means every level is full except possibly the last one, which fills from left to right. Because of that, the tree fits in a vector with no gaps: the root is at index 0 and the levels are stored one after another.

For a node at index i:

- left child = 2i + 1
- right child = 2i + 2
- parent = (i - 1) / 2 (integer division)

Example: the node at index 4 has its parent at (4 - 1) / 2 = 1, and its children at 9 and 10. No pointers are needed, since the positions are computed. A complete tree with n nodes has height floor(log2 n), which is why push and pop are O(log n).

The heap only orders parents against their children. Siblings and nodes in different subtrees are not ordered, so a heap is not sorted. All you know for sure is that the max is at the root.

### How the operations keep the heap valid

- **heapifyUp(i):** while the value at i is bigger than its parent, swap them and move up. It stops at the root or once the parent is larger. Used by `push`.
- **heapifyDown(i):** while either child is bigger than the value at i, swap with the larger child and move down. Swapping with the larger child keeps that child valid as the new parent of its sibling. Used by `pop` and `buildHeap`.
- **push:** add the value at the end (the tree stays complete), then `heapifyUp`.
- **pop:** save the root, move the last element to the root, remove the last slot, then `heapifyDown(0)`. Throws `std::logic_error` if the heap is empty.
- **buildHeap:** copy the values, then call `heapifyDown` on each non-leaf node from index n/2 - 1 down to 0. Leaves are already valid one-node heaps, so they get skipped.
- **heapSort:** pops everything from a copy of the heap, filling the result from the back, so the output is in ascending order and the original heap is unchanged.

### Big-O summary

, Operation , Time , Extra space , Why 

 `push` , O(log n) , O(1) amortized , at most one swap per level going up 
 `pop` , O(log n),| O(1) , at most one swap per level going down 
 `top` , O(1) , O(1) , the max is always at index 0 
 `contains` , O(n) , O(1) , heap order doesn't tell you which subtree to check, so it's a linear scan 
 `buildHeap` , O(n) , O(n) for the copy of the input , bottom-up heapify (see below) 
 `heapSort` , O(n log n) , O(n)  n pops at O(log n) each, plus the copy and the output vector 
 `heapifyUp` / `heapifyDown` , O(log n) , O(1) , follow one path through the tree 

**Memory:** the heap stores n ints in one contiguous vector, so it's O(n) total with no per-node pointer overhead. Everything is iterative, so there is no recursion stack.

### Why buildHeap is O(n) and not O(n log n)

Pushing n values one at a time costs O(n log n). Bottom-up building is cheaper because most nodes are near the bottom, where `heapifyDown` has very little distance to travel. About n/2 nodes are leaves and do no work, about n/4 move at most 1 level, about n/8 move at most 2 levels, and so on. The total is about n * (1/4 + 2/8 + 3/16 + ...) = n * 1, so it's O(n). Only the few nodes near the root pay the full log n.

### Heap sort

A full heap sort is O(n) to build plus n pops at O(log n) each, which is O(n log n) in the best, average and worst case. A classic in-place heap sort uses O(1) extra space. This version works on a copy and returns a new vector so the heap stays usable, which costs O(n) extra space. Heap sort is not stable, meaning equal values can change their relative order.

### Heap vs. other structures

Max-heap , Sorted vector , BST (balanced) , BST (skewed) 
 Insert , O(log n) , O(n) (shifting) , O(log n) , O(n) 
 Find max , O(1) , O(1) , O(log n) , O(n) 
 Remove max , O(log n) , O(1) (pop back) , O(log n) , O(n) 
 Search any value , O(n) , O(log n) , O(log n) , O(n) 
 Sorted output , O(n log n) , O(n) , O(n) , O(n) 
 Build from n values , O(n) , O(n log n) , O(n log n) , O(n^2) 
 Memory , array, no pointers , array, no pointers , 2 pointers per node , 2 pointers per node 

- **vs. a sorted vector:** a sorted vector is better for searching and for getting sorted output, but every insert has to shift elements, which is O(n). A heap inserts in O(log n), so it wins when values keep getting added.
- **vs. a BST:** a BST keeps everything in order, so it can search for any value, find min and max, and do in-order traversal. A heap only keeps track of the max, but it can't become skewed. A complete tree is always balanced, so the O(log n) is guaranteed. It also uses less memory and is more cache-friendly.
- **vs. the priority queue abstraction:** a priority queue is the interface (push, top, pop by priority), and a heap is the usual way to implement it. `std::priority_queue` in C++ is a binary max-heap on a vector, which is the same design as this lab.

### When a heap is the better choice

- You keep needing the largest (or smallest) item while new items keep arriving, like task scheduling, event simulation, or Dijkstra's and Prim's algorithms.
- You want the top k items from a big stream: keep a heap of size k, which costs O(n log k).
- You want O(n log n) sorting guaranteed in the worst case with O(1) extra space (in-place heap sort).

A heap is a poor choice when you need to search for arbitrary values, delete arbitrary values, or iterate in sorted order. For those, a BST or a sorted array works better.
