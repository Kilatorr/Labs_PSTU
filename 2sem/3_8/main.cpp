#include <iostream>
using namespace std;

int main() {
    int n = 10;
	int arr[n] = {5, 2, 3, 10, 4 ,1, 6, 9, 10, 8};
	int counter=0;
	
    for (int i=0; i < n; i++) {
        if (arr[i]%2 == 0) {
            counter++;
        }
    }
    
    int arr_2[n+counter];
    int j=0;
    
    for (int i=0; i < n+counter; i++) {
        if (arr[i]%2 == 0) {
            arr_2[j++] = -1;
            arr_2[j++] = arr[i];
        } else {
            arr_2[j++] = arr[i];
        }
    }
    
    for (int i=0; i < n+counter; i++) {
        cout<<arr_2[i]<<" ";
    }
	
    return 0;
}
