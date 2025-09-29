#include <iostream>

struct Node
{
    int data;
    Node *next = nullptr;
    Node(int val) : data(val), next(nullptr) {}
    Node(const Node &other) : data(other.data), next(other.next) {}
    Node(Node &&other) : data(other.data), next(other.next)
    {
        other.next = nullptr; // 避免悬挂指针
    }
};

int main()
{
    Node n0 = Node{0, nullptr};

    Node &n1 = n0;
    n1.data = 1;

    Node n2 = n0; // 调用拷贝构造函数
    n2.data = 2;

    Node n3 = std::move(n0); // 调用移动构造函数
    n3.data = 3;

    

    std::cout << n0.data << std::endl;
    return 0;
}