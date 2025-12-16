#include <iostream>
using namespace std;

int main()
{
    int N; int sum = 0; int prod = 1;
    cin >> N;

    for (int i = 1; i <= N; i++) {

        prod = 1;
        for (int j = 1; j <= 2*i; j++) {
            prod *= j;
        }

        sum += prod;
    }
    cout << sum << endl;
    return 0;
    
}

