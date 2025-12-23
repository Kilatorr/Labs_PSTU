#include <bits/stdc++.h>
using namespace std;

int main() {
float a, b, c, d, x1, x2;
cin >> a >> b >> c;
d = sqrt(pow(b, 2) - 4*a*c);
if (d > 0)
{
x1 = (-b+d)/(2*a);
x2 = (-b-d)/(2*a);
cout << "x1 = " << x1 << endl << "x2 = " << x2 << endl;
}
else if (d == 0)
{
x1 = (-b)/(2*a);
cout << "x1 = x2 = " << x1 << endl;
}
else { cout << "Корней нет" << endl; }
}
