#include <unistd.h>
#include <stdio.h>

int main()
{
	long long i = 0;

	getchar();

	while (++i && sleep(1) == 0) {
		printf("%d\n", i);
	}
}