#include <iostream>
using namespace std;

int main() {
    int n = 10;
	int arr[n] = {5, 2, 3, 10, 4 ,1, 6, 9, 10, 8};
	int k=2;
	k = k%n;
	int tmp[k];
	
    for (int i=0; i < n-k; i++) {
        if (i < k) {
            tmp[i] = arr[i];
        }
        arr[i] = arr[i+k];
    }
    for (int i=0; i < k; i++) {
        arr[n-k+i] = tmp[i];
    }
    
	for (int i=0; i < n; i++) {
	    cout<<arr[i]<<" ";
	}
	
    return 0;
}