// This is my implementation of kruskal's algorithm for use in the hackerrank challenge Kruskal (MST): Really Special Subtree
// https://www.hackerrank.com/challenges/kruskalmstrsub/problem

#include <bits/stdc++.h>

using namespace std;

int find(int* ds, int i) {
    if (ds[i] < 0) { // representative member
        return i;
    }
    int a = find(ds, ds[i]); // find representative member
    ds[i] = a; // path compression
    return a;
}

bool connected(int* ds, int i, int j) {
    int a = find(ds, i); // rep member of i
    int b = find(ds, j); // rep member of j
    return a == b;
}

int getSize(int* ds, int i) {
    int a = find(ds, i); // get representative member
    return -1 * ds[a]; // size is negative
}

void connect(int* ds, int i, int j) {
    int a = find(ds, i); // rep member of i
    int b = find(ds, j); // rep member of j
    if (a == b) {
        return;
    }
    if (ds[a] < ds[b]) { // i's set has more members
        ds[a] += ds[b];
        ds[b] = a;
    } else { // js set has more members
        ds[b] += ds[a];
        ds[a] = b;
    }
}


int main()
{
    int g_nodes;
    int g_edges;

    cin >> g_nodes >> g_edges;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> g_from(g_edges);
    vector<int> g_to(g_edges);
    vector<int> g_weight(g_edges);

    for (int i = 0; i < g_edges; i++) {
        cin >> g_from[i] >> g_to[i] >> g_weight[i];
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Write your code here.
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < g_edges; i++) {
        edges.push_back(make_tuple(g_from[i], g_to[i], g_weight[i]));
    }
    
    sort(edges.begin(), edges.end(),
        [](tuple<int, int, int> x1, tuple<int, int, int> x2) {
            if (get<2>(x1) == get<2>(x2)) {
                return get<0>(x1) + get<1>(x1) < get<0>(x2) + get<1>(x2);
            }
            return get<2>(x1) < get<2>(x2);
    });
    
    int numSubgraphs = g_nodes;
    
    int* ds = new int[g_nodes+1]; // since verticies are 1 indexed
    for (int i = 0; i < g_nodes+1; i++) {
        ds[i] = -1;
    }
    
    int totalWeight = 0;
    
    for (auto edge : edges) {
        int from = get<0>(edge);
        int to = get<1>(edge);
        int weight = get<2>(edge);
        
        if (!connected(ds, from, to)) {
            connect(ds, from, to);
            totalWeight += weight;
        }
    }
    
    cout << totalWeight;

    return 0;
}
