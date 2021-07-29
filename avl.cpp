//SPOJ USERNAME: cyberhero22
//STATUS: https://www.spoj.com/status/SDITSAVL,cyberhero22/

//AVL algorithm help: https://www.youtube.com/watch?v=jDM6_TnYIqE
//https://www.ics.uci.edu/~goodrich/teach/cs260P/notes/AVLTrees.pdf
//Helped with the insertion, rotation, balance, and update functions. Only had
//pseudocode and trees to help with general idea and understanding

#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Node {
    public:
        long value;
        long height;
        long balance; 
        long leftSize;
        long rightSize;
        Node *root;
        Node *left;
        Node *right;
};

vector<string> results;

void update(Node *node)  {
    long leftNodeHeight = -1;
    long rightNodeHeight = -1;
    
    if(node->left != NULL) {
        leftNodeHeight = node->left->height;
    }
    if(node->right != NULL) {
        rightNodeHeight = node->right->height;
    }
    node->height = 1 + max(leftNodeHeight, rightNodeHeight);
    node->balance = rightNodeHeight - leftNodeHeight;
}

Node *leftRotation(Node *node) {
    Node* temp = node->right;
    node->right = temp->left;
    temp->left = node;

    if(node->right != NULL) {
        node->rightSize = node->right->rightSize + node->right->leftSize + 1;
    }
    else node->rightSize = 0;

    if(node != NULL) {
        temp->leftSize = node->leftSize + node->rightSize + 1;
    }
    else temp->leftSize = 0;

    update(node);
    return temp;
}

Node *rightRotation(Node *node) {
    Node* temp = node->left;
    node->left = temp->right;
    temp->right = node;

    if(node->left != NULL) {
        node->leftSize = node->left->leftSize + node->left->rightSize + 1;
    }
    else node->leftSize = 0;
    
    if(node != NULL) {
        temp->rightSize = node->rightSize + node->leftSize + 1;
    }
    else temp->rightSize = 0;

    update(node);
    return temp;
}

Node *balance(Node *node) {
    if(node->balance == -2) {
        if(node->left->balance <= 0) 
            return rightRotation(node);
        else {
            node->left = leftRotation(node->left);
            return rightRotation(node);
        }
    }
    else if(node->balance == 2) {
        if(node->right->balance >= 0) {
            return leftRotation(node);
        }
        else {
            node->right = rightRotation(node->right);
            return leftRotation(node);
        }
    }
    return node;
}

Node *insert(Node *node, long value) {
    if(!node) {
        Node *node = (Node*) malloc(sizeof(Node));
        node->value = value;
        node->height = 0;
        node->balance = 0;
        node->leftSize = 0;
        node->rightSize = 0;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    if(value < node->value) {
        node->leftSize++;
        node->left = insert(node->left, value);
    }
    if(value >= node->value) {
        node->rightSize++;
        node->right = insert(node->right, value);
    }

    update(node);
    node = balance(node);
    return node;
}

void search(Node *node, long value, int *counter) {
    while(node) {
        if(value >= node->value) {
            *counter = *counter + node->leftSize + 1;
            if(value == node->value) {
                results.push_back(to_string(*counter));
                break;
            }
            node = node->right;
        }
        else if(value < node->value) {
            node = node->left;
        }
    }
    results.push_back("Data tidak ada");
}

int main(void) {
    std::ios::sync_with_stdio(false);
    Node tree;
    tree.root = NULL;
    int qeueries;
    cin >> qeueries;
    int i = 0;
    while(i < qeueries) {
        int counter = 0;
        int parameter = 0;
        int val = 0;
        cin >> parameter >> val;

        if(parameter == 1) {
            tree.root = insert(tree.root, val);
        }
        if(parameter == 2) {
            search(tree.root, val, &counter); 
        }
        i++;
    }

    i = 0;
    while(i < results.size()) {
        cout << results[i] << "\n";
        i++;
    }

    return 0;
}