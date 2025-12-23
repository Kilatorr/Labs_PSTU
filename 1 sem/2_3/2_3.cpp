#include <bits/stdc++.h>
using namespace std;

int main() {
int n, r = 0, dr = 0;
cin >> n;
for(int i = 1; i <= n; i++)
{
    dr = 1;
    for(int j = i; j <= 2*i; j++)
    {
        dr *= j;
    }
    r += dr;
}
cout << r << endl;
}
