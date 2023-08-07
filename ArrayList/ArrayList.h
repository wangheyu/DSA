#include <iostream>
#include <algorithm>

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
    void makeEmpty();
    // 从实用角度, find 返回一个指针会更有意义, 所以这里也提供了动静两套版本.
    const char* find(char val) const ;  
    char* find(char val) ;
    // 原本的 find 保留, 但改名为 findIdx.
    int findIdx(char val) const;
    // 动态函数就不可以加 const 限制.
    void insert(char val, int pos);
    void remove(char val);
    // 不允许修改返回的指针, 也不允许函数修改类成员数据. 
    const char* findKth(int pos) const;
    // 这是上一个函数的重载, 允许修改返回的指针, 也允许修改函数成员的数据.
    char* findKth(int pos);
    ArrayList() { }
    ArrayList(int N) { data = new char[N]; };
    ~ArrayList() { if (data != nullptr) delete [] data; }
    // 复制构造函数, 这里对参数做了引用.
    ArrayList(const ArrayList &rhs);
    // 赋值运算的重载.
    ArrayList &operator=(const ArrayList &rhs);
};
