#include <stdio.h>

unsigned test_bit(unsigned x, int b);

// struct object_type {
// 	unsigned int circle: 1, slider: 1, combo: 1, spinner: 1, skip: 3,
// 		hold: 1
// };

#define CIRCLE 1
#define SLIDER 2
#define HOLD_NOTE 128

int main()
{
	printf("%d\n", 22 & SLIDER)
}

/* Test bit b in x. */
unsigned int test_bit(unsigned int x, int b)
{
	return (x & 1 << b);
}

// void print_bits(unsigned int x)
// {
// 	for (int i = 0; i < sizeof(x); i++)

// }