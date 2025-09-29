#include <iostream>
#include <initializer_list>
#include <utility> // for std::move

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
        Node(T &&_val, Node *_next = nullptr) : data(std::move(_val)), next(_next) {}
    };
    Node *head = nullptr;
    int size = 0;
    void copyFrom(const SingleLinkedList &other);

public:
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
    void push_back(const T &val);  
    void push_front(const T &val);
    Node* find_prev(const T &val);
    bool insert(const T &target, const T &val);
    bool remove(const T &val);
    SingleLinkedList(SingleLinkedList<T>&& other) noexcept;
    SingleLinkedList<T>& operator=(SingleLinkedList<T>&& other) noexcept;

    class iterator {
        using node_ptr = Node*;
        node_ptr curr = nullptr;
        explicit iterator(node_ptr p) : curr(p) {}
        friend class SingleLinkedList; // 允许外部构造 begin/end
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        iterator() = default;

        // 解引用
        reference operator*() const { return curr->data; }
        pointer operator->() const { return std::addressof(curr->data); }

        // 前缀 ++
        iterator& operator++() {
            curr = curr ? curr->next : nullptr;
            return *this;
        }
        // 后缀 ++
        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        friend bool operator==(const iterator& a, const iterator& b) { return a.curr == b.curr; }
        friend bool operator!=(const iterator& a, const iterator& b) { return !(a == b); }
    };

    class const_iterator {
        using node_ptr = const Node*;
        node_ptr curr = nullptr;
        explicit const_iterator(node_ptr p) : curr(p) {}
        friend class SingleLinkedList;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        const_iterator() = default;
        // 从非 const 迭代器构造（允许隐式转换）
        const_iterator(const iterator& it) : curr(it.curr) {}

        reference operator*() const { return curr->data; }
        pointer operator->() const { return std::addressof(curr->data); }

        const_iterator& operator++() {
            curr = curr ? curr->next : nullptr;
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        friend bool operator==(const const_iterator& a, const const_iterator& b) { return a.curr == b.curr; }
        friend bool operator!=(const const_iterator& a, const const_iterator& b) { return !(a == b); }
    };

    // 迭代器访问
    iterator begin() noexcept { return iterator(head); }
    iterator end() noexcept { return iterator(nullptr); }
    const_iterator begin() const noexcept { return const_iterator(head); }
    const_iterator end() const noexcept { return const_iterator(nullptr); }
    const_iterator cbegin() const noexcept { return const_iterator(head); }
    const_iterator cend() const noexcept { return const_iterator(nullptr); }    
};

template <typename T>
SingleLinkedList<T>::SingleLinkedList(SingleLinkedList&& other) noexcept
  : head(other.head), size(other.size) {
    other.head = nullptr; other.size = 0;
}

template <typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(SingleLinkedList&& other) noexcept {
    if (this != &other) {
        makeEmpty();
        head = other.head; size = other.size;
        other.head = nullptr; other.size = 0;
    }
    return *this;
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

template <typename T>
void SingleLinkedList<T>::push_back(const T &val)
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

template <typename T>
void SingleLinkedList<T>::push_front(const T &val)
{
    Node *newNode = new Node(val);
    newNode->next = head;
    head = newNode;
    ++size;
}

template <typename T>
typename SingleLinkedList<T>::Node* SingleLinkedList<T>::find_prev(const T &val)
{
    Node *current = head;
    Node *prev = nullptr;
    while (current != nullptr)
    {
        if (current->data == val)
        {
            return prev;
        }
        prev = current;
        current = current->next;
    }
    return nullptr;
}

template <typename T>
bool SingleLinkedList<T>::insert(const T &target, const T &val)
{
    Node *prev = find_prev(target);
    if (prev == nullptr)
    {
        if (head == nullptr)
        {
            // 链表为空，无法插入
            return false;
        }
        else if (head->data == target)
        {
            // 目标节点是头节点
            push_front(val);
            return true;
        }
        else
        {
            // 目标节点不存在
            return false;
        
        }
    }
    // 创建新节点
    Node *newNode = new Node(val);
    newNode->next = prev->next;
    prev->next = newNode;
    size++;
    return true;
}

template <typename T>
bool SingleLinkedList<T>::remove(const T &val)
{
    Node *prev = find_prev(val);
    if (prev == nullptr)
    {
        if (head == nullptr)
        {
            // 链表为空，无法删除
            return false;
        }
        else if (head->data == val)
        {
            // 目标节点是头节点
            Node *toDelete = head;
            head = head->next;
            delete toDelete;
            size--;
            return true;
        }
        else
        {
            // 目标节点不存在
            return false;
        }
    }
    // 删除目标节点
    Node *toDelete = prev->next;
    if (toDelete == nullptr)
    {
        // 目标节点不存在 
        return false;
    }
    prev->next = toDelete->next;
    delete toDelete;
    size--;
    return true;
}

int main()
{
    SingleLinkedList<int> list = {1, 2, 3, 4, 5};
    list.printList();
    SingleLinkedList<int> list2 = list; // 测试拷贝构造函数
    list2.printList();
    SingleLinkedList<double> dlist = {1.1, 2.2, 3.3};
    dlist.printList();
    dlist.push_back(4.4);
    dlist.printList();
    dlist.push_front(0.0);
    dlist.printList();
    dlist.insert(2.2, 1.5);
    dlist.printList();
    dlist.remove(3.3);
    dlist.printList();
    dlist.remove(0.0);
    dlist.printList();
    dlist.remove(4.4);
    dlist.printList();

    SingleLinkedList<double> dlist2 = std::move(dlist); // 测试移动构造函数
    dlist2.printList();
    dlist.printList(); // dlist 应该为空

    SingleLinkedList<double>::iterator it = dlist2.begin();
    while (it != dlist2.end()) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;



    return 0;
}
