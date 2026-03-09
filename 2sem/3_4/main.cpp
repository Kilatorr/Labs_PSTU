#include <iostream>
using namespace std;

int main() {
    int n = 10;
	int arr[n] = {5, 2, 3, 10, 4 ,1, 6, 9, 10, 8};
	bool is_sorted = true;
	
	for (int i=1; i < n; i++) {
	    if (arr[i] < arr[i-1]) {
	        is_sorted = false;
	        break;
	    }
	}
	
	cout<<is_sorted;
	
    return 0;
}