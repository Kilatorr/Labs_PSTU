#include <iostream>
using namespace std;

int Norm(int k, int n, int start, int end) {
    while (k < 0) {k += n;}
    while (k >= n) {k -= n;}
    
    k += start;
    if (k > 100) {
        k -= 100;
    }
    
    return k;
}

void Print(int arr[100], int start, int end, int k) {
    if (start < end) {
        for (int i=k; i < end; i++) {
            cout<<arr[i]<<" ";
        }
        for (int i=start; i < k; i++) {
            cout<<arr[i]<<" ";
        }
    } else if (k < end) {
        for (int i=k; i < end; i++) {
            cout<<arr[i]<<" ";
        }
        for (int i=start; i < 100; i++) {
            cout<<arr[i]<<" ";
        }
        for (int i=0; i < k; i++) {
            cout<<arr[i]<<" ";
        }
    } else {
        for (int i=k; i < 100; i++) {
            cout<<arr[i]<<" ";
        }
        for (int i=0; i < end; i++) {
            cout<<arr[i]<<" ";
        }
        for (int i=start; i < k; i++) {
            cout<<arr[i]<<" ";
        }
    }
    cout<<endl;
}

int Del_left(int arr[100], int start, int end) {
    int j=start;
    for (int i=start; i < end; i++) {
        if (arr[i]%2 == 1) {
            arr[j++] = arr[i];
        }
    }
    
    return j;
}

int Del_right(int arr[100], int start, int end) {
    int j=end-1;
    for (int i=end-1; i >= start; i--) {
        if (arr[i]%2 == 1) {
            arr[j--] = arr[i];
        }
    }
    
    return j;
}

int main() {
	int N = 100;
	int arr[N];
	
	int n;
	cin>>n;
	int start=0, end=0;
	if (n > N) {
	    cout<<"Ошибка размера";
	} else {
	    // 1) Реализация
	    for (int i=0; i < n; i++) {
	        cin>>arr[i];
	    }
	    end = n;
	    
	    // 2) Распечатование
	    int k;
	    cin>>k;
	    k = Norm(k, n, start, end);
	    
	    Print(arr, start, end, k);
	    
	    // 3) Добавление в начало и конец
	    if (n+2 > N) {
	        cout<<"Ошибка размера";
	    } else {
	        int a, b;
	        cin>>a>>b;
	        
	        if (start == 0) {
	            start = N-1;
	            arr[start] = a;
	        } else {
	            arr[--start] = a;
	        }
	        
	        if (end == N) {
	            end = 1;
	            arr[end-1] = b;
	        } else {
	            arr[end++] = b;
	        }
	        
	        // 4) Удалить чётные элементы
	        if (start < end) {
	            end = Del_left(arr, start, end);
	        } else {
	            start = Del_right(arr, start, N)+1;
	            end = Del_left(arr, 0, end);
	        }
	        
	        // 5) Распечатование
	        cin>>k;
	        k = Norm(k, n, start, end);
	    
	        Print(arr, start, end, start);
	    }
	    
	}
    return 0;
}
