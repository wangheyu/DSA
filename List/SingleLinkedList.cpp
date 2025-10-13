#include <iostream>
#include <initializer_list>
#include <list>

/**
 * @brief 单向链表容器（教学实现）
 * @tparam T 元素类型
 *
 * 说明：
 * - 该容器使用简单的单向节点结构进行存储，仅维护头指针 head 和元素数量 size。
 * - pushBack 为 O(n)，pushFront 为 O(1)；insertAfter/remove 需要线性查找目标值，整体为 O(n)。
 * - 迭代器为简化版本，仅支持前向遍历，未完全满足标准前向迭代器定义。
 * - 节点 Node 的拷贝/移动构造为浅拷贝 next（存在风险），实际使用中不应复制/移动 Node 对象。
 */
template <typename T>
class SingleLinkedList
{
private:
    /**
     * @brief 链表节点
     *
     * 注意：
     * - Node 的拷贝/移动构造当前实现会浅拷贝 next 指针，可能造成潜在风险（请勿在容器外部复制/移动 Node）。
     * - 容器内部通过 new/delete 管理节点生命周期。
     */
    struct Node
    {
        T data;        ///< 存储的数据
        Node *next = nullptr; ///< 指向下一个节点的指针，末尾节点为 nullptr

        /**
         * @brief 默认构造，值初始化 data
         */
        Node() : data(T()) {}

        /**
         * @brief 使用给定值与后继指针构造
         * @param _val 数据值（拷贝）
         * @param _next 后继节点指针，默认为 nullptr
         */
        Node(const T &_val, Node *_next = nullptr) : data(_val), next(_next) {}

        /**
         * @brief 拷贝构造（浅拷贝 next）
         * @param other 另一个节点
         */
        Node(const Node &other) : data(other.data), next(other.next) {}

        /**
         * @brief 移动构造（浅移动 next，并将 other.next 置空）
         * @param other 另一个节点
         */
        Node(Node &&other) : data(other.data), next(other.next)
        {
            other.next = nullptr; // 避免悬挂指针
        }
    };

    Node *head = nullptr; ///< 链表头指针，空链表为 nullptr
    int size = 0;         ///< 当前元素个数（示例实现使用 int，生产建议用 std::size_t）

    /**
     * @brief 从另一个链表拷贝内容（先清空自身，再逐节点拷贝）
     * @param other 源链表
     *
     * 异常安全：
     * - 若 T 的拷贝构造抛异常，当前对象内容会被清空（弱异常保证）。
     */
    void copyFrom(const SingleLinkedList &other);

    /**
     * @brief 查找目标值节点的前驱节点
     * @param target 目标值
     * @return 若存在，返回其前驱节点指针；否则返回 nullptr。若 head 即为目标，则也返回 nullptr。
     */
    Node* find_prev(const T &target) const;

    /**
     * @brief 查找第一个等于目标值的节点
     * @param target 目标值
     * @return 若找到返回节点指针，否则返回 nullptr
     */
    Node* find(const T &target) const;

//    /**
//     * @brief 递归插入（示例：在尾部追加），不建议在长链表中使用（栈风险）
//     * @param target 要插入的值
//     * @param pos 从该指针开始向后查找尾部（传引用以便在空位置写入）
//     */
//    void insert(const T &target, Node* &pos);

public:
    /**
     * @brief 简化的前向迭代器（仅演示）
     *
     * 仅支持：
     * - 前置/后置自增
     * - 解引用获取数据引用
     * - 相等比较
     *
     * 注意：未提供 const_iterator 与 operator->，不完全等同标准前向迭代器。
     */
    class iterator
    {
    private:
        Node *current; ///< 当前所指节点

    public:
        /**
         * @brief 由节点指针构造迭代器
         * @param node 节点指针
         */
        explicit iterator(Node *node) : current(node) {}

        /**
         * @brief 前置++，前进到下一个节点
         * @return 自身引用
         */
        iterator& operator++()
        {
            if (current != nullptr)
                current = current->next;
            return *this;
        }

