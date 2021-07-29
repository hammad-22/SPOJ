//SPOJ USERNAME: cyberhero22
//STATUS: https://www.spoj.com/status/ADAINDEX,cyberhero22/

//Help taken from https://medium.com/basecs/trying-to-understand-tries-3ec6bede0014
//as well as starting code from exam

#include <cstdio>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

class Node {
    public:
        int counter;
        Node* child[26];
        char* substr[26];
        Node() {
            counter = 0;
            for(int i = 0; i < 26; i++) {
                child[i] = NULL;
                substr[i] = "";
            }
    }
};

void insert(Node* node, char *str) {
    Node* curr = node;
    int i = 0;
    while(i < strlen(str)) {
        if (curr->child[(str[i] - 'a')] == NULL) {
            Node* temp = (Node*) malloc(sizeof(Node));
            curr->child[(str[i] - 'a')] = temp;
        }
        curr = curr->child[(str[i] - 'a')];
        curr->counter = curr->counter + 1;
        i++;
    }
}

int query(Node* node, char *str) {
    Node* curr = node;
    int i = 0;
    while(i < strlen(str)) {
        if (curr->child[(str[i] - 'a')] == NULL)
            break;
        curr = curr->child[(str[i] - 'a')];
        if (i == strlen(str) - 1){
            return curr->counter;
        }
        i++;
    }
    return 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    int N;
    int Q;
    int i;
    Node *root = (Node*) malloc(sizeof(Node));
    vector<string> results;

    cin >> N >> Q;

    while(i < N) {
        char s[150000];
        cin >> s;

        insert(root, s);
        i++;
    }
    i = 0;
    while(i < Q) {
        char s[150000];
        cin >> s;

        results.push_back(to_string(query(root, s)));
        i++;
    }
    i = 0;
    while(i < results.size()) {
        cout << results[i] << "\n";
        i++;
    }
}