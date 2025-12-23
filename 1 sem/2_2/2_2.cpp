#include <bits/stdc++.h>
using namespace std;

int main() {
int n; int res = 1;
cin >> n;
if (n <= 0)
{
    cout << "Ошибка" << endl;
}
else 
{
    for (int i = 1; i <= n; i++)
    {
        res *= i;
    }
    cout << res << endl;
}
}