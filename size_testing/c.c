#include <stdio.h>

#define SIGNATURE "\xDB\x5D\xE8\x8B"

void do_something(unsigned char *pattern);

int main()
{
	printf("%d\n", sizeof(SIGNATURE));

	do_something(SIGNATURE);

	return 0;
}

void do_something(unsigned char *pattern)
{
	printf("%d", sizeof(pattern));
}
