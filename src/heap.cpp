#include "project/heap.h"

#include <algorithm>
#include <stdexcept>

MaxHeap::MaxHeap() = default;

MaxHeap::MaxHeap(const std::vector<int>& values) {
    buildHeap(values);
}

bool MaxHeap::empty() const noexcept {
    return data_.empty();
}

std::size_t MaxHeap::size() const noexcept {
    return data_.size();
}

int MaxHeap::top() const {
    if (empty()) {
        throw std::logic_error("Heap is empty");
    }
    return data_.front();
}

bool MaxHeap::contains(int value) const {
    for (int item : data_) {
        if (item == value) {
            return true;
        }
    }
    return false;
}

void MaxHeap::push(int value) {
    // Add to the end to keep the tree complete, then move it up into place.
    data_.push_back(value);
    heapifyUp(data_.size() - 1);
}

int MaxHeap::pop() {
    if (empty()) {
        throw std::logic_error("Heap is empty");
    }

    // Move the last element to the root, then sift it down to restore the heap.
    const int maxValue = data_.front();
    data_.front() = data_.back();
    data_.pop_back();
    if (!empty()) {
        heapifyDown(0);
    }
    return maxValue;
}

void MaxHeap::buildHeap(const std::vector<int>& values) {
    data_ = values;

    // Leaves are already valid heaps, so sift down every non-leaf node,
    // starting from the last one and working back to the root.
    for (std::size_t i = data_.size() / 2; i > 0; --i) {
        heapifyDown(i - 1);
    }
}

std::vector<int> MaxHeap::heapSort() {
    // Pop from a copy so the heap itself is left unchanged.
    MaxHeap working = *this;
    std::vector<int> sorted(data_.size());
    for (std::size_t i = sorted.size(); i > 0; --i) {
        sorted[i - 1] = working.pop();
    }
    return sorted;
}

std::vector<int> MaxHeap::toVector() const {
    return data_;
}

std::size_t MaxHeap::parentIndex(std::size_t index) {
    if (index == 0) {
        return 0;
    }
    return (index - 1) / 2;
}

std::size_t MaxHeap::leftChildIndex(std::size_t index) {
    return (2 * index) + 1;
}

std::size_t MaxHeap::rightChildIndex(std::size_t index) {
    return (2 * index) + 2;
}

void MaxHeap::heapifyUp(std::size_t index) {
    // Swap with the parent while this value is larger than it.
    while (index > 0) {
        const std::size_t parent = parentIndex(index);
        if (data_[parent] >= data_[index]) {
            break;
        }
        swap(data_[parent], data_[index]);
        index = parent;
    }
}

void MaxHeap::heapifyDown(std::size_t index) {
    // Swap with the larger child while either child is bigger than this value.
    const std::size_t count = data_.size();
    while (true) {
        const std::size_t left = leftChildIndex(index);
        const std::size_t right = rightChildIndex(index);
        std::size_t largest = index;

        if (left < count && data_[left] > data_[largest]) {
            largest = left;
        }
        if (right < count && data_[right] > data_[largest]) {
            largest = right;
        }
        if (largest == index) {
            break;
        }
        swap(data_[index], data_[largest]);
        index = largest;
    }
}

void MaxHeap::swap(int& a, int& b) {
    std::swap(a, b);
}

bool MaxHeap::isValidHeap() const {
    for (std::size_t i = 1; i < data_.size(); ++i) {
        if (data_[parentIndex(i)] < data_[i]) {
            return false;
        }
    }
    return true;
}
