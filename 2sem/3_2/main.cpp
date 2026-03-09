#include <iostream>
using namespace std;

int main() {
    int n = 9;
	int arr[n] = {5, 2, 3, 4 ,1, 6, 9, 10, 8};
	int tmp, p=2, q=5;
	
	for (int i=p; i < (q+p)/2; i++) {
	    tmp = arr[i];
	    arr[i] = arr[n-i-1];
	    arr[n-i-1] = tmp;
	}
	
	for (int i=0; i < n; i++) {
	    cout<<arr[i]<<" ";
	}
	
    return 0;
}