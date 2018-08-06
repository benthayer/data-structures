// This code works as part of the Merging Communities Challenge on HackerRank
// https://www.hackerrank.com/challenges/merging-communities/problem

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int find(int* people, int i) {
    if (people[i] < 0) { // representative member
        return i;
    }
    int a = find(people, people[i]); // find representative member
    people[i] = a; // path compression
    return a;
}

int getSize(int* people, int i) {
    int a = find(people, i); // get representative member
    return -1 * people[a]; // size is negative
}

void connect(int* people, int i, int j) {
    int a = find(people, i); // rep member of i
    int b = find(people, j); // rep member of j
    if (a == b) {
        return;
    }
    if (people[a] < people[b]) { // i's set has more members
        people[a] += people[b];
        people[b] = a;
    } else { // js set has more members
        people[b] += people[a];
        people[a] = b;
    }
}


int main() {
    int n;
    int q;
    cin >> n >> q;
    
    int* people = new int[n+1];
    for (int i = 0; i < n+1; i++) {
        people[i] = -1;
    }
    
    char c;
    for (int i = 0; i < q; i++) {
        cin >> c;
        if (c == 'M') {
            int i, j;
            cin >> i >> j;
            connect(people, i, j);
        } else {
            int i;
            cin >> i;
            cout << getSize(people, i) << endl;
        }
    }
    return 0;
}
