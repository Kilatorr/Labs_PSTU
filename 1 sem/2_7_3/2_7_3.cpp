#include <bits/stdc++.h>
using namespace std;

int main() {
int n;
cin >> n;
for (int i = 0; i < n; i++)
{
cout << "*";
}
cout << endl;
for (int j = 0; j < n - 2; j++)
{
    cout << "*";
    for (int h = 0; h < n-2; h++)
    {
        cout << " ";
    }
    cout << "*" << endl;
}
for (int k = 0; k < n; k++)
{
    cout << "*";
}
}