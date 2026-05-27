#pragma once
#include <iostream>
#include <map>

using namespace std;

template <class T>
class Container
{
private:
    multimap<int, T> data;

public:
    Container()
    {
    }

    void Add(int key, T value)
    {
        data.insert(make_pair(key, value));
    }

    void Print()
    {
        typename multimap<int, T>::iterator it;
        for (it = data.begin(); it != data.end(); it++)
            cout << it->first << " : " << it->second << endl;
    }

    int Size()
    {
        return (int)data.size();
    }

    void MaxAddBegin()
    {
        if (data.empty()) return;

        typename multimap<int, T>::iterator it = data.begin();
        T maximum = it->second;
        for (it = data.begin(); it != data.end(); it++)
            if (it->second > maximum) maximum = it->second;

        multimap<int, T> temp;
        temp.insert(make_pair(0, maximum));
        for (it = data.begin(); it != data.end(); it++)
            temp.insert(make_pair(it->first + 1, it->second));
        data = temp;
    }

    void DelMin()
    {
        if (data.empty()) return;

        typename multimap<int, T>::iterator it = data.begin();
        typename multimap<int, T>::iterator min_it = it;
        T minimum = it->second;
        for (it = data.begin(); it != data.end(); it++)
        {
            if (it->second < minimum)
            {
                minimum = it->second;
                min_it = it;
            }
        }
        data.erase(min_it);
    }

    void AddAverage()
    {
        if (data.empty()) return;

        typename multimap<int, T>::iterator it;
        T sum = T();
        for (it = data.begin(); it != data.end(); it++)
            sum = sum + it->second;

        T average = sum / (int)data.size();
        for (it = data.begin(); it != data.end(); it++)
            it->second = it->second + average;
    }
};
