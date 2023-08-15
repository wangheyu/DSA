#include "ArrayList.h"

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

void ArrayList::makeEmpty()
{
    if (size == 0)
    {
        if (data != nullptr)
        {
            std::cerr << "Error: An empty list has a non-null pointer." << std::endl;
            exit(-1);
        }
    }
    else
    {
        size = 0;
        if (data != nullptr)
        {
            delete [] data;
            data = nullptr;
        }
        else
        {
            std::cerr << "Error: A non-empty list has a null pointer." << std::endl;
            exit(-1);
        }
    }
    return;
}

const char* ArrayList::find(char val) const  
{  
    for (int i = 0; i < size; ++i) {  
        if (data[i] == val)  
        {  
            return &data[i];  
        }  
    }  
    return nullptr;  
}  
  
char* ArrayList::find(char val)   
{  
   return const_cast<char*>(static_cast<const ArrayList&>(*this).find(val));  
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
        if (data == nullptr)
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

const char* ArrayList::findKth(int pos) const
{
    if (pos < 0 || pos >= size)
    {
        std::cerr << "Error: Invalid position." << std::endl;
        exit(-1);
    }
    return data + pos;
}

char* ArrayList::findKth(int pos) 
{
    return const_cast<char*>(static_cast<const ArrayList&>(*this).findKth(pos));  
}

ArrayList::ArrayList(const ArrayList &rhs)
{
    size = rhs.size;
    if (size == 0)
    {
        data = nullptr;
        return;
    }
    data = new char[size];
    for (int i = 0; i < size; i++)
        data[i] = rhs.data[i];
    return;
}

ArrayList &ArrayList::operator=(const ArrayList &rhs)
{
    if (this != &rhs)
    {
        this->makeEmpty();
        size = rhs.size;
        data = new char[size];
        for (int i = 0; i < size; i++)
            data[i] = rhs.data[i];
    }
    return *this;
}

ArrayList::ArrayList(std::initializer_list<char> initList) {  
    size = initList.size();  
    data = new char[size];  
  
    int i = 0;  
    for (auto it = initList.begin(); it != initList.end(); it++, i++) {  
        data[i] = *it;  
    }  
}  
