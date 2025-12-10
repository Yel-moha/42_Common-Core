#include<unistd.h>

int main(void)
{
    write(1, "Hello world", 11);
    write(1, "\n", 1);
    return (0);
}