#include <iostream>

int main()
{
    int A[] = {1, 3, 5, 7, 9};
    int *B = A;
    std::cout << "A = " << A << std::endl;
    std::cout << "The value of B is:" << *B << std::endl;
   return 0;
}