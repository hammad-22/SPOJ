//SPOJ USERNAME: cyberhero22
//STATUS: https://www.spoj.com/status/SEGSQRSS,cyberhero22/

//segment tree and lazy propogation help taken from here: https://cp-algorithms.com/data_structures/segment_tree.html
//Helped understand how to work with segment in array format and utilized it to come up with a solution for this project

#include <vector>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

long long int arr[1000000];
long long int tree[1000000];
long long int sum[1000000];
long long int lazy[1000000];
vector<string> results;

void merge(long long int v) {
    tree[v] = tree[2*v] + tree[2*v+1];
	sum[v] = sum[2*v] + sum[2*v+1];
}

void build(long long int v, long long int tl, long long int tr) {
	if(tl == tr) {
		tree[v] = arr[tl]*arr[tl];
		sum[v] = arr[tl];
	} else {
		long long int tm = (tl + tr)/2;
		build(v*2, tl, tm);
		build(2*v+1, tm + 1, tr);
        merge(v);
	}
}

long long int push(long long int v, long long int tl, long long int tr) {
    if(lazy[v] != 0) {
        tree[v] = (tr - tl + 1)*(lazy[v]*lazy[v]);
        sum[v] = (tr - tl + 1)*lazy[v];
		if(tl != tr) {
				lazy[2*v] = lazy[v];
				lazy[2*v+1] = lazy[v];
		}
		lazy[v] = 0;
	}
    return (tl + tr) / 2;
}

void update1(long long int v, long long int tl, long long int tr, long long int l, long long int r, long long int new_val) {
	long long int tm = push(v, tl, tr);
    tree[v] = tree[v] + (tr - tl + 1)*(pow(new_val,2)) + 2*sum[v]*new_val;
    sum[v] = sum[v] + (tr - tl + 1)*new_val;
    if(tl != tr) {
        lazy[2*v] = lazy[2*v] + new_val;
        lazy[2*v+1] = lazy[2*v+1] + new_val;
    }

	update1(2*v, tl, tm, l, r, new_val);
	update1(2*v+1, tm + 1, tr, l, r, new_val);
	merge(v);
}

void update2(long long int v, long long int tl, long long int tr, long long int l, long long int r, long long int new_val) {
	long long int tm = push(v, tl, tr);
    sum[v] = (tr-tl + 1)*new_val;
    tree[v] = (tr - tl + 1)*(pow(new_val,2));
    if(tl != tr) {
        lazy[2*v] = new_val;
        lazy[2*v+1] = new_val;
    }

	update2(2*v, tl, tm, l, r, new_val);
	update2(2*v+1, tm + 1, tr, l, r, new_val);
	merge(v);
}

long long int query(long long int v, long long int tl, long long int tr, long long int l, long long int r) {
    if(l > r) {
        return 0;
    }
    if(l <= tl && tr <= r) {
		return tree[v];
	}
	long long int tm = push(v, tl, tr);

	return query(2*v, tl, tm, l, min(r, tm)) + query(2*v+1, tm + 1, tr, max(l, tm+1), r);
}

int main() {
	std::ios::sync_with_stdio(false);
	long long int T;
    long long int N;
    long long int Q;
    long long int i = 1;
    long long int j;
    long long int type;
    long long int p;
    long long int q;
    long long int x;

	cin >> T;
	while(i <= T) {
		results.push_back("Case " + to_string(i) + ":");
		
		cin >> N >> Q;
        j = 1;
		while(j <= N) {
			cin >> arr[j];
            j++;
		}
		build(1, 1, N);

		while(Q > 0) {
			cin >> type >> p >> q;
            
			if(type == 0) {
				cin >> x;
				update1(1, 1, N, p, q, x);
			} 
            else if(type == 1) {
				cin >> x;
				update2(1, 1, N, p, q, x);
            }
            else {
				results.push_back(to_string(query(1, 1, N, p, q)));
			}
            Q--;
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