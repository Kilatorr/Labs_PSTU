#include <iostream>
#include <cmath>

using namespace std;

int main() {
	int n, s;
	float a, max;
	cin >> n;

	max = sin(n);
	cout << max << " ";
	s = 1;

	for (int i = 1; i < n; i++) {
		a = sin(n + i / double(n));
		cout << a << " ";

		if (a > max) {
			max = a;
			s = 0;
		}
		if (abs(a - max) < 0.000001) {
			s++;
		}
	}
	cout << endl << s << " " << max;


	return 0;
}