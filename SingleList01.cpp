#include "SingleList01.h"

#include <iostream>

int main()
{
    SingleLinkedList<int> list1 = {1, 2, 3, 4, 5};
    list1.printList();
    std::cout << "Size of list1: " << list1.getSize() << std::endl;
    std::cout << "Current value of list1: " << list1.getCurrentVal() << std::endl;
    list1.setCurrentVal(10);
    std::cout << "Current value of list1: " << list1.getCurrentVal() << std::endl;
    list1.printList();
    return 0;
}