#include <iostream>
#include <initializer_list>

template <typename T>
class SingleLinkedList
{
private:
    struct Node
    {
        T data;
        Node *next = nullptr;
        Node () : data(T()){}
        Node (T val): data(val), next(nullptr) {}
    };    
    Node *head = nullptr;
    int size = 0;
    void copyFrom(const SingleLinkedList &other);
public:
    SingleLinkedList() = default;
    SingleLinkedList(std::initializer_list<T> lst)
    {
        size = lst.size();
        Node *tail = nullptr;
        for (auto val : lst)
        {
            // Node *newNode = new Node;
            // newNode->data = val;
            // newNode->next = nullptr;
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
        }
    }

    ~SingleLinkedList()
    {
        makeEmpty();
    }
    void makeEmpty();
    void printList() const;
    void push_back(T val);
    SingleLinkedList(const SingleLinkedList &other)
    {
        size = other.size;
        if (other.head == nullptr)
        {
            head = nullptr;
        }
        else
        {
            head = new Node(other.head->data);
//            head->data = other.head->data;
            Node *currentOther = other.head->next;
            Node *currentThis = head;
            while (currentOther != nullptr)
            {
                // Node *newNode = new Node;
                // newNode->data = currentOther->data;
                // newNode->next = nullptr;
                Node *newNode = new Node(currentOther->data);
                currentThis->next = newNode;
                currentThis = newNode;
                currentOther = currentOther->next;
            }
        }
    }
    SingleLinkedList& operator=(const SingleLinkedList &other);
};

template <typename T>
void SingleLinkedList<T>::copyFrom(const SingleLinkedList<T> &other)
{
    size = other.size;
    copyFrom(other);
}

template <typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(const SingleLinkedList<T> &other)
{
    if (this != &other) // 防止自赋值
    {
        makeEmpty(); // 释放原有内存
        size = other.size;
        copyFrom(other);
    }
    return *this;
}

template <typename T>
void SingleLinkedList<T>::push_back(T val)
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
    size++;
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
    Node *current = head;
    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

int main ()
{
    SingleLinkedList<int> list = {1, 2, 3, 4, 5};
    list.printList();
    SingleLinkedList<int> list2 = list; // 测试拷贝构造函数
    list2.printList();
    SingleLinkedList<double> dlist = {1.1, 2.2, 3.3};
    dlist.printList();
    return 0;
}


