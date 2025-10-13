#include <iostream>
#include <initializer_list>
#include <list>


template <typename T>
class SingleLinkedList
{
private:
    struct Node
    {
        T data;
        Node *next = nullptr;
        Node() : data(T()) {}
        Node(const T &_val, Node *_next = nullptr) : data(_val), next(_next) {}
        Node(const Node &other) : data(other.data), next(other.next) {}
        Node(Node &&other) : data(other.data), next(other.next)
        {
            other.next = nullptr; // 避免悬挂指针
        }
    };
    Node *head = nullptr;
    int size = 0;
    void copyFrom(const SingleLinkedList &other);
    Node* find_prev(const T &target) const;    
    Node* find(const T &target) const;    
//    void insert(const T &target, Node* &pos);

public:
    class iterator
    {
    private:
        Node *current;
    public:
        iterator(Node *node) : current(node) {}
        iterator& operator++() // 前置++
        {
            if (current != nullptr)
                current = current->next;
            return *this;
        }   
        iterator operator++(int) // 后置++
        {
            iterator temp = *this;
            ++(*this);
            return temp;
        }
        T& operator*() const
        {   
            return current->data;
        }
        bool operator==(const iterator &other) const
        {
            return current == other.current;
        }
        bool operator!=(const iterator &other) const
        {
            return current != other.current;
        }
    };

    SingleLinkedList() = default;
    SingleLinkedList(std::initializer_list<T> lst)
    {
//        size = lst.size();
        Node *tail = nullptr;
        for (const auto &val : lst)
        {
            Node *newNode = new Node(val);
            if (head == nullptr)
            {
                head = newNode;
                tail = head;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
            ++size;
        }
    }
    
    ~SingleLinkedList()
    {
        makeEmpty();
    }
    void makeEmpty();
    void printList() const;
    SingleLinkedList(const SingleLinkedList &other)
    {
        copyFrom(other);
    }
    SingleLinkedList &operator=(const SingleLinkedList &other);

    void pushFront(const T &val)
    {
        head = new Node(val, head);
        ++size;
    }
    SingleLinkedList(SingleLinkedList &&other) noexcept
        : head(other.head), size(other.size)
    {
        other.head = nullptr;
        other.size = 0;
    }

    SingleLinkedList &operator=(SingleLinkedList &&other) noexcept
    {
        if (this != &other)
        {
            makeEmpty();
            head = other.head;
            size = other.size;
            other.head = nullptr;
            other.size = 0;
        }
        return *this;
    }

    void pushBack(const T &val)
    {
        Node *newNode = new Node(val);
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
        ++size;
    }

    void insertAfter(const T &target, const T &val)
    {
        Node *current = find(target);
        if (current != nullptr)
        {
            Node *newNode = new Node(val, current->next);
            current->next = newNode;
            ++size;
        }
    }

    void remove(const T &target)
    {
        Node *current = find_prev(target);
        if (current != nullptr && current->next != nullptr)
        {
            Node *toDelete = current->next;
            current->next = toDelete->next;
            delete toDelete;
            --size;
        }
        else if (head != nullptr && head->data == target)
        {
            Node *toDelete = head;
            head = head->next;
            delete toDelete;
            --size;
        }
    }
};

// template <typename T>
// void SingleLinkedList<T>::insert(const T &target, Node* &pos)
// // 要用递归
// {   // head = pos 
//     if (pos == nullptr)
//     {
//         pos = new Node(target);
//         ++size;
//         return;
//     }
//     insert(target, pos->next);
// }





template <typename T>
typename SingleLinkedList<T>::Node 
*SingleLinkedList<T>::find_prev(const T &target) const
{
    Node *current = head;
    while (current != nullptr && current->next != nullptr)
    {
        if (current->next->data == target)
            return current;
        current = current->next;
    }
    return nullptr;
}

template <typename T>
typename SingleLinkedList<T>::Node 
*SingleLinkedList<T>::find(const T &target) const
{
    Node *current = find_prev(target);
    if (current != nullptr)
        return current->next;
    else if (head != nullptr && head->data == target)
        return head;
    return nullptr;
}

template <typename T>
void SingleLinkedList<T>::copyFrom(const SingleLinkedList<T> &other)
{
    makeEmpty();
    if (other.head == nullptr)
        return;
    head = new Node(other.head->data);
    const Node *currentOther = other.head->next;
    Node *currentThis = head;
    while (currentOther != nullptr)
    {
        currentThis->next = new Node(currentOther->data);
        currentThis = currentThis->next;
        currentOther = currentOther->next;
    }
    size = other.size;
}

template <typename T>
SingleLinkedList<T> &SingleLinkedList<T>::operator=(const SingleLinkedList<T> &other)
{
    if (this != &other)
        copyFrom(other);
    return *this;
}

template <typename T>
void SingleLinkedList<T>::makeEmpty()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    size = 0;
}

template <typename T>
void SingleLinkedList<T>::printList() const
{
    const Node *current = head; // const 更语义化
    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

int main()
{    
    SingleLinkedList<int> list = {1, 2, 3, 4, 5};
    list.printList();
    SingleLinkedList<int> list2 = list; // 测试拷贝构造函数
    list2.printList();
    SingleLinkedList<double> dlist = {1.1, 2.2, 3.3};
    dlist.printList();
    return 0;
}
