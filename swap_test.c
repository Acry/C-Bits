#include <stdio.h>
#include <stdlib.h>
#include "order32.h"
#include <byteswap.h>
#include "endian.h"

/** 
 * WIP - Scratchpad
 */

/**
 * 00 00 b5 03
 * [32-bit]unsigned long: 0 to 4294967295
 * unsigned char b=0xFAFA;
 * 32 Bit = 4 Byte = Double Word
 * 
 * result = ((valueToSwap >> 16) & 0xFFF | (valueToSwap << 16))
 * result = (valueToSwap >> 16) | (valueToSwap << 16)
 */

void printBits(size_t const, void const *const);
void printbits(unsigned long, unsigned int);
void printHex(char *, int);
void splitBytes(size_t, void *);
void printByteAsBits(unsigned char);

int main(int argc, char **argv)
{

	(void)argc;
	(void)argv;

	if (O32_HOST_ORDER == O32_LITTLE_ENDIAN)
		printf("- Byte Order is little endian, as expected\n");
	printf("- %zu bit system\n", sizeof(void *) * 8);
	printf("- size of long uInt in Bytes: %zu\n", sizeof(unsigned long int));
	printf("- size of uInt in Bytes: %zu\n\n", sizeof(unsigned int));

	unsigned int ref1 = 0;
	// printBits(sizeof(ref1), &ref1);

	unsigned int ref2 = 1;
	// printBits(sizeof(ref2), &ref2);

	unsigned int ref3 = 16909060;
	unsigned int simon = 0x0000b503;
	unsigned int wiki = 12967;
	int **ref3A = &ref3;
	printf("-----------------------------\n");
	printf("\nSize of ref3 in Bytes: %zu\n", sizeof(ref3));
	splitBytes(sizeof(wiki), &wiki);
	printHex((char *)&wiki, sizeof(wiki));
	// printHex((char *)&i, sizeof(i));
	// printBits(sizeof(ref3), &ref3);
	printf("-----------------------------\n");
	// unsigned short int ref3 = 0x0401; // 1025
	// printBits(sizeof(ref3), &ref3);

	unsigned int source = 0x0000b503;
	// printBits(sizeof(source), &source);

	unsigned int op1 = source >> 16 | source << 16;
	// printBits(sizeof(op1), &op1);

	unsigned int op2 = (source >> 16) | (source << 16);
	// printBits(sizeof(op2), &op2);

	unsigned int op3 = ((source >> 16) & 0xFFFF | (source << 16));
	// printBits(sizeof(op3), &op3);

	unsigned int op4 = __bswap_32(source);
	// printf("size of op4 in Bytes: %zu\n", sizeof(op4));
	// printBits(sizeof(op4), &op4);

	// unsigned int a = 0x01234567;
	// printBits(sizeof(a), &a);
	unsigned int i = 0x01234567;
	// printBits(sizeof(i), &i);
	// printHex((char *)&i, sizeof(i));
	// printf("Size of i in Bytes: %zu\n\n", sizeof(i));
	return EXIT_SUCCESS;
}

// Assumes little endian
void printBits(size_t const size, void const *const ptr)
{
	static unsigned int count = 1;
	printf("%d:", count);
	unsigned char *b = (unsigned char *)ptr;
	unsigned char byte;
	int i, j;

	for (i = size - 1; i >= 0; i--)
	{
		printf(" ");
		for (j = 7; j >= 0; j--)
		{
			byte = (b[i] >> j) & 1;
			printf("%u", byte);
		}
	}
	puts("");
	count++;
}

void printHex(char *start, int n)
{
	for (int i = 0; i < n; i++)
		printf("%.2x ", start[i]);
	printf("\n");
}

void splitBytes(size_t size, void *value)
{
	unsigned char bytes[size];
	memcpy(&bytes, value, size);
	// LE
	for (int i = size - 1; i >= 0; i--)
	{
		printByteAsBits(bytes[i]);
		printf(" ");
	}
	printf("\n");
}

void printByteAsBits(unsigned char c)
{
	// int8_t and uint8_t are typedef to char on platforms where 1 byte is 8 bits.
	// POSIX specification demands that CHAR_BIT == 8
	for (int i = 0; i < 8; i++)
	{
		printf("%d", !!((c << i) & 0x80));
	}
}