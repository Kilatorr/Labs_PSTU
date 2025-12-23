#include <bits/stdc++.h>
using namespace std;

int main() {
int n;
cin >> n;
int a = sqrt(n);
for (int i = 0; i < a; i++)
{
    for (int j = 0; j < a; j++)
    {
        cout << "*";
    }
    cout << endl;
}
}