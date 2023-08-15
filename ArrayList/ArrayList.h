// 一份教学型代码, 用于展示 C++ 11 水平的基本逻辑设计. 目标受众是初学者.
// 没有考虑异常处理 try/catch - throw 的问题. 
// 也不考虑连续动态操作下如何改进效率和多线程处理下的内存锁定.

#include <iostream>
#include <algorithm>
#include <cstdlib>

template <typename ELE_T>
class ArrayList
{
private:
    // C++ 11 以后允许给类成员赋初指, 且发生在任何构造函数之前.
    ELE_T* data = nullptr;
    // 用以表示数组大小, 必须靠程序员可靠维护.
    int size = 0;
    // 专门用于处理各种异常.
    enum ERR_CODE 
    {  
        SUCCESS = 0,  
        INVALID_POS = -1,  
        UNKNOW_POINTER = -2, 
        MISSING_POINTER = -3,
        OPETATING_EMPTY_LIST = -4,
        INVALID_SIZE = -5   
    };  
    void _goto_exception (ERR_CODE err_code) const;

public:
    // 这个 const 表示该成员函数不会修改类的任何数据.
    // 这个函数其实非常 C 风格, 但先遵重课本的展开方式.
    void printList() const;
    void makeEmpty();
    // 从实用角度, find 返回一个指针会更有意义, 所以这里也提供了动静两套版本.
    const ELE_T* find(const ELE_T &val) const ;  
    ELE_T* find(const ELE_T &val) ;
    // 原本的 find 保留, 但改名为 findIdx.
    int findIdx(const ELE_T &val) const;
    // 动态函数就不可以加 const 限制.
    void insert(const ELE_T &val, int pos);
    void remove(const ELE_T &val);
    // 不允许修改返回的指针, 也不允许函数修改类成员数据. 
    const ELE_T& findKth(int pos) const;
    // 这是上一个函数的重载, 允许修改返回的指针, 也允许修改函数成员的数据.
    ELE_T& findKth(int pos);
    ArrayList() { }
    // 有变化.
    ArrayList(int N, const ELE_T& val); 
    ~ArrayList() { if (data != nullptr) delete [] data; }
    // 复制构造函数, 这里对参数做了引用.
    ArrayList(const ArrayList &rhs);
    // 赋值运算的重载.
    ArrayList &operator=(const ArrayList &rhs);
    // 列表初始化.
    ArrayList(std::initializer_list<ELE_T> initList);
    // 移动赋值.
    ArrayList& operator=(ArrayList&& other) noexcept;
    // 移送构造; 
    ArrayList(ArrayList&& other) noexcept;
    // 允许初始化赋值运算.
    ArrayList &operator=(std::initializer_list<ELE_T> list);
};

template <typename ELE_T>
void ArrayList<ELE_T>::_goto_exception(ArrayList<ELE_T>::ERR_CODE error_code) const
{
    switch (error_code)
    {
    case ArrayList<ELE_T>::SUCCESS:
        // do nothing.
        break;
    case ArrayList<ELE_T>::INVALID_POS:
        std::cerr << "Error: Invalid position." << std::endl;
        exit(-1);
        break;
    case ArrayList<ELE_T>::UNKNOW_POINTER:
        std::cerr << "Error: An empty list has a non-null pointer." << std::endl;
        delete [] data;
        exit(-1);
        break;
    case ArrayList<ELE_T>::MISSING_POINTER:
        std::cerr << "Error: A non-empty list has a null pointer." 
                  << std::endl;
        exit(-1);
        break;
    case ArrayList<ELE_T>::OPETATING_EMPTY_LIST:
        std::cerr << "Warning: Try to find the k-th element in an empty list." << std::endl;
        // do noting.
        break;
    case ArrayList<ELE_T>::INVALID_SIZE:
        std::cerr << "The size of the list is invalid." << std::endl;
        exit(-1);
        /* code */
    
    default:
        std::cerr << "Error: Unknown error." << std::endl;
        exit(-1);
        break;
    }
}

template <typename ELE_T>
void ArrayList<ELE_T>::printList() const
{
    if (size == 0)
    {
        std::cout << "The list is empty." << std::endl;
        return;
    }
    for (int i = 0; i < size; i++)
        std::cout << data[i] << " ";
    std::cout << std::endl;
    // 作为void函数, 不需要 return 语句.
    // 这个可以作为个人风格的一种体现.
    return;
}

template <typename ELE_T>
void ArrayList<ELE_T>::makeEmpty()
{
    if (size == 0)
    {
        if (data != nullptr)
            _goto_exception(UNKNOW_POINTER);
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
            _goto_exception(MISSING_POINTER);
    }
    return;
}