        /**
         * @brief 后置++，前进到下一个节点，返回旧值
         * @return 旧的迭代器副本
         */
        iterator operator++(int)
        {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        /**
         * @brief 解引用获取当前数据
         * @return 当前节点数据的引用
         * @note 若指向 end（nullptr），解引用为未定义行为
         */
        T& operator*() const
        {
            return current->data;
        }

        /**
         * @brief 相等比较
         */
        bool operator==(const iterator &other) const
        {
            return current == other.current;
        }

        /**
         * @brief 不等比较
         */
        bool operator!=(const iterator &other) const
        {
            return current != other.current;
        }
    };

    /**
     * @brief 返回指向首元素的迭代器
     * @return 若链表为空，返回等于 end() 的迭代器
     */
    iterator begin() { return iterator(head); }

    /**
     * @brief 返回尾后迭代器（空迭代器）
     */
    iterator end() { return iterator(nullptr); }

    /**
     * @brief 默认构造，创建空链表
     */
    SingleLinkedList() = default;

    /**
     * @brief 使用初始化列表构造链表（按顺序尾插）
     * @param lst 初始化列表
     * @note 该实现局部维护 tail 指针以 O(n) 构建整个链表
     */
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

    /**
     * @brief 析构函数，释放所有节点
     */
    ~SingleLinkedList()
    {
        makeEmpty();
    }

    /**
     * @brief 清空链表，删除所有节点
     */
    void makeEmpty();

    /**
     * @brief 打印链表所有元素（以空格分隔，末尾换行）
     * @note 仅用于演示/调试，实际库设计通常不内置 I/O。
     */
    void printList() const;

    /**
     * @brief 拷贝构造函数，深拷贝 other 的所有元素
     * @param other 源链表
     */
    SingleLinkedList(const SingleLinkedList &other)
    {
        copyFrom(other);
    }

    /**
     * @brief 拷贝赋值，先清空当前，再深拷贝 other
     * @param other 源链表
     * @return 自身引用
     *
     * @note 异常安全为“弱保证”：若拷贝过程中抛异常，当前对象可能已被部分清空。
     */
    SingleLinkedList &operator=(const SingleLinkedList &other);

    /**
     * @brief 头部插入（前插）
     * @param val 要插入的值
     * @complexity O(1)
     */
    void pushFront(const T &val)
    {
        head = new Node(val, head);
        ++size;
    }

    /**
     * @brief 移动构造，将 other 的所有权转移到当前对象
     * @param other 源对象（被移动后置空）
     */
    SingleLinkedList(SingleLinkedList &&other) noexcept
        : head(other.head), size(other.size)
    {
        other.head = nullptr;
        other.size = 0;
    }

    /**
     * @brief 移动赋值，释放当前内容并接管 other 的资源
     * @param other 源对象（被移动后置空）
     * @return 自身引用
     */
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

    /**
     * @brief 尾部插入（后插）
     * @param val 要插入的值
     * @complexity O(n)（无尾指针）
     */
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

    /**
     * @brief 在第一个等于 target 的节点之后插入一个新值
     * @param target 目标值
     * @param val 要插入的值
     * @note 若未找到 target，本函数不进行任何操作
     * @complexity O(n)（需要线性查找）
     */
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

