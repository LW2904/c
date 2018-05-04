#include <stdio.h>

int main()
{
	double v, sum = 0;

	while (scanf("%lf", &v) == 1)
		printf("\t%f\n", sum += v);

	return 0;
}
