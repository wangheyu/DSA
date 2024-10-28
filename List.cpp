#include "List.h"
#include <iostream>

int main()
{
    List<int> lst;
    for (int i = 0; i < 10; ++i)
    {
        lst.push_back(i);
    }

    for (const auto &it : lst)
    {
        std::cout << it << std::endl;
    }

    // for (auto it = lst.begin(); it != lst.end(); ++it)
    // {
    //     std::cout << *it << std::endl;
    // }

//     List<int> lst = {1, 2, 3, 4, 5};
//     for (auto &x : lst)
//     {
//         std::cout << x << "\t";
//     }
//     std::cout << std::endl;

// //    List<int> lst2 = std::move(lst);
//     List<int> lst2 = List<int> {5, 6};
//     for (auto &x : lst2)
//     {
//         std::cout << x << "\t";
//     }
//     std::cout << std::endl;

//     lst2 = std::move(lst);
//     for (auto &x : lst2)
//     {
//         std::cout << x << "\t";
//     }
//     std::cout << std::endl;

    return 0;
}
