#include <iostream>

int main() {
    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << "head address of the array: " << a << std::endl;
    std::cout << "size of int: " << sizeof(int) << std::endl;
    std::cout << "the third element: " << a[3] << std::endl;
    std::cout << "the address of the third element: " << &a[3] << std::endl;
    std::cout << "the address of the third element after the first element: " << (a + 3) << std::endl;
    std::cout << "the value of the third element after the first element: " << *(a + 3) << std::endl;
    return 0;
}