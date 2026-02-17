#include <iostream>
using namespace std;

int main() {
    int n = 10;
	int arr[n] = {5, 2, 77, 4 ,8, 6, 97, 10, 80, 7};
	int min, tmp;
	
	for (int i=0; i < n; i++) {
	    min = i;
	    for (int j=i+1; j < n; j++) {
	        if (arr[j] < arr[min]) {
	            min = j;
	        }
	    }
	    if (arr[min] < arr[i]) {
	        tmp = arr[min];
	        arr[min] = arr[i];
	        arr[i] = tmp;
	    }
	}
	
	for (int i=0; i < n; i++) {
	    cout<<arr[i]<<" ";
	}
	
    return 0;
}