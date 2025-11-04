//
// Created by Manju Muralidharan on 10/19/25.
// Modified by Bassam Siagian, finished 11/3/2025
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()

        // add new element at the end
        data[size] = idx;
        int current = size;
        size++;


        // bubble up new element until correct position
        // min-heap property: parent <= children
        while (current > 0) {
            int parent = (current - 1) / 2;

            // compare weights of current nodes to parent
            if (weightArr[data[current]] < weightArr[data[parent]]) {

            // swap if smaller
                int temp = data[current];
                data[current] = data[parent];
                data[parent] = temp;
                current = parent; // move up to parent's position
            } else {
                break; // to stop bubbling up if satisfied
            }
        }
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()


        if (size == 0) // empty heap condition
            return -1;// placeholder

        // bubble down to restore structure
        int minItem = data[0];
        data[0] = data[size - 1];
        size--;

        // Downheap
        int current = 0;
        while (2 * current + 1 < size) { // continue while node has at least left child
            int leftChild = 2 * current + 1; // calculate left child index
            int rightChild = 2 * current + 2; // calculate right child index
            int smallest = current; // assume it's smallest

            // compare with left to find smallest
            if (leftChild < size && weightArr[data[leftChild]] < weightArr[data[smallest]]) {
                smallest = leftChild;
            }

            // compare with right if find smallers
            if (rightChild < size && weightArr[data[rightChild]] < weightArr[data[smallest]]) {
                smallest = rightChild;
            }

            // if current node not smallest, swap with smallest child
            if (smallest != current) {
                int temp = data[current];
                data[current] = data[smallest];
                data[smallest] = temp;
                current = smallest;
            } else {
                break; // satisfied condition, stop bubbling down
            }
        }

        return minItem;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent

        int currentIdx = data[pos];
        int currentWeight = weightArr[currentIdx];

        // Move the element until correct position
        while (pos > 0) {
            int parent = (pos - 1) / 2;
            int parentWeight = weightArr[data[parent]];

            //Stop if meets
            if (currentWeight >= parentWeight) {
                break;
            }

            data[pos] = data[parent];
            pos = parent;
        }

        data[pos] = currentIdx;
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child

        while (2 * pos + 1 < size) {
            int leftChild = 2 * pos + 1;
            int rightChild = 2 * pos + 2;
            int smallest = pos;

            if (leftChild < size && weightArr[data[leftChild]] < weightArr[data[smallest]]) {
                smallest = leftChild;
            }
            if (rightChild < size && weightArr[data[rightChild]] < weightArr[data[smallest]]) {
                smallest = rightChild;
            }

            if (smallest != pos) {
                int temp = data[pos];
                data[pos] = data[smallest];
                data[smallest] = temp;
                pos = smallest;
            } else {
                break;
            }
        }
    }
};

#endif