#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

class MaxHeap {
public:
    MaxHeap();
    explicit MaxHeap(const std::vector<int>& values);

    bool empty() const noexcept;
    std::size_t size() const noexcept;
    int top() const;
    bool contains(int value) const;

    void push(int value);
    int pop();
    void buildHeap(const std::vector<int>& values);
    std::vector<int> heapSort();
    std::vector<int> toVector() const;

private:
    std::vector<int> data_;

    static std::size_t parentIndex(std::size_t index);
    static std::size_t leftChildIndex(std::size_t index);
    static std::size_t rightChildIndex(std::size_t index);

    void heapifyUp(std::size_t index);
    void heapifyDown(std::size_t index);
    void swap(int& a, int& b);
    bool isValidHeap() const;
};
