#include <iostream>

int main(void)
{
    char buf[512];

    std::cout << "Hello world !" << std::endl;

    std::cout << "Input o world: ";
    std::cin >> buf;
    std::cout << "You entred: [" << buf << "]" << std::endl;

    return 0;
}