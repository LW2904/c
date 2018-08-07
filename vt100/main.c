#include <stdio.h>

#define ASCII_ESC 27

int main()
{
	setbuf(stdout, NULL);

	printf("%c[6n", ASCII_ESC);
}