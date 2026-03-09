#include <iostream>
using namespace std;

int main() {
    int n = 3;
	int arr[n][n] = {{1, 2, 3}, {6, 5, 4}, {9, 8, 7}};
	int tmp, l=1;
    
  
    for(int i=0; i < n-1; i++) {            
        for(int j=0; j < n-i-1; j++) {     
            if (arr[l][j+1] < arr[l][j]) {
                
                for (int k=0; k < n; k++) {
                    tmp = arr[k][j+1]; 
                    arr[k][j+1] = arr[k][j]; 
                    arr[k][j] = tmp;
                }
                
            }
        }
    }
    
    for (int i=0; i < n; i++) {
        for (int j=0; j < n; j++) {
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
	
    return 0;
}