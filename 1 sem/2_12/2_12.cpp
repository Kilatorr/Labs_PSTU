#include <bits/stdc++.h>
using namespace std;

int main() {
int n, nextnum, max, min;
cin >> n; //кол-во чисел
cin >> max; //первое число
min = max;
for (int i = 2; i <= n; i++)
{
cin >> nextnum; //след числа
if (nextnum > max) { max = nextnum; }
else if (nextnum < min) { min = nextnum; }
}
cout << "sum = " << max + min << endl;
}
