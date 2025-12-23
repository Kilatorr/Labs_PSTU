#include <bits/stdc++.h>
using namespace std;

int main() {
int n, num;
string firstnum;
firstnum = "Все числа равны нулю";
cin >> n;
for (int i = 1; i <= n; i++)
{
cin >> num;
if (num != 0)
{
if (num > 0) { firstnum = "(+) Положительное"; break; }
else { firstnum = "(-) Отрицательное"; break; }
}
}
cout << firstnum << endl;
}