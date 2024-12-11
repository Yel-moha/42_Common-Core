/* #include "ft_printf.h"

int main(void)
{
	int ret1, ret2;
	int test_count = 0;
	char str[25] = "0x12345678";

	// Test 1
	ret1 = ft_printf("Character: %c\n", 'A');
	ret2 = printf("Character: %c\n", 'A');
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 2
	ret1 = ft_printf("String: %s\n", "Hello, World!");
	ret2 = printf("String: %s\n", "Hello, World!");
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 3
	ret1 = ft_printf("Pointer: %p\n", (void *)str);
	ret2 = printf("Pointer: %p\n", (char *)str);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 4
	ret1 = ft_printf("Decimal: %d\n", 12345);
	ret2 = printf("Decimal: %d\n", 12345);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 5
	ret1 = ft_printf("Integer: %i\n", -12345);
	ret2 = printf("Integer: %i\n", -12345);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 6
	ret1 = ft_printf("Unsigned: %u\n", 12345);
	ret2 = printf("Unsigned: %u\n", 12345);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 7
	ret1 = ft_printf("Hexadecimal (lowercase): %x\n", 0x123abc);
	ret2 = printf("Hexadecimal (lowercase): %x\n", 0x123abc);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 8
	ret1 = ft_printf("Hexadecimal (uppercase): %X\n", 0x123ABC);
	ret2 = printf("Hexadecimal (uppercase): %X\n", 0x123ABC);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 9
	ret1 = ft_printf("Percent: %%\n");
	ret2 = printf("Percent: %%\n");
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 10
	ret1 = ft_printf("Null string: %s\n", NULL);
	ret2 = printf("Null string: %s\n", NULL);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 11
	ret1 = ft_printf("Multiple args: %c %s %p %d %i %u %x %X %%\n", 'A', "Hello", (void *)0x12345678, 12345, -12345, 12345, 0x123abc, 0x123ABC);
	ret2 = printf("Multiple args: %c %s %p %d %i %u %x %X %%\n", 'A', "Hello", (void *)0x12345678, 12345, -12345, 12345, 0x123abc, 0x123ABC);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 12
	ret1 = ft_printf("Empty string: %s\n", "");
	ret2 = printf("Empty string: %s\n", "");
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 13
	ret1 = ft_printf("Zero: %d\n", 0);
	ret2 = printf("Zero: %d\n", 0);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 14
	ret1 = ft_printf("Negative: %d\n", -1);
	ret2 = printf("Negative: %d\n", -1);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 15
	ret1 = ft_printf("Large number: %d\n", 2147483647);
	ret2 = printf("Large number: %d\n", 2147483647);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 16
	ret1 = ft_printf("Small number: %d\n", -2147483648);
	ret2 = printf("Small number: %d\n", -2147483648);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 17
	ret1 = ft_printf("Unsigned large: %u\n", 4294967295);
	ret2 = printf("Unsigned large: %u\n", 4294967295);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 18
	ret1 = ft_printf("Hexadecimal zero: %x\n", 0);
	ret2 = printf("Hexadecimal zero: %x\n", 0);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 19
	ret1 = ft_printf("Hexadecimal large: %x\n", 4294967295);
	ret2 = printf("Hexadecimal large: %x\n", 4294967295);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 20
	ret1 = ft_printf("Hexadecimal uppercase zero: %X\n", 0);
	ret2 = printf("Hexadecimal uppercase zero: %X\n", 0);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 21
	ret1 = ft_printf("Hexadecimal uppercase large: %X\n", 4294967295);
	ret2 = printf("Hexadecimal uppercase large: %X\n", 4294967295);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 22
	ret1 = ft_printf("Character: %c\n", 'Z');
	ret2 = printf("Character: %c\n", 'Z');
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 23
	ret1 = ft_printf("String: %s\n", "Test");
	ret2 = printf("String: %s\n", "Test");
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 24
	ret1 = ft_printf("Pointer: %p\n", (void *)0x0);
	ret2 = printf("Pointer: %p\n", (void *)0x0);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 25
	ret1 = ft_printf("Decimal: %d\n", -98765);
	ret2 = printf("Decimal: %d\n", -98765);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 26
	ret1 = ft_printf("Integer: %i\n", 98765);
	ret2 = printf("Integer: %i\n", 98765);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 27
	ret1 = ft_printf("Unsigned: %u\n", 98765);
	ret2 = printf("Unsigned: %u\n", 98765);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 28
	ret1 = ft_printf("Hexadecimal (lowercase): %x\n", 0xabcdef);
	ret2 = printf("Hexadecimal (lowercase): %x\n", 0xabcdef);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 29
	ret1 = ft_printf("Hexadecimal (uppercase): %X\n", 0xABCDEF);
	ret2 = printf("Hexadecimal (uppercase): %X\n", 0xABCDEF);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 30
	ret1 = ft_printf("Percent: %%\n");
	ret2 = printf("Percent: %%\n");
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 31
	ret1 = ft_printf("Null string: %s\n", NULL);
	ret2 = printf("Null string: %s\n", NULL);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	// Test 32
	ret1 = ft_printf("Multiple args: %c %s %p %d %i %u %x %X %%\n", 'B', "World", (void *)0x87654321, 54321, -54321, 54321, 0xabcdef, 0xABCDEF);
	ret2 = printf("Multiple args: %c %s %p %d %i %u %x %X %%\n", 'B', "World", (void *)0x87654321, 54321, -54321, 54321, 0xabcdef, 0xABCDEF);
	printf("Test %d - ft_printf: %d, printf: %d\n", ++test_count, ret1, ret2);

	printf("Total tests run: %d\n", test_count);

	return 0;
} */