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
