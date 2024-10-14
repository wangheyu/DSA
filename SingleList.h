/**
 * @file SingleList.h
 * @author Crazyfish (wang_heyu@msn.com)
 * @brief 演示 C++ 基本设计和单链表的实现. 教学用途，严禁用于任何实际工作. 
 *        否则会有意想不到的惊喜.
 * @version 0.1
 * @date 2024-10-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CRAZYFISH_SINGLELINKED_LIST__
#define __CRAZYFISH_SINGLELINKED_LIST__

#include <iostream>
#include <limits>
#include <initializer_list>
#include <algorithm>

/**
 * @brief 用于教学演示的单链表实现.
 * 
 * @tparam T 节点存放的数据类型.
 */
template <typename T>
class SingleLinkedList
{
private:
    /**
     * @brief 链表的节点。暂时就是当 struct 用。
     * 
     */
    class Node
    {
    private:
        T data;			        /**< 节点内存放的数据. */
        Node* next = nullptr;	/**< 指向下一个节点的指针. */
    public:
        /** 
         * 带数据初始化的构造函数.
         * 
         * @param _val 初始化的数据.
         */
         Node(const T& _val) : data(_val) {}
// 不如用初始化列表        
//         Node(const T& _val) {data = _val;};

         friend class SingleLinkedList<T>;
    };

    Node* head = nullptr;	        /**< 头指针. */
    Node* currentPos = nullptr;	    /**< 当前位置的指针. 除非是空链表, 否则该指针不能空. */
    int size = 0;		            /**< 节点总数. */

    /**
     * @brief 清除链表内的所有节点.
     * 
     */
    void _makeEmpty();

    /**
     * @brief 将 @p _l 的内容拷贝到当前链表.
     * 
     * @param _l 拷贝源.
     */
    void _copy(const SingleLinkedList<T>& _l);

public:
    /** 
     * 默认构造函数.
     * 
     */
    SingleLinkedList(){};

    /** 
     * 默认析构函数.
     * 
     */
    ~SingleLinkedList();

    /** 
     * 带列表初始化的构造函数.
     * 
     * @param _l 初始化列表.
     */
     SingleLinkedList(std::initializer_list<T> _l);

    /** 
     * 列出表内全部元素.
     * 
     */
     void printList() const;

    /** 
     * 删除表内全部元素, 使之成为空表.
     * 
     */
     void makeEmpty();

    /** 
     * 查找指定元素.
     * 
     * @param _val 被查找的元素.  
     * 
     * @return 将当前位置移动到第一个找到的元素, 如果没有找到, 
     * 则当前位置不动.
     */
     void find(const T& _val)
     {
         Node* p = head;
         while (p != nullptr)
         {
             if (p->data == _val)
             {
                 currentPos = p;
                 return;
             }
             p = p->next;
         }
     }

    /** 
     * 判定链表是否为空.
     * 
     * 
     * @return 空链表返回 true, 非空返回 false.
     */
    bool isEmpty() const
    {
        return head == nullptr;
    };

    /**
     * @brief 获得链表的长度.
     * 
     * @return int 链表长度.
     */
    int getSize() const {return size;};

    /**
     * @brief 获得当前位置的数据.
     * 
     * @return const T& 当前节点的数据.
     */
    const T& getCurrentVal() const {return currentPos->data;};

    /**
     * @brief 设置当前位置的数据.
     * 
     * @param _val 用于设置的数据.
     */
    void setCurrentVal(const T& _val) {currentPos->data = _val;};
    
    /**
     * @brief 拷贝构造函数.
     * 
     * @param _l 拷贝源.
     */
    SingleLinkedList(const SingleLinkedList<T>& _l);

    /**
     * @brief 拷贝赋值函数.
     * 
     * @param _l 拷贝源.
     * @return SingleLinkedList<T>& 复制后的链表.
     */
    SingleLinkedList<T>& operator=(SingleLinkedList<T> _l);

// 一个传统的拷贝赋值函数
//    SingleLinkedList<T>& operator=(const SingleLinkedList<T>& _l);

    // 移动构造函数，但不打算实现.
    // SingleLinkedList(SingleLinkedList<T>&& _l) : head(_l.head), currentPos(_l.currentPos), size(_l.size)
    // {
    //     _l.head = nullptr;
    //     _l.currentPos = nullptr;
    //     _l.size = 0;
    // }

    /**
     * @brief 在当前位置之后插入一个值.
     * 
     * @param _val 插入的值.
     */
    void insert (const T& _val);

    /**
     * @brief 删除当前位置的下一个节点.
     * 
     */
    void remove ();
};

template <typename T>
void SingleLinkedList<T>::remove()
{
    if (currentPos == nullptr)
    {
        std::cerr << "Current position is null, remove failed." << std::endl;
        return;
    }
    Node* p = currentPos->next;
    if (p == nullptr)
    {
        std::cerr << "No next node, remove failed." << std::endl;
        return;
    }
    currentPos->next = p->next;
    delete p;
    --size;
}

template<typename T>
void SingleLinkedList<T>::insert(const T& _val)
{
    Node* newNode = new Node(_val);
    if (head == nullptr)
    {
        head = newNode;
        currentPos = head;
    }
    else if (currentPos == nullptr)
    {
        std::cerr << "Current position is null, insert failed." << std::endl;
    }
    else
    {
        newNode->next = currentPos->next;
        currentPos->next = newNode;
    }
    ++size;
}

template <typename T>
SingleLinkedList<T>::SingleLinkedList(std::initializer_list<T> _l)
{
    for (auto i = _l.begin(); i != _l.end(); ++i)
    {
        Node* newNode = new Node(*i);
        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
    }
    if (head != nullptr)
        currentPos = head;

}

template <typename T>
void SingleLinkedList<T>::printList() const
{
    Node* p = head;
    while (p != nullptr)
    {
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

template <typename T>
void SingleLinkedList<T>::_makeEmpty()
{
    Node* p = head;
    while (p != nullptr)
    {
        Node* t = p;
        p = p->next;
        delete t;
    }
}

template <typename T>
void SingleLinkedList<T>::makeEmpty()
{
    _makeEmpty();
    head = nullptr;
    currentPos = nullptr;
    size = 0;
}

template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
    _makeEmpty();
}

template <typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T>& _l)
{
    _copy(_l);
}

// 一个传统的拷贝赋值函数的实现，主要问题是比较复杂，内部出错环节多。
// template <typename T>
// SingleLinkedList<T>& SingleLinkedList<T>::operator=(const SingleLinkedList<T>& _l)
// {
//     if (this == &_l)
//         return *this;
//     makeEmpty();
//     _copy(_l);
//     return *this;
// }

/// 利用 Copy and Swap 的技巧，实现拷贝赋值函数。逻辑简单，不容易出错。
template <typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(SingleLinkedList<T> _l)
{
    std::swap(head, _l.head);
    std::swap(currentPos, _l.currentPos);
    std::swap(size, _l.size);
    return *this;
}

template <typename T>
void SingleLinkedList<T>::_copy(const SingleLinkedList<T>& _l)
{
    Node* p = _l.head;
    while (p != nullptr)
    {
        Node* newNode = new Node(p->data);
        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
        p = p->next;
    }
    if (head != nullptr)
      currentPos = head;
}

#else 
    // DO NOTHING.
#endif // __CRAZYFISH_SINGLELINKED_LIST__

