#ifndef __LIST_MARK__
#define __LIST_MARK__

#include <utility>

/**
 * @brief 课本上的 List 实现.
 *
 * @tparam Object List 中的元素类型.
 */
template <typename Object>
class List
{
private:
    /**
     * @brief 节点的定义. 因为定义的是私有类，所以不需要考虑命名冲突.
     * 外部不会访问到这个类. 因为 struct 默认是 public 的. 所以在
     * List 类内部，Node 类的成员变量和成员函数都是可以直接访问的.
     */
    struct Node
    {
        Object data; /**<! 节点内存放的数据. */
        Node *prev;  /**<! 指向前一个节点的指针. */
        Node *next;  /**<! 指向后一个节点的指针. */
        /**
         * @brief 列表型节点的构造函数. 注意这里的默认参数的使用.
         * 使我们同时拥有一个默认构造函数和一个带参数的构造函数.
         *
         * @param d 节点内存放的数据. 默认为空.
         * @param p 前一个节点的指针. 默认为空.
         * @param n 后一个节点的指针. 默认为空.
         */
        Node(const Object &d = Object{}, Node *p = nullptr,
             Node *n = nullptr)
            : data{d}, prev{p}, next{n} {}

        /**
         * @brief 移动构造函数. 唯一的区别是节点数据是一个右值引用. 因此以 std::move 的方式传递.
         *
         * @param d 节点内存放的数据. 只有这里是一个显式的右值引用，才会调用这个构造函数.
         * @param p 前一个节点的指针. 默认为空.
         * @param n 后一个节点的指针. 默认为空.
         */
        Node(Object &&d, Node *p = nullptr, Node *n = nullptr)
            : data{std::move(d)}, prev{p}, next{n} {}
    };

public:
    /**
     * @brief 一个静态的迭代器类. 用于创建一个可以随机访问 List 的迭代器.
     * 迭代器可以看作是一个被封装的指针.
     *
     */
    class const_iterator
    {
    public:
        /**
         * @brief 默认构造函数. 用于初始化迭代器.
         *
         */
        const_iterator() : current{nullptr}
        {
        }

        /**
         * @brief 返回当前节点的数据. 注意这里是只读的.
         *
         * @return const Object& 当前节点的数据.
         */
        const Object &operator*() const
        {
            return retrieve();
        }

        /**
         * @brief 迭代器的前置自增运算符. 用于将迭代器指向下一个节点.
         *
         * @return const_iterator& 下一个节点的迭代器.
         */
        const_iterator &operator++()
        {
            current = current->next;
            return *this;
        }

        /**
         * @brief 迭代器的后置自增运算符. 用于将迭代器指向下一个节点.
         *
         * @return const_iterator 下一个节点的迭代器.
         */
        const_iterator operator++(int)
        {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        /// 这里我们看到前自增和后自增的区别. 就是 std::cout << *iter++ << std::endl;
        /// 和 std::cout << *++iter << std::endl; 的区别. 前者是先输出当前值，再自增；后者是先自增，再输出.
        /// 这里也可以看到，为什么尽量用前自增，因为后自增需要一个临时变量来保存当前值，效率低.

        /**
         * @brief 判断两个迭代器是否相等.
         *
         * @param rhs 右操作数.
         * @return true 相等.
         * @return false 不相等.
         */
        bool operator==(const const_iterator &rhs) const
        {
            return current == rhs.current;
        }

        /**
         * @brief 判断两个迭代器是否不相等.
         *
         * @param rhs 右操作数.
         * @return true 不相等.
         * @return false 相等.
         */
        bool operator!=(const const_iterator &rhs) const
        {
            /// 这里直接调用 == 运算，多了一次调用，但能确保一致性.
            return !(*this == rhs);
        }

    protected:
        /// 在继承中，protected 修饰的成员变量和成员函数，可以被子类访问，但不能被外部访问.
        /// 因此它实际上应该看作是内部的和私有的.

        Node *current; /**<! 当前节点的指针. */

        /**
         * @brief 返回当前节点的数据.
         *
         * @return const Object& 当前节点的数据.
         */
        Object &retrieve() const
        {
            return current->data;
        }

        /**
         * @brief 一个带参数的构造函数. 用于快速调整迭代器的位置. 不宜对外开放.
         *
         * @param p 当前节点的新位置.
         */
        const_iterator(Node *p) : current{p}
        {
        }

        friend class List<Object>; /**<! 使 List 类可以访问到迭代器的私有成员和 protected 成员. */

        /// 注意到 const_iterator 并没有提供析构函数，因为它不需要也不应该释放内存.
    };

    /**
     * @brief 动态的迭代器，可以修改节点的数据. 它继承自 const_iterator. 体现 
     * iterator IS-A const_iterator 的关系.
     * 
     */
    class iterator : public const_iterator
    {
    public:
        /**
         * @brief 默认构造函数. 用于初始化迭代器. 为何这里不需要初始化 current 呢？
         * 因为它继承自 const_iterator，而 const_iterator 已经初始化了 current 为 nullptr.
         * 子类的构造函数会调用父类的构造函数，所以这里不需要再初始化 current 了.
         *
         */
        iterator()
        {
        }

