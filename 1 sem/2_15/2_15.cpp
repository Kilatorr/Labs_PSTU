#include <bits/stdc++.h>
using namespace std;

int main() {
int n, s;
string v = "Данная цифра отсутствует в числе";
cin >> n >> s;
while (n > 0)
{ 
    if (s == n % 10)
    {
        v = "Данная цифра присутствует в числе";
        break;
    }
    n /= 10;
}
cout << v << endl;
}
