#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double a = 0.1, b = 1.0;
    int k = 10, n = 10;
    double eps = 0.0001;

    double h = (b - a) / k;
    double ln3 = log(3.0);

    cout << fixed << setprecision(10);

    for (int i = 0; i <= k; i++) {
        double x = a + i * h;
        double y = pow(3.0, x);   // точное значение функции

        // Сумма для заданного n
        double sn = 1.0;
        double an = 1.0;

        for (int j = 1; j <= n; j++) {
            an = an * x * ln3 / j;
            sn += an;
        }

        // Сумма для заданной точности eps
        double se = 1.0;
        double ae = 1.0;
        int j = 1;

        while (true) {
            ae = ae * x * ln3 / j;

            if (fabs(ae) < eps) {
                break;
            }

            se += ae;
            j++;
        }

        cout << "x = " << x << endl;
        cout << "y = " << y << endl;
        cout << "S(n) = " << sn << endl;
        cout << "S(eps) = " << se << endl;
        cout << "|y - S(n)| = " << fabs(y - sn) << endl;
        cout << "|y - S(eps)| = " << fabs(y - se) << endl;
        cout << endl;
    }

    return 0;
}
