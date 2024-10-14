#include <iostream>

int main()
{
    int A = 100;
    int *B = &A;
    std::cout << "A = " << A << std::endl;
    std::cout << "The address of A is:" << &A << std::endl;
    std::cout << "B = " << B << std::endl;
    std::cout << "The value of B is:" << *B << std::endl;
    A = 200;
    std::cout << "A = " << A << std::endl;
    std::cout << "The address of A is:" << &A << std::endl;
    std::cout << "B = " << B << std::endl;
    std::cout << "The value of B is:" << *B << std::endl;
    *B = 300;
    std::cout << "A = " << A << std::endl;
    std::cout << "The address of A is:" << &A << std::endl;
    std::cout << "B = " << B << std::endl;
    std::cout << "The value of B is:" << *B << std::endl;
    B = new int;
    *B = 400;
    std::cout << "A = " << A << std::endl;
    std::cout << "The address of A is:" << &A << std::endl;
    std::cout << "B = " << B << std::endl;
    std::cout << "The value of B is:" << *B << std::endl;
    return 0;
}