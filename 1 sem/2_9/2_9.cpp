#include <iostream>

using namespace std;

int main() {

    int n, d;

    cin >> n;

    d = n / 2;

    //задняя грань
    for (int i = 0; i < d; i++) {
        cout << " ";
    }

    for (int i = 0; i < n; i++) {
        cout << "* ";
    }

    cout << endl;
    //Верхние диагонали

    for (int i = 0; i < d - 1; i++) {
        
        //Левая диагональ
        for (int j = 1; j < d - i; j++) {
            cout << " ";
        }

        cout << "* ";

        //Правая диагональ
        for (int j = 0; j < n - 2; j++) {
            cout << "  ";
        }

        cout << "*";

        //Заднее правое вертикальное ребро
        for (int j = 1; j <= i; j++) {
            cout << " ";
        }

        cout << "*" << endl;
    }

    
    //Передняя грань + кусок задней грани
    for (int i = 0; i < n; i++) {
        cout << "* ";
    }

    for (int i = 0; i < d - 2; i++) {
        cout << " ";
    }

    cout << "* " << endl;

    //боковые грани(прямые)

    for (int i = 0; i < n - d - 1; i++) {
        cout << "* ";

        for(int j = 0; j < n - 2; j++) {
            cout << "  ";
        }

        cout << "* ";

        for (int j = 0; j < d - 2; j++) {
            cout << " ";
        }

        cout << "*" << endl;
    }

    //Нижняя правая грань

    for (int i = 0; i <  d - 1; i++) {
        cout << "* ";

        //Вертикальные стороны

        for (int j = 0; j < n - 2; j++) {
            cout << "  ";
        }

        cout << "*";

        //Косая грань

        for (int j = 0; j < d - i - 2; j++) {
            cout << " ";
        }

        cout << "*" << endl;
    }

    //нижняя грань

    for (int i = 0; i < n; i++) {
        cout << "* ";
    }

    cout << endl;

    return 0;
}