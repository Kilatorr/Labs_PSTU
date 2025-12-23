#include <iostream>
#include <cmath>

using namespace std;

int main() {
	int n, max_i;
	double a_i, max;
	max_i = 0;
	cin >> n;

	max = sin(n);
	for (int i = 1; i < n; i++) {
		a_i = sin(n + i / double(n));
		if (a_i > max) { max = a_i; max_i = i; }
	}
	
	cout << max << " " << max_i;
	return 0;
}