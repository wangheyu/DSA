#include "ArrayList02.h"
#include <iostream>
void ArrayList::init(int _maxSize)
{
    size = _maxSize;
    data = new double[size];
    for (int i = 0; i < size; i++)
        data[i] = 0.0;
}

void ArrayList::printList()
{
    for (int i = 0; i < size; i++)
        std::cout << data[i] << " ";
    std::cout << std::endl;
}

void ArrayList::insert(double _val, int _pos)
{
    if (_pos < 0 || _pos >= size)
    {
        std::cerr << "Error: position out of range." << std::endl;
        return;
    }
    for (int i = size - 1; i > _pos; i--)
        data[i] = data[i - 1];
    data[_pos] = _val;
}