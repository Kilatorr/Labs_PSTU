#include <iostream>
using namespace std;

int main() {
    int n = 10;
	int arr[n] = {5, 2, 3, 10, 4 ,1, 6, 9, 10, 8};
	int max=arr[0], min=arr[0];
	
    for (int i=1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        } else if (arr[i] < min) {
            min = arr[i];
        }
    }
    
    cout<<max<<endl<<min<<endl;	
	
    return 0;
}