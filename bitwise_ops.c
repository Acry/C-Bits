#include <stdio.h>
#include <stdlib.h>

/*
 * C bitwise operators
 * 6 of them:
 * >> shift right
 * << shift left
 * ~ NOT
 * & AND
 * | OR
 * ^ XOR
 * 
 */

/*
 * 
 * Look dox.svg for truth tables and other stuff.
 * And check https://github.com/Acry/Byte_Drawer for an
 * interactive visualisation.
 *
 */

void traverse_byte(unsigned char);

int main(int argc, char **argv)
{

	(void)argc;
	(void)argv;

	printf("Hello Bits!\n\n");

	// Byte unset
	unsigned char x = 0;
	traverse_byte(x); // 1
	// 00000000

	// Byte set
	x = 1;
	traverse_byte(x); // 2
	// 00000001

	// >> Shift left by 4
	x = x << 4;
	traverse_byte(x); // 3
	// 00010000

	// >> Shift Right by 1
	x = x >> 1;
	traverse_byte(x); // 4
	// 00001000

	// ~ NOT
	// Inverts Bits
	x = ~x;
	traverse_byte(x); // 5
	// 11110111

	// & AND
	// Both set results in set
	unsigned char a = 0;
	unsigned char b = 0xff;
	unsigned char c = a & b;
	traverse_byte(c); // 6
	// 00000000

	a = 1;
	b = 1;
	c = a & b;
	traverse_byte(c); // 7
	// 00000001

	// | OR
	// any set results in set
	a = 85;
	b = 170;
	c = a | b;
	traverse_byte(c); // 8
	// 11111111

	// ^ XOR
	// either set results in set, but not both
	a = 213;
	c = a ^ b;
	traverse_byte(c); // 9
	// 01111111

	return EXIT_SUCCESS;
}

void traverse_byte(unsigned char c)
{
	static unsigned int count = 1;
	printf("%d: ", count);
	for (int i = 0; i < 8; i++)
	{
		printf("%d", !!((c << i) & 0x80));
	}
	printf("\n\n");
	count++;
}
