#include "SingleList.h"

#include <iostream>
#include <utility>


int main()
{
    SingleLinkedList<int> list1 = {1, 2, 3, 4, 5};
    list1.printList();
    std::cout << "Size of list1: " << list1.getSize() << std::endl;
    std::cout << "Current value of list1: " << list1.getCurrentVal() << std::endl;
    list1.setCurrentVal(10);
    std::cout << "Current value of list1: " << list1.getCurrentVal() << std::endl;
    list1.printList();
    SingleLinkedList<int> list2(list1);
    list2.printList();
    
    // 会先调用 SingleLinkedList<int> {6, 7, 8, 9, 10}， 然后调用拷贝构造函数。
    // 实际上由于编译器的优化，SingleLinkedList<int> {6, 7, 8, 9, 10} 会直接生成到目标变量，
    // 而不是先生成一个临时变量，然后再拷贝到目标变量。也就是直接生成到 list3。
    SingleLinkedList<int> list3(SingleLinkedList<int> {6, 7, 8, 9, 10});
    list3.printList();

    list1 = list2 = list3;
    list1.printList();
    list2.printList();
    list3.printList();

    list1.insert(100);
    list1.insert(100);
    list1.printList();
    list1.remove();
    list1.remove();
    list1.printList();
    return 0;
}