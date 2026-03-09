#include <iostream>
using namespace std;

int nod(int n, int m) {
	if (n == m) {
		return n;
	}
	else if (n > m) {
		return nod(n - m, m);
	}
	else {
		return nod(n, m - n);
	}
}

int main() {
	int n, m;
	cin >> n;
	cin >> m;
	cout << nod(n, m) << endl;
}
