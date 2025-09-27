#include <iostream>
#include <initializer_list>
#include <vector>

#define NIL -1

typedef double t_ele;

class ArrayList
{
private:
    int size = 0;
    t_ele *data = nullptr;
public:
    ArrayList(){};
    ArrayList(std::initializer_list<t_ele> _l)   // 这里不能左值引用，为啥？
    {
        size = _l.size();
        data = new t_ele [size];
        int i = 0;
        for (t_ele e : _l)
        {
            data[i] = e;
            i++;
        }
    };

    ArrayList(const ArrayList &_l)
    {
        size = _l.size;
        data = new t_ele [size];
        for (int i = 0; i < size; i++)
            data[i] = _l.data[i];
    }

    ArrayList &operator=(const ArrayList &_l)
    {
        if (this == &_l)
            return *this;
        makeEmpty();
        size = _l.size;
        data = new t_ele [size];
        for (int i = 0; i < size; i++)
            data[i] = _l.data[i];
        return *this;
    }

    void printList() const
    {
        std::cout << "Values: " << std::endl;
        for (int i = 0; i < size; i++)
            std::cout << data[i] << "\t";
        std::cout << std::endl;    
    };
    void makeEmpty()
    {
        size = 0;
        if (data != nullptr)
            delete [] data;
        data = nullptr;             // avoid double free.
    }
    int find(const t_ele &_v) const; // 左值引用，避免复制。当 t_ele 是复杂数据结构时。
    void insert(const t_ele &_v, int _p);  // insert _v after pos _p. 同理。
    void push_ahead(const t_ele &_v);      // insert _v to the first pos.
    void remove(const t_ele &_v);          // remove the first ele equals to _v, do nothing if not found.
    ~ArrayList()
    {
        if (data != nullptr)        // avoid double free.
            makeEmpty();
    }
};

void ArrayList::push_ahead(const t_ele &_v)
{
    if (size == 0)
    {
        data = new t_ele;
        *data = _v;
        size ++;
        return;        
    }
    t_ele *new_data = new t_ele[size + 1];
    *new_data = _v;
    for (int i = 1; i < size + 1; i++)
        new_data[i] = data[i - 1];  
    delete [] data;         
    data = new_data;
    size ++; 
}

int ArrayList::find(const t_ele& _v) const
{
    for (int i = 0; i < size; i++)
        if (_v == data[i])
            return i;
    return NIL;
}

void ArrayList::remove(const t_ele &_v)
{
    int idx = find(_v);
    if (idx == NIL)
        return;
    t_ele *new_data = new t_ele [size - 1];
    for (int i = 0; i < idx; i++)
        new_data[i] = data[i];
    for (int i = idx + 1; i < size; i++)
        new_data[i - 1] = data[i];
    delete  data;         // ???
    data = new_data;
    size --;              // ???
}

int main()
{
    ArrayList A {1, 2, 3, 4, 5};
    A.printList();

    ArrayList C = A;
    ArrayList B(A);
    ArrayList D;

    D = A;
//    C = LB = A; // B.=（A）
    B.printList();
    C.printList();
    D.printList();
    return 0;
}

/// std::vector 
///    