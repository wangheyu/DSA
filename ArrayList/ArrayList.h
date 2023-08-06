#include <iostream>
#include <cassert>
#include <cstdlib>

class ArrayList
{
private:
    // C++ 11 以后允许给类成员赋初指, 且发生在任何构造函数之前.
    char* data = nullptr;
    // 用以表示数组大小, 必须靠程序员可靠维护.
    int size = 0;
public:
    // 这个 const 表示该成员函数不会修改类的任何数据.
    void printList() const;
    void makeEmpty() const;
    const char* find(char val) const;
    char* find(char val);
    int findIdx(char val) const;
    // 动态函数就不可以加 const 限制.
    void insert(char val, int pos);
    void remove(char val);
    // 不允许修改返回的指针, 也不允许函数修改类成员数据. 
    const char* findKth(int pos) const;
    // 这是上一个函数的重载, 允许修改返回的指针, 也允许修改函数成员的数据.
    char* findKth(int pos);
    ArrayList() { data = nullptr; }
    ArrayList(int N);
    ~ArrayList() { if (data != nullptr) delete [] data; data = nullptr; }
};

