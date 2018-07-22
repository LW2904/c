#include <stdio.h>

void print_bytes(int *x);

int main()
{
	int x = 12578329;
	int y = -12578329;

	print_bytes(&x);
	puts("");
	print_bytes(&y);
}

void print_bytes(int *x)
{
	for (size_t i = 0; i < sizeof(*x); i++) {
		unsigned char byte = *((unsigned char *)x + i);

		printf("%2d: %u (%x)\n", (int)i, byte, byte);
	}
}