#include "List.h"
#include <iostream>

int main()
{
    List<int> lst;
    for (int i = 0; i < 10; ++i)
    {
        lst.push_back(i);
    }

    for (auto it = lst.begin(); it != lst.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    return 0;
}
