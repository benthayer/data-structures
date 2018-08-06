#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class AVLNode {
    public:
    char element;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(char val):element(val), height(0), left(nullptr), right(nullptr) {}

    void print() {
        cout << "(" << element;
        if (left != nullptr || right != nullptr) {
            cout << ", ";
            if (left == nullptr) {
                cout << "NULL, ";
            } else {
                cout << left->element << ", ";
            }
            if (right == nullptr) {
                cout << "NULL";
            } else {
                cout << right->element << "";
            }
        }

        cout << ") ";

        if (left != nullptr) {
            left->print();
        }
        if (right != nullptr) {
            right->print();
        }
    }
};

int getHeight(AVLNode* ptr) {
    if (ptr == nullptr) {
        return -1;
    } else {
        return ptr->height;
    }
}

void updateHeight(AVLNode* ptr) {
    if (ptr == nullptr) 
        return;
    int leftHeight = getHeight(ptr->left);
    int rightHeight = getHeight(ptr->right);

    ptr->height = max(leftHeight, rightHeight) + 1;
}

void leftRotate(AVLNode*& ptr) {
    AVLNode* newTop = ptr->right;
    ptr->right = newTop->left;
    newTop->left = ptr;
    ptr = newTop;
    
    updateHeight(ptr->left);
    updateHeight(ptr);
}

void rightRotate(AVLNode*& ptr) {
    AVLNode* newTop = ptr->left;
    ptr->left = newTop->right;
    newTop->right = ptr;
    ptr = newTop;
    
    updateHeight(ptr->right);
    updateHeight(ptr);
}

void rebalance(AVLNode*& ptr, int balance) {
    if (balance > 1) {
        // rebalance
        if (getHeight(ptr->right->left) > getHeight(ptr->right->right)) {
            rightRotate(ptr->right);
        }
        leftRotate(ptr);
    } else if (balance < -1) {
        if (getHeight(ptr->left->right) > getHeight(ptr->left->left)) {
            leftRotate(ptr->left);
        }
        rightRotate(ptr);
    }
}

void rebalance(AVLNode*& ptr) {
    if (ptr == nullptr) {
        return;
    }
    
    int leftHeight = getHeight(ptr->left);
    int rightHeight = getHeight(ptr->right);

    int balance = rightHeight - leftHeight;

    rebalance(ptr, balance);
}

void insert(AVLNode*& ptr, int insertVal) {
    if (ptr == nullptr) {
        ptr = new AVLNode(insertVal);
        return;
    }
    if (insertVal < ptr->element) {
        insert(ptr->left, insertVal);
    } else {
        insert(ptr->right, insertVal);
    }

    int leftHeight = getHeight(ptr->left);
    int rightHeight = getHeight(ptr->right);
    ptr->height = max(leftHeight, rightHeight) + 1;

    int balance = rightHeight - leftHeight;
    rebalance(ptr, balance);
}

void swapAndRemoveLeft(AVLNode*& ptr, AVLNode*& replacePtr) {
    if (ptr->right == nullptr) {
        if (ptr == replacePtr->left) {
            AVLNode* oldPtr = replacePtr;
            replacePtr = ptr;
            ptr->right = oldPtr->right;

            delete oldPtr;
        } else {
            AVLNode* oldPtr = replacePtr;
            replacePtr = ptr;
            ptr = ptr->left;

            replacePtr->left = oldPtr->left;
            replacePtr->right = oldPtr->right;
            replacePtr->height = oldPtr->height;

            delete oldPtr;
        }
    } else {
        swapAndRemoveLeft(ptr->right, replacePtr);
    }
}

void swapAndRemoveRight(AVLNode*& ptr, AVLNode*& replacePtr) {
    if (ptr->left == nullptr) {
        if (ptr == replacePtr->right) {
            AVLNode* oldPtr = replacePtr;
            replacePtr = ptr;
            ptr->left = oldPtr->left;

            delete oldPtr;
        } else {
            AVLNode* oldPtr = replacePtr;
            replacePtr = ptr;
            ptr = ptr->right;

            replacePtr->left = oldPtr->left;
            replacePtr->right = oldPtr->right;
            replacePtr->height = oldPtr->height;

            delete oldPtr;
        }
    } else {
        swapAndRemoveRight(ptr->left, replacePtr);
    }
}

void rebalanceLeft(AVLNode*& ptr) {
    if (ptr == nullptr)
        return;
    rebalanceLeft(ptr->right);
    updateHeight(ptr);
    rebalance(ptr);
}

void rebalanceRight(AVLNode*& ptr) {
    if (ptr == nullptr)
        return;
    rebalanceRight(ptr->left);
    updateHeight(ptr);
    rebalance(ptr);
}

void remove(AVLNode*& ptr, char removeVal) {
    if (ptr == nullptr) {
        return;
    }
    if (removeVal < ptr->element) {
        remove(ptr->left, removeVal);
    } else if (removeVal > ptr->element) {
        remove(ptr->right, removeVal);
    } else {
        // remove this one
        if (ptr->left == nullptr) {
            AVLNode* toRemove = ptr;
            ptr = toRemove->right;
            delete toRemove;
        } else if (ptr->right == nullptr) {
            AVLNode* toRemove = ptr;
            ptr = toRemove->left;
            delete toRemove;
        } else {
            // neither are null
            if (ptr->left->height >= ptr->right->height) {
                swapAndRemoveLeft(ptr->left, ptr);
                rebalanceLeft(ptr->left);
            } else {
                swapAndRemoveRight(ptr->right, ptr);
                rebalanceRight(ptr->right);
            }

        }
    }
    rebalance(ptr);
}

int main() {
    string s = "mnolkqphia";
    AVLNode* head = nullptr;

    for (char c: s) {
        insert(head, c);
        cout << c << " ";
        head->print();
        cout << endl;
    }

    cout << "Removing" << endl;
    
    for (char c: s) {
        cout << c << " ";
        remove(head, c);
        if (head == nullptr) {
            cout << "Empty" << endl;
        } else {
            head->print();
            cout << endl;
        }
    }
    return 0;
}