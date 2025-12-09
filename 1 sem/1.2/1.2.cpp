#include <iostream>
using namespace std;

int main (){
    float a , b;
    cin >> a >> b;
    if (b == 0)
    {
        cout << "не дели на 0" << endl;
    }
    else{
        cout << a/b << endl;
    }
return 0;
}
