// This code works as part of the QHeap1 challenge on Hackerrank
// https://www.hackerrank.com/challenges/qheap1/problem

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void heapifyUp(vector<int>& heap, int loc) {
    // 0 - 1, 2
    // 1 - 3, 4
    // 2 - 5, 6
    // loc - 1 / 2
    // loc * 2 + 1
    // loc * 2 + 2
    if (loc == 0)
        return;
    
    int parentLoc = (loc-1)/2;
    if (heap[loc] < heap[parentLoc]) {
        int temp = heap[loc];
        heap[loc] = heap[parentLoc];
        heap[parentLoc] = temp;
        heapifyUp(heap, parentLoc);
    }
}

void heapifyDown(vector<int>& heap, int loc) {
    // swap
    int leftChild = loc * 2 + 1;
    int rightChild = loc * 2 + 2;
    int child;
    if (rightChild < heap.size()) {
        if (heap[leftChild] < heap[rightChild]) {
            child = leftChild;
        } else {
            child = rightChild;
        }
    } else if (leftChild < heap.size()) {
        child = leftChild;
    } else {
        return;
    }
    if (heap[loc] > heap[child]) {
        int temp = heap[loc];
        heap[loc] = heap[child];
        heap[child] = temp;
        heapifyDown(heap, child);
    }
}

void heapify(vector<int>& heap, int loc) {
    if (heap[loc] < heap[(loc-1)/2]) {
        heapifyUp(heap, loc);
    } else {
        heapifyDown(heap, loc);
    }
}

void insert(vector<int>& heap, int num) {
    // insert to end
    // heapify up
    heap.push_back(num);
    heapifyUp(heap, heap.size()-1);
}

void remove(vector<int>& heap, int num) {
    // insert last element to i's place, heapify up or down
    for (int i = 0; i < heap.size(); i++) {
        if (heap[i] == num) {
            heap[i] = heap.back();
            heap.pop_back();
            heapify(heap, i);
            return;
        }
    }
}

int main() {
    int q; // num queries
    cin >> q;
    
    vector<int> heap;
    
    int type;
    int num;
    for (int i = 0; i < q; i++) {
        cin >> type;
        if (type == 1) {
            cin >> num;
            insert(heap, num);
        } else if (type == 2) {
            cin >> num;
            remove(heap, num);
        } else {
            cout << heap[0] << endl;
        }
    }
    
    return 0;
}
