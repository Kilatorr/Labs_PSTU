#include <bits/stdc++.h>
using namespace std;

int main() {
int n, nextnum, max;
cin >> n; //кол-во чисел
cin >> max; //первое число
for (int i = 2; i <= n; i++)
{
cin >> nextnum; //след числа
if (nextnum > max) { max = nextnum; }
}
cout << "max = " << max << endl;
}
