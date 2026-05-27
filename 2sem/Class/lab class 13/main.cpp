#include "Money.h"
#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>
#include <windows.h>

using namespace std;

template <class T>
void PrintVector(vector<T> a)
{
    for (int i = 0; i < (int)a.size(); i++)
        cout << a[i] << " ";
    cout << endl;
}

template <class T>
T SumVector(vector<T> a)
{
    T sum = T();
    for (int i = 0; i < (int)a.size(); i++)
        sum = sum + a[i];
    return sum;
}

template <class T>
class AddAverageFunction
{
private:
    T average;

public:
    AddAverageFunction(T a)
    {
        average = a;
    }

    void operator()(T& value)
    {
        value = value + average;
    }
};

template <class T>
void MaxAddBegin(vector<T>& a)
{
    if (a.empty()) return;
    typename vector<T>::iterator it = max_element(a.begin(), a.end());
    a.insert(a.begin(), *it);
}

template <class T>
void DelMin(vector<T>& a)
{
    if (a.empty()) return;
    typename vector<T>::iterator it = min_element(a.begin(), a.end());
    a.erase(it);
}

template <class T>
void AddAverage(vector<T>& a)
{
    if (a.empty()) return;

    T average = SumVector(a) / (int)a.size();
    for_each(a.begin(), a.end(), AddAverageFunction<T>(average));
}

template <class T>
vector<T> StackToVector(stack<T> s)
{
    vector<T> a;
    while (!s.empty())
    {
        a.push_back(s.top());
        s.pop();
    }
    reverse(a.begin(), a.end());
    return a;
}

template <class T>
stack<T> VectorToStack(vector<T> a)
{
    stack<T> s;
    for (int i = 0; i < (int)a.size(); i++)
        s.push(a[i]);
    return s;
}

template <class T>
void PrintStack(stack<T> s)
{
    vector<T> a = StackToVector(s);
    PrintVector(a);
}

template <class T>
void MaxAddBegin(stack<T>& s)
{
    vector<T> a = StackToVector(s);
    MaxAddBegin(a);
    s = VectorToStack(a);
}

template <class T>
void DelMin(stack<T>& s)
{
    vector<T> a = StackToVector(s);
    DelMin(a);
    s = VectorToStack(a);
}

template <class T>
void AddAverage(stack<T>& s)
{
    vector<T> a = StackToVector(s);
    AddAverage(a);
    s = VectorToStack(a);
}

template <class T>
void PrintMultiset(multiset<T> a)
{
    typename multiset<T>::iterator it;
    for (it = a.begin(); it != a.end(); it++)
        cout << *it << " ";
    cout << endl;
}

template <class T>
void MaxAddBegin(multiset<T>& a)
{
    if (a.empty()) return;
    typename multiset<T>::iterator it = a.end();
    it--;
    a.insert(*it);
}

template <class T>
void DelMin(multiset<T>& a)
{
    if (a.empty()) return;
    a.erase(a.begin());
}

template <class T>
void AddAverage(multiset<T>& a)
{
    if (a.empty()) return;

    T sum = T();
    typename multiset<T>::iterator it;
    for (it = a.begin(); it != a.end(); it++)
        sum = sum + *it;

    T average = sum / (int)a.size();

    vector<T> temp;
    for (it = a.begin(); it != a.end(); it++)
        temp.push_back(*it + average);

    a.clear();
    for (int i = 0; i < (int)temp.size(); i++)
        a.insert(temp[i]);
}

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    cout << "Zadacha 1. Vector<Money>" << endl;
    vector<Money> a;
    a.push_back(Money(10, 50));
    a.push_back(Money(7, 25));
    a.push_back(Money(15, 10));
    a.push_back(Money(3, 40));
    cout << "Nachalnyi vector: ";
    PrintVector(a);
    MaxAddBegin(a);
    cout << "Posle max_element i dobavleniya max v nachalo: ";
    PrintVector(a);
    DelMin(a);
    cout << "Posle min_element i udaleniya min: ";
    PrintVector(a);
    AddAverage(a);
    cout << "Posle for_each i dobavleniya srednego: ";
    PrintVector(a);

    cout << endl << "Zadacha 2. Adapter stack<Money>" << endl;
    stack<Money> s;
    s.push(Money(5, 20));
    s.push(Money(11, 30));
    s.push(Money(4, 90));
    cout << "Nachalnyi stack: ";
    PrintStack(s);
    MaxAddBegin(s);
    cout << "Posle dobavleniya max v nachalo: ";
    PrintStack(s);
    DelMin(s);
    cout << "Posle udaleniya min: ";
    PrintStack(s);
    AddAverage(s);
    cout << "Posle dobavleniya srednego: ";
    PrintStack(s);

    cout << endl << "Zadacha 3. Associativnyi container multiset<Money>" << endl;
    multiset<Money> m;
    m.insert(Money(2, 15));
    m.insert(Money(8, 75));
    m.insert(Money(6, 40));
    cout << "Nachalnyi multiset: ";
    PrintMultiset(m);
    MaxAddBegin(m);
    cout << "Posle dobavleniya max: ";
    PrintMultiset(m);
    DelMin(m);
    cout << "Posle udaleniya min: ";
    PrintMultiset(m);
    AddAverage(m);
    cout << "Posle dobavleniya srednego: ";
    PrintMultiset(m);

    return 0;
}
