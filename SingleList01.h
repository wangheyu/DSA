#ifndef __CRAZYFISH_SINGLELINKED_LIST__
#define __CRAZYFISH_SINGLELINKED_LIST__

#include <iostream>
#include <limits>
#include <initializer_list>

template <typename T>
class SingleLinkedList
{
private:
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
         Node(const T& _val) {data = _val;};

         friend class SingleLinkedList<T>;
    };

    Node* head = nullptr;	        /**< 头指针. */
    Node* currentPos = nullptr;	    /**< 当前位置的指针. 除非是空链表, 否则该指针不能空. */
    int size = 0;		            /**< 节点总数. */
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
     * @return 将当前位置移动到第一个找到的元素, 如果没有找到, 则当前
     * 位置不动.
     */
     void find(const T& _val);

    /** 
     * 判定链表是否为空.
     * 
     * 
     * @return 空链表返回 true, 非空返回 false.
     */
    bool is_empty() const;

    int getSize() const {return size;};

    const T& getCurrentVal() const {return currentPos->data;};

    void setCurrentVal(const T& _val) {currentPos->data = _val;};
};

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
void SingleLinkedList<T>::makeEmpty()
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
SingleLinkedList<T>::~SingleLinkedList()
{
    makeEmpty();
}

#else 
    // DO NOTHING.
#endif // __CRAZYFISH_SINGLELINKED_LIST__

