#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <class T>
class Set
{
private:
    vector<T> data;

public:
    Set()
    {
    }

    void Add(T value)
    {
        data.push_back(value);
    }

    void Print()
    {
        for (int i = 0; i < (int)data.size(); i++)
            cout << data[i] << " ";
        cout << endl;
    }

    void MaxAddBegin()
    {
        if (data.empty()) return;
        typename vector<T>::iterator it = max_element(data.begin(), data.end());
        data.insert(data.begin(), *it);
    }

    void DelMin()
    {
        if (data.empty()) return;
        typename vector<T>::iterator it = min_element(data.begin(), data.end());
        data.erase(it);
    }

    void AddAverage()
    {
        if (data.empty()) return;

        T sum = T();
        for (int i = 0; i < (int)data.size(); i++)
            sum = sum + data[i];

        T average = sum / (int)data.size();
        for (int i = 0; i < (int)data.size(); i++)
            data[i] = data[i] + average;
    }
};
