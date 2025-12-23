#include <bits/stdc++.h>
#include <cmath>
using namespace std;

int main() {
float n, x, factorial, sum;
cin >> n >> x;
sum = 1 + x;
factorial = 1;
for (int i = 2; i <= n; i++)
{
factorial *= i;
sum += (pow(x, i) / factorial);
}
cout << sum << endl;
}
