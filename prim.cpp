// This is my implementation of prim's algorithm for use in the hackerrank challenge Prim's (MST) : Special Subtree
// https://www.hackerrank.com/challenges/primsmstsub/problem

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

class Heap {
    private:
    vector<int> heap;
    int* weights;
    int* indexes;
    int total;
    
    void heapifyUp(int loc) {
        if (loc == 0)
            return;

        int parentLoc = (loc-1)/2;
        if (weights[heap[loc]] < weights[heap[parentLoc]]) {
            int temp = heap[loc];
            heap[loc] = heap[parentLoc];
            heap[parentLoc] = temp;
            indexes[heap[loc]] = loc;
            indexes[heap[parentLoc]] = parentLoc;
            heapifyUp(parentLoc);
        }
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
            return;
        }
        if (weights[heap[loc]] > weights[heap[child]]) {
            int temp = heap[loc];
            heap[loc] = heap[child];
            heap[child] = temp;
            indexes[heap[loc]] = loc;
            indexes[heap[child]] = child;
            heapifyDown(child);
        }
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
        total = 0;
    }
    
    int pop_top() {
        int a = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        indexes[heap[0]] = 0;
        indexes[a] = -1;
        heapifyDown(0);
        total += weights[a];
        return a;
    }
    
    void update(int vertex, int weight) {
        if (indexes[vertex] == -1) {
            return;
        }
        if (weight < weights[vertex]) {
            weights[vertex] = weight;
            heapify(indexes[vertex]);
        }
    }
    
    int getTotal() {
        return total;
    }
    
    int getWeight(int vertex) {
        return weights[vertex];
    }
};


// Complete the prims function below.
int prims(int n, vector<vector<int>> edges, int start) {
    vector<vector<pair<int, int>>> adjacencyList(n);
    for (auto edge : edges) {
        int from = edge[0]-1; // zero index
        int to = edge[1]-1; // zero index
        int weight = edge[2];
        adjacencyList[from].push_back(make_pair(to, weight));
        adjacencyList[to].push_back(make_pair(from, weight));
    }
    
    Heap heap(n);
    heap.update(start-1, 0); // zero index
    
    int vertex;
    for (int i = 0; i < n; i++) {
        vertex = heap.pop_top();
        cout << "Popped " << vertex << " for " << heap.getWeight(vertex) << endl;
        for (int j = 0; j < adjacencyList[vertex].size(); j++) {
            heap.update(adjacencyList[vertex][j].first, adjacencyList[vertex][j].second);
        }
    }
    
    return heap.getTotal();
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nm_temp;
    getline(cin, nm_temp);

    vector<string> nm = split_string(nm_temp);

    int n = stoi(nm[0]);

    int m = stoi(nm[1]);

    vector<vector<int>> edges(m);
    for (int i = 0; i < m; i++) {
        edges[i].resize(3);

        for (int j = 0; j < 3; j++) {
            cin >> edges[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int start;
    cin >> start;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int result = prims(n, edges, start);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
