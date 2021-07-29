//SPOJ USERNAME: cyberhero22
//STATUS: https://www.spoj.com/status/INVENT,cyberhero22/


//Kruskals algorithm help: https://www.programiz.com/dsa/kruskal-algorithm
//Only used for understanding the algorithm pseudo-code to see how it can 
//be implemenetd for this project, didn't copy or plagairize

#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

int findSet(int x, unsigned long long parent [15000]){
    return parent[x] == x ? x : parent[x] = findSet(parent[x], parent);
}

int main(){
    std::ios::sync_with_stdio(false);
    int problems;
    cin >> problems;
    while(problems) {
        pair <unsigned long long, pair<unsigned long, unsigned long> > edges [15000]; //w, <a,b>
        unsigned long long heights [15000], weight [15000], parent [15000];
        int N;
        int i = 0;
        cin >> N; 
        unsigned long long total = 0;
        while(i < N-1) {
            cin >> edges[i].second.first >> edges[i].second.second >> edges[i].first; //a, b, w
            total = total + edges[i].first;
            if(i+1 == N-1) {
                parent[i+2] = i+2;
                heights[i+2] = 1;
                weight[i+2] = 1;
            }
            parent[i+1] = i+1;
            heights[i+1] = 1;
            weight[i+1] = 1;
            i++;
        }
        sort(edges, edges+N-1);
        i = 0;
        while(i < N-1){
            total = total + (weight[findSet(edges[i].second.first, parent)]*weight[findSet(edges[i].second.second, parent)]-1)*(edges[i].first+1);
            int a = findSet(edges[i].second.first, parent);
            int b = findSet(edges[i].second.second, parent);
            if(heights[a] > heights[b]) {
                parent[b] = a;
                weight[a] = weight[a] + weight[b];
            }
            else if(heights[a] <= heights[b]) {
                parent[a] = b;
                weight[b] = weight[b] + weight[a];
            }
            i++;
        }
        if(problems > 1) {
            cout << total << '\n';
        }
        else {
            cout << total;
        }
        problems--;
    }
    return 0;
}