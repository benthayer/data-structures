#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>

using namespace std;

class SkipNode {
    public:
    int element;
    vector<SkipNode*> nexts;
    SkipNode() {}
    SkipNode(int i, int n):element(i) {
        nexts = vector<SkipNode*>(n+1);
    }
};

SkipNode* find(SkipNode* node, int i) {
    int level = node->nexts.size()-1;
    while (level >= 0) {
        while((node->nexts[level] != nullptr) && (node->nexts[level]->element <= i)) {
            node = node->nexts[level];
        }
        level--;
    }
    if (node->element == i)
        return node;
    return nullptr;
}

void insert(SkipNode* node, int insertVal) {
    int insertLevel = 0;
    while (rand() % 2 == 0) {
        insertLevel++;
    }

    cout << "Inserting " << insertVal << " at level " << insertLevel << endl;

    SkipNode* insertNode = new SkipNode(insertVal, insertLevel);
    int level = node->nexts.size() - 1;
    
    // expand head if necessary
    if (insertLevel >= node->nexts.size()) {
        while (node->nexts.size() <= insertLevel) {
            node->nexts.push_back(insertNode);
        }
    }

    while (level >= 0) {
        while((node->nexts[level] != nullptr) && (node->nexts[level]->element < insertVal)) {
            node = node->nexts[level];
        }
        if (level <= insertLevel) {
            insertNode->nexts[level] = node->nexts[level];
            node->nexts[level] = insertNode;
        }
        level--;
    }
}

void remove(SkipNode* head, int removeVal) {
    cout << "Removing " << removeVal << endl;
    SkipNode* node = head;
    int level = node->nexts.size()-1;
    while (level > 0) {
        while((node->nexts[level] != nullptr) && (node->nexts[level]->element < removeVal)) {
            node = node->nexts[level];
        }
        if (node->nexts[level] != nullptr && node->nexts[level]->element == removeVal) {
            node->nexts[level] = node->nexts[level]->nexts[level];
        }
        level--;
    }

    while((node->nexts[level] != nullptr) && (node->nexts[level]->element < removeVal)) {
        node = node->nexts[level];
    }
    if (node->nexts[level]->element == removeVal) {
        SkipNode* toDelete = node->nexts[level];
        node->nexts[level] = node->nexts[level]->nexts[level];
        delete toDelete;
    }

    while (head->nexts[head->nexts.size()-1] == nullptr) {
        head->nexts.pop_back();
    }
}

void print(SkipNode* node) {
    for (int level = node->nexts.size()-1; level >= 0; level--) {
        SkipNode* nextNode = node;
        cout << "Level " << level << ": ";
        while (nextNode->nexts[level] != nullptr) {
            nextNode = nextNode->nexts[level];
            cout << nextNode->element << " ";
        }
        cout << endl;
    }
}

int main() {
    srand(time(NULL));
    SkipNode* head = new SkipNode();
    int n = 100;
    for (int i = 0; i < n; i++) {
        int insertVal = i;
        insertVal = rand() % n;
        while (find(head, insertVal) != nullptr) {
            insertVal = rand() % n;
        }
        
        insert(head, i);
        print(head);
        cout << endl;
    }

    for (int i = 0; i < n; i++) {
        cout << "Finding " << i << endl;
        SkipNode* a = find(head, i);
        cout << "Found " << a->element << endl << endl;
    }

    for (int i = 0; i < n; i++) {
        int removeVal = i;
        removeVal = rand() % n;
        while (find(head, removeVal) == nullptr) {
            removeVal = rand() % n;
        }
        
        remove(head, removeVal);
        print(head);
        cout << endl;
    }

    cout << "complete" << endl;
    return 0;
}