#include <iostream>
using namespace std;

int main() {
	int n, temp, max;
	cin >> n;

	cout << "first n ";
	cin >> max;
	for (int i = 1; i < n; i++) {
		cin >> temp;
		if (temp > max) { max = temp; }
	}
	cout << max << endl;
	return 0;
}