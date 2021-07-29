//SPOJ USERNAME: cyberhero22
//STATUS: https://www.spoj.com/status/SDITSBST,cyberhero22/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Node {
    public:
        long value;
        int size;
        Node *root;
        Node *left;
        Node *right;
};

Node *search(Node *root, long value, int *counter) {
    if(!root) {
        return root;
    }
    else if(value < root->value) {
        *counter = *counter + root->size + 1;
        return search(root->left, value, counter);
    }
    else if(value > root->value) {
        return search(root->right, value, counter);
    }
    else if(value == root->value) {
        *counter = *counter + root->size + 1;
        return root;
    }
}
 
Node *insert(Node *root, long value) {
    if(!root) {
        Node *n = (Node*) malloc(sizeof(Node));
        n->size = 0;
        n->value = value;
        n->left = NULL;
        n->right = NULL;
        return n;
    }
    else if(value < root->value) {
        root->left = insert(root->left, value);
    }
    else if(value > root->value) {
        root->size++;
        root->right = insert(root->right, value);
    }
 
    return root;
}
 
int main(void) {
    Node tree;
    tree.root = NULL;
    vector<string> results;
    int qeueries;
    cin >> qeueries;
    int i = 0;   
    while(i < qeueries) {
        int parameter;
        long value;
        int counter = 0;
        cin >> parameter >> value;

        if(parameter == 1) {
            tree.root = insert(tree.root, value);
        }
        if(parameter == 2) {
            if(search(tree.root, value, &counter) != NULL) {
                results.push_back(to_string(counter));
            }
            else {
                results.push_back("Data tidak ada");
            }
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