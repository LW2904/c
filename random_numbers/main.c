#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define RANGE 40
#define ITERS 1000

int generate_number(int d);
float get_standard_dev(int count, int *data);

int main()
{
	int rn, numbers[RANGE] = {0};

	srand((unsigned) time(NULL));

	for (int i = 0; i < ITERS; i++) {
		numbers[generate_number(RANGE)]++;
	}

	for (int i = 0; i < RANGE; i++) {
		printf("%3d: %d\n", i - (RANGE / 2), numbers[i]);
	}

	int unstbl = get_standard_dev(RANGE, numbers) * 10;
	printf("unstableness: %d\n", unstbl);

	return 0;
}

int generate_number(int d)
{
	int ra = (rand() % d);
	int rb = (rand() % (d / 2)) * ((ra < (d / 2)) ? -1 : 1);

	return (ra + rb) % d;
}

float get_standard_dev(int count, int *data)
{
	int sum = 0;
	float mean, sd = 0.0;

	for (int i = 0; i < count; i++) {
		sum += data[i];
	}

	mean = sum/10;

	for(int i = 0; i < count; i++)
		sd += pow(data[i] - mean, 2);

	return sqrt(sd / 10);
}