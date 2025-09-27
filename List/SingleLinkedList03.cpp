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
    Node* find(const T &_val) const;             /**< 查找指定元素. */
    Node* findPrev(const T &_val) const;         /**< 查找指定元素的前驱节点. */

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
    void push_front(const T &_val); // 在当前节点之后插入新节点
    void push_back(const T &_val);  // 在链表头部插入新节点
    void pop_front();               // 删除当前节点之后的节点
    void pop_back();                // 删除链表头部的节点
    void insertAfter(const T &_posVal, const T &_val);
    void removeByValue(const T &_val); // 删除指定值的节点
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

template <typename T>
void SingleLinkedList<T>::push_front(const T &_val)
{
    Node* newNode = new Node();
    newNode->data = _val;
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }
}

template <typename T>
void SingleLinkedList<T>::push_back(const T &_val)
{
    Node* newNode = new Node();
    newNode->data = _val;
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node* tail = head;
        while (tail->next != nullptr)
        {
            tail = tail->next;
        }
        tail->next = newNode;
    }
}

template <typename T>
void SingleLinkedList<T>::pop_front()
{
    if (head == nullptr)
        return;
    Node* temp = head;
    head = head->next;
    delete temp;
}

template <typename T>
void SingleLinkedList<T>::pop_back()
{
    if (head == nullptr)
        return;
    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
        return;
    }
    Node* p = head;
    while (p->next->next != nullptr)
    {
        p = p->next;
    }
    Node* temp = p->next;
    p->next = nullptr;
    delete temp;
}

template <typename T>
typename SingleLinkedList<T>::Node* SingleLinkedList<T>::find(const T &_val) const
{
    Node* p = head;
    while (p != nullptr)
    {
        if (p->data == _val)
            return p;
        p = p->next;
    }
    return nullptr; // 未找到
}

template <typename T>
void SingleLinkedList<T>::insertAfter(const T &_posVal, const T &_val)
{
    Node* posNode = find(_posVal);
    if (posNode == nullptr)
    {
        std::cerr << "Error: position value not found." << std::endl;
        return;
    }
    Node* newNode = new Node();
    newNode->data = _val;
    newNode->next = posNode->next;
    posNode->next = newNode;
}

template <typename T>
typename SingleLinkedList<T>::Node* SingleLinkedList<T>::findPrev(const T &_val) const
{
    if (head == nullptr || head->data == _val)
        return nullptr; // 没有前驱节点
    Node* p = head;
    while (p->next != nullptr)
    {
        if (p->next->data == _val)
            return p;
        p = p->next;
    }
    return nullptr; // 未找到
}

template <typename T>
void SingleLinkedList<T>::removeByValue(const T &_val)
{
    Node* prevNode = findPrev(_val);
    if (prevNode == nullptr)
    {
        if (head != nullptr && head->data == _val)
        {
            pop_front();
        }
        else
        {
            std::cerr << "Error: value not found." << std::endl;
        }
        return;
    }
    Node* targetNode = prevNode->next;
    prevNode->next = targetNode->next;
    delete targetNode;
}

int main()
{
    SingleLinkedList<int> lst = {1, 2, 3, 4, 5};
    lst.printList();

    lst.push_front(0);
    lst.printList();

    lst.push_back(6);
    lst.printList();

    lst.pop_front();
    lst.printList();

    lst.pop_back();
    lst.printList();

    lst.insertAfter(3, 99);
    lst.printList();

    lst.removeByValue(99);
    lst.printList();

    return 0;
}