        /**
         * @brief 返回当前节点的数据. 注意这里是可读可写的. 因为它直接调用了父类的 retrieve 函数. 
         * 而父类的 retrieve 函数返回的是一个引用，并没有限制不能修改. 而父类的 retrieve 函数后缀的 const 
         * 只限制了它不能修改父类的成员变量. 因此这里所有的规则都是可以遵守的.
         *
         * @return Object& 当前节点的数据.
         */
        Object &operator*()
        {
            return const_iterator::retrieve();
        }

        /**
         * @brief 这其实是一个重载. 一般我们规定重载必须通过参数列表来区分. 
         * 但通过 return 的 const 修饰符来区分是一个例外. 这使得我们可以给同一个函数分别提供动态和静态的版本，
         * 然后根据它们的实际使用情况来选择调用哪一个. 注意这里直接调用的父类的对应静态运算. 严格说我们也可以直接调用父类的运算符, 
         * 但这样会使代码更加清晰.
         * 
         * @return const Object& 
         */
        const Object &operator*() const
        {
            return const_iterator::operator*();
        }

        /**
         * @brief 迭代器的前置自增运算符. 用于将迭代器指向下一个节点.
         *
         * @return iterator& 下一个节点的迭代器.
         */
        iterator &operator++()
        {
            this->current = this->current->next;
            return *this;
        }

        /**
         * @brief 迭代器的后置自增运算符. 用于将迭代器指向下一个节点.
         *
         * @return iterator 下一个节点的迭代器.
         */
        iterator operator++(int)
        {
            iterator old = *this;
            ++(*this);
            return old;
        }

    protected:
        /**
         * @brief 一个带参数的构造函数. 用于快速调整迭代器的位置.
         *
         * @param p 当前节点的新位置.
         */
        iterator(Node *p) : const_iterator{p}
        {
        }

        friend class List<Object>;  /**<! 同样使 List 类可以访问到迭代器的私有成员和 protected 成员. */
    };

public:
    List() { init( ); }

    List(const List &rhs)
    {
        init( );
        for (auto & x : rhs)
            push_back(x);
    }
    ~List()
    {
        clear( );
        delete head;
        delete tail;
    }

    /// ？？？
    // List &operator=(const List &rhs)
    // {
    //     List copy = rhs;
    //     std::swap( *this, copy );
    //     return *this;
    // }

    /// 这里采用了 copy-and-swap 的技术. 通过传值的方式来调用拷贝构造函数，
    /// 然后通过 swap 来交换数据. 而 copy 这个临时对象会在函数结束时被销毁.
    /// 这个技术使得整个过程逻辑简单，并且效率更高. 但是一些实现的关键技术细节都是在 
    /// C++ 14 起引入的，因此只实现了 C++ 11 的版本的课本并没有做到.
    List &operator=(List copy)
    {
        std::swap( theSize, rhs.theSize );
        std::swap( head, rhs.head );
        std::swap( tail, rhs.tail );
// 这里最好显式交换每一个成员，或者专门为这个类实现一个 swap 函数.
//        std::swap( *this, copy );
        return *this;
    }

    List(List &&rhs) : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
    {
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }
    
    /// 这个功能已经被上面的实现所覆盖. 所以不再需要.
    /// 但奇怪的是这里的交换居然是深入到成员的.
    // List &operator=(List &&rhs)
    // {
    //     std::swap( theSize, rhs.theSize );
    //     std::swap( head, rhs.head );
    //     std::swap( tail, rhs.tail );
    //     return *this;
    // }

    iterator begin()
    {
        return {head->next};
    }

    const_iterator begin() const
    {
        return {head->next};
    }

    iterator end()
    {
        return {tail};
    }

    const_iterator end() const
    {
        return {tail};
    }

    int size() const
    {
        return theSize;
    }

    bool empty() const
    {
        return size() == 0;
    }

    void clear()
    {
        while (!empty())
            pop_front();
    }

    Object &front()
    {
        return *begin();
    }

    const Object &front() const
    {
        return *begin();
    }

    Object &back()
    {
        return *--end();
    }

    const Object &back() const
    {
        return *--end();
    }

    void push_front(const Object &x)
    {
        insert(begin(), x);
    }

    void push_front(Object &&x)
    {
        insert(begin(), std::move(x));
    }

    void push_back(const Object &x)
    {
        insert(end(), x);
    }

    void push_back(Object &&x)
    {
        insert(end(), std::move(x));
    }

    void pop_front()
    {
        erase(begin());
    }

    void pop_back()
    {
        erase(--end());
    }

    iterator insert(iterator itr, const Object &x)
    {
        Node *p = itr.current;
        theSize++;
        return { p->prev = p->prev->next = new Node{ x, p->prev, p } };
    }

    iterator insert(iterator itr, Object &&x)
    {
        Node *p = itr.current;
        theSize++;
        return { p->prev = p->prev->next = new Node{ std::move( x ), p->prev, p } };
    }

    iterator erase(iterator itr)
    {
        Node *p = itr.current;
        iterator retVal{ p->next };
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        theSize--;
        return retVal;
    }

    iterator erase(iterator from, iterator to)
    {
        for( iterator itr = from; itr != to; )
        itr = erase( itr );
        return to;
    }

private:
    int theSize;    /**<! 数据节点总数. */
    Node *head;     /**<! 头指针. */
    Node *tail;     /**<! 尾指针. */
    void init()
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
};

#else
// DO NOTHING.
#endif