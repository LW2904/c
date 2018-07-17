#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i, r;

	for (i = 0; i < 10; i++) {
		r = (rand() % 20) - 10;

		printf("%d\n", r);
	}
}