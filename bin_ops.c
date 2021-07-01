#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Other binary operations
 */

void traverse_byte(char);
unsigned char set_one(unsigned char, int, bool, bool);
unsigned char inv_bit(unsigned char, int);
unsigned char alternate(unsigned char, bool);

int main(int argc, char **argv)
{

	(void)argc;
	(void)argv;

	printf("Hello Bits!\n\n");

	// Byte set
	unsigned char x = 1;
	traverse_byte(x); // 1
	// 00000001

	// Byte shift left by 4 (inline ASM/INTEL)
	int value = 4;
	__asm__("shl %%cl, %%al;"
					: "=a"(x)
					: "a"(x), "c"(value));
	traverse_byte(x); // 2
	// 00010000

	// circular shift right by 5 (inline ASM/INTEL)
	value = 5;
	__asm__("ror %%cl, %%al;"
					: "=a"(x)
					: "a"(x), "c"(value));
	traverse_byte(x); // 3
	// 10000000

	// circular shift left by 1 (inline ASM/INTEL)
	value = 1;
	__asm__("rol %%cl, %%al;"
					: "=a"(x)
					: "a"(x), "c"(value));
	traverse_byte(x); // 4
	// 00000001first

	// Set all on
	x = 0xff;
	traverse_byte(x); // 5
	// 11111111

	// Set all off
	x = 0;
	traverse_byte(x); // 6
	// 00000000

	x = 1;
	x = set_one(x, 0, false, false);
	traverse_byte(x); // 7
	// 00000000

	x = set_one(x, 0, true, false);
	traverse_byte(x); // 8
	// 00000001

	x = inv_bit(x, 3);
	traverse_byte(x); // 9
	// 00001001
	x = inv_bit(x, 3);
	traverse_byte(x); // 10
	// 00000001

	x = set_one(x, 0, false, true);
	traverse_byte(x); // 11
	// 11111110

	x = set_one(x, 0, true, true);
	traverse_byte(x); // 12
	// 00000001

	x = alternate(x, false);
	traverse_byte(x); // 13
	// 01010101

	x = alternate(x, true);
	traverse_byte(x); // 14
	// 10101010

	x = 0;
	// Set bits like in the shift right by 4 example
	x = set_one(x, 1, true, false);
	x = set_one(x, 3, true, false);
	x = set_one(x, 5, true, false);
	x = set_one(x, 7, true, false);
	traverse_byte(x);
	// >> shift right by 4
	x = x >> 4;
	traverse_byte(x);
	return EXIT_SUCCESS;
}

void traverse_byte(char c)
{
	static unsigned int count = 1;
	printf("%d:\n", count);
	for (int i = 0; i < 8; i++)
	{
		printf("%d", !!((c << i) & 0x80));
	}
	printf("\n\n");
	count++;
}

unsigned char set_one(unsigned char byte, int offset, bool state, bool invert)
{
	if (invert == true)
		for (int i = 0; i < 8; i++)
		{
			byte = byte ^ (1 << i);
		}

	if (state == true)
		byte = byte | (1 << offset);
	else
		byte = byte & ~(1 << offset);
	return byte;
}

unsigned char inv_bit(unsigned char byte, int offset)
{
	if (byte & 1 << offset)
		byte = byte & ~(1 << offset);
	else
		byte = byte | (1 << offset);
	return byte;
}

unsigned char alternate(unsigned char byte, bool first)
{
	if (first == true)
		byte = 170;
	else
		byte = 85;
	return byte;
}
