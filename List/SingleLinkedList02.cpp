#include <iostream>
#include <initializer_list>

template <typename T>
class SingleLinkedList
{
private:
    struct Node
    {
        T data;               /**< 节点内存放的数据. */
        Node *next = nullptr; /**< 指向下一个节点的指针. */
    };

    Node *head = nullptr;                         /**< 头指针. */
    void makeEmpty();                             /**< 释放链表内存. */
    void copyList(const SingleLinkedList &other); /**< 复制链表. */

public:
    /**
     * 默认构造函数.
     *
     */
    SingleLinkedList() {};

    /**
     * 默认析构函数.
     *
     */
    ~SingleLinkedList();

    SingleLinkedList(std::initializer_list<T> _l)
    {
        Node *tail = nullptr; // 考虑为什么需要这个？
        for (auto i = _l.begin(); i != _l.end(); ++i)
        {
            Node *newNode = new Node(); // 能否写成 Node* newNode = new Node{*i}; ???
            newNode->data = *i;         // 这里是否觉得不方便？
            if (head == nullptr)
            {
                head = newNode;
                tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode; // 是否应该将 tail 固定为成员变量？
            }
        }
    };

    SingleLinkedList(const SingleLinkedList &other);

    SingleLinkedList &operator=(const SingleLinkedList &other);

    /**
     * 列出表内全部元素.
     *
     */
    void printList() const;
};

template <typename T>
void SingleLinkedList<T>::printList() const
{
    Node *p = head;
    while (p != nullptr)
    {
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
    makeEmpty();
}

template <typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList &other)
{
    head = nullptr;
    copyList(other);
}

template <typename T>
SingleLinkedList<T> &SingleLinkedList<T>::operator=(const SingleLinkedList &other)
{
    if (this != &other)
    {
        copyList(other);
    }
    return *this;
}

template <typename T>
void SingleLinkedList<T>::makeEmpty()
{
    Node *p = head;
    while (p != nullptr)
    {
        Node *next = p->next; // 先保存下一个节点的地址
        delete p;
        p = next;
    }
    head = nullptr; // 避免悬空指针
}

template <typename T>
void SingleLinkedList<T>::copyList(const SingleLinkedList &other)
{
    makeEmpty(); // 先清空当前链表
    Node *p = other.head;
    while (p != nullptr)
    {
        Node *newNode = new Node();
        newNode->data = p->data;
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node *tail = head;
            while (tail->next != nullptr)
            {
                tail = tail->next;
            }
            tail->next = newNode;
        }
        p = p->next;
    }
}

int main()
{
    SingleLinkedList<int> lst = {1, 2, 3, 4, 5};
    lst.printList();

    SingleLinkedList<double> lst2 = {1.1, 2.2, 3.3, 4.4, 5.5};
    lst2.printList();


    SingleLinkedList<int> lst3 = lst; // 调用拷贝构造函数
    lst3.printList();

    SingleLinkedList<double> lst4;
    lst4 = lst2; // 调用赋值操作符
    lst4.printList();

    return 0;
}