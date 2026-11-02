#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "project/heap.h"

#include <stdexcept>
#include <vector>

TEST_CASE("MaxHeap default constructor and empty-state checks") {
    MaxHeap heap;
    REQUIRE(heap.empty());
    REQUIRE(heap.size() == 0u);
    REQUIRE_THROWS_AS(heap.top(), std::logic_error);
    REQUIRE_FALSE(heap.contains(5));
    REQUIRE_THROWS_AS(heap.pop(), std::logic_error);
}

TEST_CASE("MaxHeap push, top, and size") {
    MaxHeap heap;
    heap.push(10);
    heap.push(5);
    heap.push(15);
    heap.push(7);

    REQUIRE(heap.size() == 4u);
    REQUIRE_FALSE(heap.empty());
    REQUIRE(heap.top() == 15);
    REQUIRE(heap.contains(10));
    REQUIRE(heap.contains(15));
    REQUIRE_FALSE(heap.contains(99));
}

TEST_CASE("MaxHeap pop removes the maximum and preserves heap property") {
    MaxHeap heap;
    for (int value : {10, 5, 15, 3, 7, 20, 1}) {
        heap.push(value);
    }

    REQUIRE(heap.pop() == 20);
    REQUIRE(heap.top() == 15);
    REQUIRE(heap.pop() == 15);
    REQUIRE(heap.top() == 10);
    REQUIRE(heap.size() == 5u);
}

TEST_CASE("MaxHeap build from vector") {
    std::vector<int> values = {4, 10, 3, 5, 1, 7, 8, 2};
    MaxHeap heap(values);

    REQUIRE(heap.size() == values.size());
    REQUIRE(heap.top() == 10);
    REQUIRE(heap.contains(8));
    REQUIRE(heap.contains(1));
    REQUIRE_FALSE(heap.empty());
}

TEST_CASE("MaxHeap duplicate insertion and contains behavior") {
    MaxHeap heap;
    heap.push(5);
    heap.push(5);
    heap.push(3);

    REQUIRE(heap.size() == 3u);
    REQUIRE(heap.contains(5));
    REQUIRE(heap.top() == 5);
}

TEST_CASE("MaxHeap heapSort returns sorted output") {
    MaxHeap heap;
    std::vector<int> values = {9, 4, 7, 1, 3, 6, 8, 2, 5};
    for (int value : values) {
        heap.push(value);
    }

    std::vector<int> sorted = heap.heapSort();
    REQUIRE(sorted == std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

TEST_CASE("MaxHeap handles empty pop and heapSort edge cases") {
    MaxHeap emptyHeap;
    REQUIRE_THROWS_AS(emptyHeap.pop(), std::logic_error);

    MaxHeap singleHeap;
    singleHeap.push(42);
    REQUIRE(singleHeap.pop() == 42);
    REQUIRE(singleHeap.empty());

    MaxHeap other;
    other.buildHeap({7});
    REQUIRE(other.top() == 7);

    MaxHeap emptySortHeap;
    REQUIRE(emptySortHeap.heapSort().empty());
}

TEST_CASE("MaxHeap buildHeap handles already-heap and random input") {
    MaxHeap heap;
    heap.buildHeap({1, 2, 3, 4, 5});
    REQUIRE(heap.top() == 5);
    REQUIRE(heap.size() == 5u);

    MaxHeap other;
    other.buildHeap({8, 3, 9, 1, 6, 2, 7, 4});
    REQUIRE(other.top() == 9);
    REQUIRE(other.contains(7));
    REQUIRE(other.contains(4));
}

TEST_CASE("MaxHeap supports repeated pops in descending order") {
    MaxHeap heap;
    for (int value : {12, 4, 9, 18, 1, 7, 5, 3, 15}) {
        heap.push(value);
    }

    std::vector<int> popped;
    while (!heap.empty()) {
        popped.push_back(heap.pop());
    }

    REQUIRE(popped == std::vector<int>({18, 15, 12, 9, 7, 5, 4, 3, 1}));
}

TEST_CASE("MaxHeap handles negatives and duplicates consistently") {
    MaxHeap heap;
    for (int value : {-5, -10, -3, -5, -1, -8, -3}) {
        heap.push(value);
    }

    REQUIRE(heap.top() == -1);
    REQUIRE(heap.contains(-10));
    REQUIRE(heap.contains(-5));
    REQUIRE(heap.size() == 7u);

    REQUIRE(heap.pop() == -1);
    REQUIRE(heap.top() == -3);
}

TEST_CASE("MaxHeap toVector preserves heap contents for inspection") {
    MaxHeap heap;
    for (int value : {9, 1, 7, 3, 5}) {
        heap.push(value);
    }

    std::vector<int> data = heap.toVector();
    REQUIRE(data.size() == 5u);
    REQUIRE(std::count(data.begin(), data.end(), 9) == 1);
    REQUIRE(std::count(data.begin(), data.end(), 1) == 1);
    REQUIRE(std::count(data.begin(), data.end(), 7) == 1);
}
