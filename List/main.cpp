#include "ArrayList.h"

int main()
{
    ArrayList list;

    list.insert(1.1, 0);
    list.insert(2.2, 1);
    list.insert(3.3, 2);
    list.insert(4.4, 3);
    list.insert(5.5, 4);

    std::cout << "List: ";
    list.printList();

    std::cout << "Find 3.3 at index: " << list.find(3.3) << std::endl;
    std::cout << "Find 6.6 at index: " << list.find(6.6) << std::endl;

    list.makeEmpty();
    std::cout << "After makeEmpty(), List: ";
    list.printList();

    return 0;
}