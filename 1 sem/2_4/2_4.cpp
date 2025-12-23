#include <bits/stdc++.h>
using namespace std;

int main() {
int n;
cin >> n;
int woid = n/2;
int zvezda = 1;
for (int i = 0; i < (n+1)/2; i++)
{
for (int j = 0; j < woid; j++)
{
cout << " ";
}
woid--;
for (int j = 0; j < zvezda; j++)
{
cout << "*";
}
zvezda += 2;
cout << endl;
}
}
