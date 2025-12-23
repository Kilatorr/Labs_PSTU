#include <bits/stdc++.h>
using namespace std;

int main() {
int c, firstnum, r = 1;
bool flag = false;
cin >> firstnum;
while (r != 0)
{
    cin >> c;
    if (c == 0 or firstnum == 0) { break; }
    if (firstnum <= c) { flag = true; firstnum = c; }
    else { flag = false; break; }
}
if (flag) { cout << "Числа упорядочены по возрастанию" << endl; }
else { cout << "Числа не упорядочены" << endl; }
}
