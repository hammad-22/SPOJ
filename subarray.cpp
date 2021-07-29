//SPOJ USERNAME: cyberhero22
//STATUS: https://www.spoj.com/status/ARRAYSUB,cyberhero22/
#include <iostream>
#include <deque>
using namespace std;

void arraysub(int *arr, int n, int k) {
    int i, j;
    int highest = arr[0];
    for(i = 0; i < n - k + 1; i++) {
        highest = arr[i];
        for(j = i; j < i+k && j < n; j++) {
            if(arr[j] > highest) {
                highest = arr[j];
            }
        }
        if(i + 1 >= n - k + 1) {
            cout << highest;
        }
        else {
            cout << highest << " ";
        }
    }
}

int main (int argc , char *argv[]) {

	int n, k;
	int *array;

	scanf("%d" , &n);

	array = ( int * ) malloc (n*sizeof(int));

	int i = 0;
	while(i < n) {
		scanf("%d" , &array[i]);
        i++;
	}
	scanf("%d" , &k);

	arraysub(array, n, k);

	return 0;
}