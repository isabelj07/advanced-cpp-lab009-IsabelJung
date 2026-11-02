# Lab 9 — Heap Data Structure and Algorithm Analysis

## Course
CS 20 — Advanced Programming with C++

## Objective
This laboratory focuses on heaps, a complete binary tree represented as an array. Students will implement a max-heap and analyze the runtime and memory behavior of common heap operations.

## Required tasks
Students must implement a max-heap using a dynamic vector representation. The heap must support:

- insertion of values;
- retrieval of the maximum element;
- removal of the maximum element;
- heap construction from an array;
- heap sort;
- membership checks;
- correct heap property maintenance.

## Requirements
The implementation should:

- maintain the max-heap property;
- use array-based indexing correctly;
- implement `heapifyUp` and `heapifyDown`;
- maintain valid parent/child relationships;
- use clear naming and modular design;
- avoid unnecessary global state;
- include input validation where appropriate.

## Analysis focus
You must also provide a concise but rigorous written analysis that covers:

- insertion cost;
- extraction cost;
- heap construction cost;
- heap sort cost;
- search cost in a heap;
- memory complexity;
- trade-offs versus a sorted vector or BST;
- when a heap is preferable to other structures.

## Required deliverables
Students must submit:

- the C++ heap implementation;
- unit tests covering normal and edge cases;
- a brief analysis document with Big-Oh complexity;
- an explanation of the heap property and index formulas.

## Quality expectations

- meaningful names;
- comments explaining heap operations and invariants;
- const-correctness where appropriate;
- memory-safe implementation;
- clean formatting and modular design.

## Important note
The starter project intentionally contains function stubs and tests that fail until the student completes the implementation. This is by design so the lab is a rigorous programming assignment rather than a solved example.
