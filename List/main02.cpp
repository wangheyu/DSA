#include <iostream>
#include "ArrayList02.h"
int main()
{
    ArrayList A;
    A.init(10);
    A.insert(34, 0);
    A.insert(12, 1);
    A.printList();
    return 0;
}