#include <iostream>
using namespace std;

int main() {
    int n = 10;
	int arr[n] = {50, 2, 7, 4 ,1, 6, 9, 100, 7, 7};
	int tmp;
	
	for(int i=0; i < n-1; i++) {            
        for(int j=0; j < n-1; j++) {     
            if (arr[j+1] < arr[j]) {
                tmp = arr[j+1]; 
                arr[j+1] = arr[j]; 
                arr[j] = tmp;
            }
        }
    }
	
	for (int i=0; i < n; i++) {
	    cout<<arr[i]<<" ";
	}
	
    return 0;

}