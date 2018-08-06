// This is implementation of dijkstra's algorithm for solving the  Dijkstra: Shortest Reach 2 problem on hackerrank
// https://www.hackerrank.com/challenges/dijkstrashortreach/problem

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);
class Heap {
    private:
    vector<int> heap;
    int* weights;
    int* indexes;
    
    void heapifyUp(int loc) {
        if (loc == 0) {
            indexes[heap[loc]] = loc;
            return;
        }

        int parentLoc = (loc-1)/2;
        if (weights[heap[loc]] < weights[heap[parentLoc]]) {
            int temp = heap[loc];
            heap[loc] = heap[parentLoc];
            heap[parentLoc] = temp;
            heapifyUp(parentLoc);
        }
        indexes[heap[loc]] = loc;
    }

    void heapifyDown(int loc) {
        int leftChild = loc * 2 + 1;
        int rightChild = loc * 2 + 2;
        int child;
        if (rightChild < heap.size()) {
            if (weights[heap[leftChild]] < weights[heap[rightChild]]) {
                child = leftChild;
            } else {
                child = rightChild;
            }
        } else if (leftChild < heap.size()) {
            child = leftChild;
        } else {
            indexes[heap[loc]] = loc;
            return;
        }
        if (weights[heap[loc]] > weights[heap[child]]) {
            int temp = heap[loc];
            heap[loc] = heap[child];
            heap[child] = temp;
            heapifyDown(child);
        }
        indexes[heap[loc]] = loc;
    }

    void heapify(int loc) {
        if (weights[heap[loc]] < weights[heap[(loc-1)/2]]) {
            heapifyUp(loc);
        } else {
            heapifyDown(loc);
        }
    }
    public:
    Heap(int n) {
        weights = new int[n];
        indexes = new int[n];
        for (int i = 0; i < n; i++) {
            weights[i] = INT_MAX;
            heap.push_back(i);
            indexes[i] = i;
        }
    }
    
    int pop_top() {
        int a = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        indexes[heap[0]] = 0;
        indexes[a] = -1;
        heapifyDown(0);
        return a;
    }
    
    void update(int vertex, int weight) {
        if (indexes[vertex] == -1) {
            return;
        }
        if (weight < weights[vertex]) {
            weights[vertex] = weight;
            heapifyUp(indexes[vertex]);
        }
    }
    
    int getWeight(int vertex) {
        return weights[vertex];
    }
};


// Complete the prims function below.
void shortestReach(int n, vector<vector<pair<int, int>>>& adjacencyList, int start) {
    
    Heap heap(n);
    heap.update(start, 0);
    
    vector<int> distances;
    for (int i = 0; i < n-1; i++) {
        distances.push_back(-1);
    }
    
    int vertex;
    for (int i = 0; i < n; i++) {
        vertex = heap.pop_top();
        int weight = heap.getWeight(vertex);
        if (weight == INT_MAX) {
            break;
        }
        if (vertex < start) {
            distances[vertex] = weight;
        } else {
            distances[vertex-1] = weight;
        }
        for (int j = 0; j < adjacencyList[vertex].size(); j++) {
            heap.update(adjacencyList[vertex][j].first, adjacencyList[vertex][j].second+weight);
        }
    }
    
    for (int i = 0; i < distances.size(); i++) {
        cout << distances[i] << " ";
    }
    cout << endl;
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n, m, s;
        cin >> n >> m;
        
        vector<vector<pair<int, int>>> adjacencyList(n);
        for (int j = 0; j < m; j++) {
            int from, to, weight;
            scanf("%d %d %d\n", &from, &to, &weight);
            
            adjacencyList[from-1].push_back(make_pair(to-1, weight));
            adjacencyList[to-1].push_back(make_pair(from-1, weight));
        }
        cin >> s;
        
        shortestReach(n, adjacencyList, s-1);
    }
    return 0;
}