template <typename ELE_T>
const ELE_T* ArrayList<ELE_T>::find(const ELE_T &val) const  
{  
    for (int i = 0; i < size; ++i) {  
        if (data[i] == val)  
        {  
            return &data[i];  
        }  
    }  
    return nullptr;  
}

template <typename ELE_T>
ELE_T* ArrayList<ELE_T>::find(const ELE_T &val) 
{  
    return const_cast<ELE_T*>(static_cast<const ArrayList<ELE_T>&>(*this).find(val));
}

template <typename ELE_T>
void ArrayList<ELE_T>::insert(const ELE_T &val, int pos)
{
    // 对于动态内存分配时可能的异常, 一定要认真排除, 这是万恶之源. 
    if (pos < 0 || pos > size)
        _goto_exception(INVALID_POS);
    if (size == 0)
    {
        if (data == nullptr)
            data = new ELE_T[1];
        else
            _goto_exception(UNKNOW_POINTER);
        data[0] = val;
        size++;
        return;
    }
    if (data == nullptr)
        _goto_exception(MISSING_POINTER);
    ELE_T* p = new ELE_T[size + 1];
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

template <typename ELE_T>
const ELE_T& ArrayList<ELE_T>::findKth(int pos) const
{
    if (size == 0)
    {
        if (data == nullptr)
            _goto_exception(OPETATING_EMPTY_LIST);   
        else
            _goto_exception(UNKNOW_POINTER);
    }
    if (pos < 0 || pos >= size)
        _goto_exception(INVALID_POS);
    return data[pos];
}

template <typename ELE_T>
ELE_T& ArrayList<ELE_T>::findKth(int pos)
{
    return const_cast<ELE_T&>(static_cast<const ArrayList<ELE_T>&>(*this).findKth(pos));
}

template <typename ELE_T>
int ArrayList<ELE_T>::findIdx(const ELE_T &val) const
{
    const ELE_T* p = find(val);
    if (p == nullptr)
        return -1;
    else
        return p - data;
}

template <typename ELE_T>
void ArrayList<ELE_T>::remove(const ELE_T &val)
{
    int pos = findIdx(val);
    // 没有找到并不认为是一个错误, 直接返回. 
    if (pos == -1)
        return;
    for (int i = pos + 1; i < size; i++)
        data[i - 1] = data[i];
    // 只改了 size, 没有释放内存. 这样如果出现连续的删除操作, 就不会频繁的申请释放内存.
    // 同样的思路也可用于 insert 函数. 但那样的话就需要另一个成员变量 capacity, 
    // 专门用于管理实际内存使用量.
    size--;
}

template <typename ELE_T>
ArrayList<ELE_T>::ArrayList(int N, const ELE_T& val)
{
    if (N > 0) {  
        data = new ELE_T[N];  
        size = N;
        std::fill_n(data, N, val);  
    } else 
        _goto_exception(INVALID_SIZE);
}

template <typename ELE_T>
ArrayList<ELE_T>::ArrayList(const ArrayList<ELE_T> &rhs)
{
    if (rhs.size == 0)
    {
        data = nullptr;
        size = 0;
        return;
    }
    if (rhs.data == nullptr)
        _goto_exception(MISSING_POINTER);
    data = new ELE_T[rhs.size];
    size = rhs.size;
    for (int i = 0; i < size; i++)
        data[i] = rhs.data[i];
}

template <typename ELE_T>
ArrayList<ELE_T> & ArrayList<ELE_T>::operator=(const ArrayList &rhs)
{
    if (this != &rhs)
    {
        this->makeEmpty();
        size = rhs.size;
        data = new ELE_T[size];
        for (int i = 0; i < size; i++)
            data[i] = rhs.data[i];
    }
    return *this;
}

template <typename ELE_T>
ArrayList<ELE_T> & ArrayList<ELE_T>::operator=(std::initializer_list<ELE_T> list)
{
    this->makeEmpty();
    size = list.size();
    data = new ELE_T[size];
    int i = 0;
    for (auto &ele : list)
        data[i++] = ele;
    return *this;
}

template <typename ELE_T>
ArrayList<ELE_T>& ArrayList<ELE_T>::operator=(ArrayList&& other) noexcept
{
    if (this != &other)
    {
        std::swap(data, other.data);  
        std::swap(size, other.size);     
    }
    return *this;
}

template <typename ELE_T>
ArrayList<ELE_T>::ArrayList(std::initializer_list<ELE_T> initList)
{
    size = initList.size();
    data = new ELE_T[size];
    int i = 0;
    for (auto &ele : initList)
        data[i++] = ele;
}

template <typename ELE_T>
ArrayList<ELE_T>::ArrayList(ArrayList&& other) noexcept
{
    std::swap(data, other.data);  
    std::swap(size, other.size);      
}