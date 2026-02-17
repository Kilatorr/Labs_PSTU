#include <iostream>
using namespace std;

int main() {
    int n = 10;
	int arr[n] = {5, 2, 3, 4 ,1, 6, 9, 10, 8, 7};
	int key;
	int tmp;
	int j;
	
	for (int i=1; i < n; i++) {
	    key = arr[i];
	    j = i-1;
	    while (j >= 0 && arr[j] > key) {
	        if (arr[j+1] < arr[j]) {
	            tmp = arr[j+1];
	            arr[j+1] = arr[j];
	            arr[j] = tmp;
	        }
	        j--;
	    }
	    arr[j+1] = key;
	}
	
	for (int i=0; i < n; i++) {
	    cout<<arr[i]<<" ";
	}
	
    return 0;
}