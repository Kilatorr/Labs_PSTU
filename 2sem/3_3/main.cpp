#include <iostream>
using namespace std;

int main() {
    int n = 10;
	int arr[n] = {5, 2, 3, 10, 4 ,1, 6, 9, 10, 8};
	int max=arr[0], counter=1;
	
    for (int i=1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
            counter = 1;
        } else if (arr[i] == max) {
            counter++;
        }
    }
    
    cout<<max<<endl<<counter<<endl;	
	
    return 0;
}