    /**
     * @brief 删除第一个等于 target 的节点
     * @param target 目标值
     * @note 若不存在目标值则不做任何操作
     * @complexity O(n)
     */
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

/**
 * @brief 查找目标值前驱节点的实现
 * @tparam T 元素类型
 * @param target 目标值
 * @return 若存在，返回其前驱节点指针；否则返回 nullptr
 */
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

/**
 * @brief 查找第一个等于目标值的节点实现
 * @tparam T 元素类型
 * @param target 目标值
 * @return 若找到返回节点指针，否则返回 nullptr
 */
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

/**
 * @brief 深拷贝 other 到当前链表（先清空自身）
 * @tparam T 元素类型
 * @param other 源链表
 * @note 异常安全为弱保证：拷贝过程中抛异常将导致当前对象被清空
 */
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

/**
 * @brief 拷贝赋值（清空自身再拷贝）
 * @tparam T 元素类型
 * @param other 源链表
 * @return 自身引用
 */
template <typename T>
SingleLinkedList<T> &SingleLinkedList<T>::operator=(const SingleLinkedList<T> &other)
{
    if (this != &other)
        copyFrom(other);
    return *this;
}

/**
 * @brief 清空链表的实现
 * @tparam T 元素类型
 */
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

/**
 * @brief 打印链表所有元素的实现
 * @tparam T 元素类型
 */
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

/**
 * @brief 测试 SingleLinkedList 各功能
 */
int main()
{
    std::cout << "==== 1) 空构造与打印 ====" << std::endl;
    SingleLinkedList<int> a;                 // 空表
    a.printList();                           // 预期：空行

    std::cout << "\n==== 2) 初始化列表构造 ====" << std::endl;
    SingleLinkedList<int> b = {1,2,3,4,5};
    b.printList();                           // 预期：1 2 3 4 5

    std::cout << "\n==== 3) pushFront / pushBack ====" << std::endl;
    a.pushFront(10); a.pushFront(20);        // a: 20 10
    a.printList();                           // 预期：20 10
    a.pushBack(30); a.pushBack(40);          // a: 20 10 30 40
    a.printList();                           // 预期：20 10 30 40

    std::cout << "\n==== 4) insertAfter ====" << std::endl;
    b.insertAfter(1, 11);                    // b: 1 11 2 3 4 5
    b.insertAfter(5, 55);                    // b: 1 11 2 3 4 5 55
    b.printList();                           // 预期：1 11 2 3 4 5 55
    b.insertAfter(999, 42);                  // 不存在：不变
    b.printList();                           // 预期：1 11 2 3 4 5 55

    std::cout << "\n==== 5) remove ====" << std::endl;
    b.remove(11);                            // b: 1 2 3 4 5 55
    b.printList();                           // 预期：1 2 3 4 5 55
    b.remove(1);                             // b: 2 3 4 5 55
    b.printList();                           // 预期：2 3 4 5 55
    b.remove(55);                            // b: 2 3 4 5
    b.printList();                           // 预期：2 3 4 5
    b.remove(999);                           // 不存在：不变
    b.printList();                           // 预期：2 3 4 5

    std::cout << "\n==== 6) 拷贝构造与拷贝赋值 ====" << std::endl;
    SingleLinkedList<int> c = b;             // 拷贝构造
    c.printList();                           // 预期：2 3 4 5
    SingleLinkedList<int> d;
    d = c;                                   // 拷贝赋值
    d.printList();                           // 预期：2 3 4 5
    c.pushFront(99);
    std::cout << "c after pushFront(99): "; c.printList(); // 预期：99 2 3 4 5
    std::cout << "d should be unchanged: "; d.printList(); // 预期：2 3 4 5

    std::cout << "\n==== 7) 移动构造与移动赋值 ====" << std::endl;
    SingleLinkedList<int> e = std::move(c);  // 移动构造
    std::cout << "e (moved-from c): "; e.printList();      // 预期：99 2 3 4 5
    std::cout << "c (moved-to empty): "; c.printList();    // 预期：空
    SingleLinkedList<int> f;
    f.pushBack(7); f.pushBack(8);
    std::cout << "f before move=: "; f.printList();        // 预期：7 8
    f = std::move(e);                       // 移动赋值
    std::cout << "f after move=: "; f.printList();         // 预期：99 2 3 4 5
    std::cout << "e after move=: "; e.printList();         // 预期：空

    std::cout << "\n==== 8) 多次插入/删除组合 ====" << std::endl;
    f.insertAfter(99, 100);                 // 99 100 2 3 4 5
    f.insertAfter(5, 6);                    // 99 100 2 3 4 5 6
    f.printList();                          // 预期：99 100 2 3 4 5 6
    f.remove(100);                          // 删中间
    f.printList();                          // 预期：99 2 3 4 5 6
    f.remove(99);                           // 删头
    f.printList();                          // 预期：2 3 4 5 6
    f.remove(6);                            // 删尾
    f.printList();                          // 预期：2 3 4 5

    std::cout << "\n==== 9) 边界条件 ====" << std::endl;
    {
        SingleLinkedList<int> g;
        g.remove(1);                          // 空表删除
        g.insertAfter(1, 2);                  // 空表插入 after
        g.printList();                        // 预期：空
        g.pushFront(1); g.remove(1);          // 删除唯一节点
        g.printList();                        // 预期：空
        g.pushBack(5); g.insertAfter(5, 6);   // 在尾后插
        g.printList();                        // 预期：5 6
        g.remove(6); g.remove(5);             // 依次删除，最终空
        g.printList();                        // 预期：空
        g.insertAfter(42, 99);                // 不存在，保持空
        g.remove(99);                         // 不存在
        g.printList();                        // 预期：空
    }

    std::cout << "\n==== 10) 不同类型模板实例化 ====" << std::endl;
    {
        SingleLinkedList<std::string> s = {"a","b","c"};
        s.printList();                        // 预期：a b c
        s.insertAfter(std::string("b"), "bb");
        s.printList();                        // 预期：a b bb c
        s.remove("a");
        s.printList();                        // 预期：b bb c
        s.remove("z");                        // 不存在
        s.printList();                        // 预期：b bb c
    }

    std::cout << "\n==== 11) 迭代器遍历与操作 ====" << std::endl;
    {
        // 11.1 空容器的迭代器
        SingleLinkedList<int> x;
        auto itx_begin = x.begin();
        auto itx_end = x.end();
        std::cout << "empty begin==end? " << (itx_begin == itx_end ? "true" : "false") << std::endl; // 预期 true

        // 11.2 单元素遍历
        x.pushBack(42);
        std::cout << "single element traversal: ";
        for (auto it = x.begin(); it != x.end(); ++it) {
            std::cout << *it << " ";          // 预期：42
        }
        std::cout << std::endl;

        // 11.3 多元素遍历（前置++）
        SingleLinkedList<int> y = {1,2,3,4};
        std::cout << "y by pre-increment: ";
        for (auto it = y.begin(); it != y.end(); ++it) {
            std::cout << *it << " ";          // 预期：1 2 3 4
        }
        std::cout << std::endl;

        // 11.4 多元素遍历（后置++）
        std::cout << "y by post-increment: ";
        for (auto it = y.begin(); it != y.end(); it++) {
            std::cout << *it << " ";          // 预期：1 2 3 4
        }
        std::cout << std::endl;

        // 11.5 解引用 + 手动步进混合
        auto it = y.begin();
        if (it != y.end()) { std::cout << "front=" << *it << " "; } // 1
        ++it; // 指向 2
        if (it != y.end()) { std::cout << "second=" << *it << " "; } // 2
        it++; // 指向 3
        if (it != y.end()) { std::cout << "third=" << *it << " "; } // 3
        std::cout << std::endl;

        // 11.6 迭代器相等/不等比较
        auto it1 = y.begin();
        auto it2 = y.begin();
        auto it3 = y.end();
        std::cout << "it1==it2? " << (it1 == it2 ? "true" : "false") << " "; // true
        std::cout << "it1!=it3? " << (it1 != it3 ? "true" : "false") << std::endl; // true

        // 11.7 修改容器后重新遍历（原迭代器可能失效，重新获取）
        y.insertAfter(4, 5); // y: 1 2 3 4 5
        std::cout << "y after insertAfter(4,5): ";
        for (auto itv = y.begin(); itv != y.end(); ++itv) {
            std::cout << *itv << " ";         // 预期：1 2 3 4 5
        }
        std::cout << std::endl;

        y.remove(1); // 删头 -> 2 3 4 5
        std::cout << "y after remove(1): ";
        for (auto itv = y.begin(); itv != y.end(); ++itv) {
            std::cout << *itv << " ";         // 预期：2 3 4 5
        }
        std::cout << std::endl;

        y.remove(5); // 删尾 -> 2 3 4
        std::cout << "y after remove(5): ";
        for (auto itv = y.begin(); itv != y.end(); ++itv) {
            std::cout << *itv << " ";         // 预期：2 3 4
        }
        std::cout << std::endl;
    }

    std::cout << "\n==== 所有测试结束 ====" << std::endl;
    return 0;
}
