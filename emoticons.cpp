//SPOJ USERNAME: cyberhero22
//STATUS: https://www.spoj.com/status/EMOTICON,cyberhero22/

//Used Trie array implementation since it got rid of my constant timeout error
//Implementation example for Trie array in this discussion: https://leetcode.com/problems/implement-trie-prefix-tree/discuss/58901/trie-using-array
//More help with setting up trie insertion and iteration here: https://leetcode.com/discuss/general-discussion/680706/Article-on-Trie.-General-Template-and-List-of-problems
//and here:https://codeforces.com/blog/entry/50357
//Memset idea from here: https://www.techiedelight.com/memory-efficient-trie-implementation-using-map-insert-search-delete/
//BFS for iterating through Trie from previous project
//Did not copy or plagirize code from leetcode, just used the discussion to see how to implement for this project due to constant timeout errors from previous project implementation

#include <iostream>
#include <cstdio>
#include <vector>
#include <string.h>

using namespace std;

class Node{
    public:
        int trie[1000][1000]; 
        long counter;
        int parent[1000]; 
        int child[1000];
        int right[1000];
        Node() {
            for(int i = 0; i < 1000; i++) {
                child[i] = NULL;
                parent[i] = NULL;
                for(int j = 0; j < 1000; j++) {
                    trie[i][j] = NULL;
                }
            }
            trie[1000][1000];
            counter = 0;
            parent[1000];
            child[1000];
            right[1000];
        }
};

Node *n = new Node;

void insert(char emote[]) {
    int x = 0;
    int i = 0;
    while(emote[i] > 1) {
        if(n->trie[x][emote[i]] != 0) {
            n->right[n->counter] = 0;
        }
        else if(n->trie[x][emote[i]] == 0) {
            n->counter++;
            n->trie[x][emote[i]] = n->counter;
            n->right[n->counter] = n->counter;
        }
        x = n->trie[x][emote[i]];
        i++;
    }
    n->child[x] = true;
}

int main(void) {
    int M;
    int N;
    int i;
    int y;
    int f;
    int total;
    vector<int> results;
    vector<int> stack;
    while(true) {
        memset(n->trie, 0, sizeof n->trie);
        memset(n->child, 0, sizeof n->child);
        memset(n->parent, 0, sizeof n->parent);
        memset(n->right, 0, sizeof n->right);

        n->trie[1000][1000]; 
        n->counter = 0;
        n->parent[1000]; 
        n->child[1000];
        n->right[1000];

        cin >> M >> N;

        if (M == 0 || N == 0) {
            break;
        }

        cin.ignore(1,'\n');
        
        i = 0;
        while(i < M) {
            char emote[1000]; 
            insert(fgets(emote,1000,stdin));
            i++;
        }

        stack.push_back(0); 
        n->parent[0] = -1;
        while(stack.size()) {
            int top = stack.front(); 
            stack.erase(stack.begin());
            y = 0;
            while(y < 1000) {
                if(n->trie[top][y] != 0) {
                    if(n->parent[top] < 0) {
                        n->parent[n->trie[top][y]] = 0;
                        n->right[n->trie[top][y]] = 0;
                    }
                    else if(n->parent[top] >= 0) {
                        int j = n->parent[top];
                        while(j >= 0) {
                            if(n->trie[j][y] != 0) {
                                n->parent[n->trie[top][y]] = n->trie[j][y];
                                n->child[n->trie[top][y]] = n->child[n->trie[top][y]] | n->child[n->trie[j][y]];
                                n->right[n->trie[top][y]] = n->child[n->trie[top][y]] | n->right[n->trie[j][y]];
                                break;
                            }
                            else {
                                j = n->parent[j];
                            }
                        }
                    }
                    else {
                        break;
                    }
                    stack.push_back(n->trie[top][y]);
                }
                y++;
            }
        }
        stack.clear();

        total = 0;
        f = 0;
        while(f < N) {
            char emote[1000];
            fgets(emote, 1000, stdin);
            int curr = 0;
            int res = 0;
            int i = 0;
            while(emote[i] > 0) {
                int j = curr;
                while(j >= 0) {
                    if(n->trie[j][emote[i]] != 0) {
                        curr = n->trie[j][emote[i]];
                        if(n->child[n->trie[j][emote[i]]] > 0) {
                            res++;
                            curr = 0; 
                        }
                        break;
                    }
                    else {
                        j = n->parent[j];
                    }
                    if(j < 0) {
                        curr = 0;
                        break;
                    }
                }
                i++;
            }
            total = total + res;
            f++;
        }
        results.push_back(total);
    }

    i = 0;
    while(i < results.size()) {
        cout << results[i] << "\n";
        i++;
    }
    results.clear();
    return 0;
}