#include "ArrayList.h"

ArrayList::ArrayList(int N)
{
    // 尽管理论上这里必然是 true, 但仍然应该通过程序确保.
    if (data == nullptr)
        data = new char[N];
    else
    {
        std::cerr << "Error: Allocating memory to a non-null pointer may result in memory leakage." 
        << std::endl;
        exit(-1);
    }
};

void ArrayList::printList() const
{
    if (size == 0)
    {
        std::cout << "The list is empty." << std::endl;
        return;
    }
    std::cout << "The list is: ";
    for (int i = 0; i < size; i++)
        std::cout << data[i] << " ";
    std::cout << std::endl;
    return;
}

void ArrayList::makeEmpty() const
{
    if (size == 0)
    {
        std::cerr << "Warning: The list is already empty." << std::endl;
        return;
    }
    else
    {
        if (data != nullptr)
            delete [] data;
        else
            std::cerr << "Error: A non-empty lsit has a null pointer." << std::endl;
            exit(-1);
    }
    return;
}

char* ArrayList::find(char val)
{
    char* p = data;
    for (int i = 0; i < size; i++, p++)
        if (*p == val)
            return p;
    return nullptr;
}

const char* ArrayList::find(char val) const
{
    return const_cast<ArrayList*>(this)->find(val);
}

int ArrayList::findIdx(char val) const
{
    const char* p = find(val);
    if (p == nullptr)
        return -1;
    else
        return p - data;
}

void ArrayList::insert(char val, int pos)
{
    if (pos < 0 || pos > size)
    {
        std::cerr << "Error: Invalid position." << std::endl;
        exit(-1);
    }
    if (size == 0)
    {
        if (data = nullptr)
            data = new char[1];
        else
        {
            std::cerr << "Warning: Allocating memory to a non-null pointer may result in memory leakage." 
            << std::endl;
            exit(-1);
        }
        data[0] = val;
        size++;
        return;
    }
    char* p = new char[size + 1];
    for (int i = 0; i < pos; i++)
        p[i] = data[i];
    p[pos] = val;
    for (int i = pos + 1; i < size + 1; i++)
        p[i] = data[i - 1];
    delete [] data;
    data = p;
    size++;
    return;
}

void ArrayList::remove(char val)
{
    int pos = findIdx(val);
    if (pos == -1)
    {
        std::cerr << "Error: The value is not in the list." << std::endl;
        exit(-1);
    }
    for (int i = pos + 1; i < size; i++)
        data[i - 1] = data[i];
    // 只改了 size, 没有释放内存.
    size--;
}

char* ArrayList::findKth(int pos)
{
    if (pos < 0 || pos >= size)
    {
        std::cerr << "Error: Invalid position." << std::endl;
        exit(-1);
    }
    return data + pos;
}

const char* ArrayList::findKth(int pos) const
{
    return const_cast<ArrayList*>(this)->findKth(pos);
}

