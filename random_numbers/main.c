#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define RANGE 40
#define ITERS 1000

float get_standard_dev(int count, int *data);
static inline int is_in(int x, int from, int to);
int generate_number(int range, int rounds, float bound);

int main()
{
	int rn, numbers[RANGE] = {0};

	srand((unsigned) time(NULL));

	for (int i = 0; i < ITERS; i++) {
		numbers[generate_number(RANGE, 2, 0.5)]++;
	}

	for (int i = 0; i < RANGE; i++) {
		printf("%3d: %d\n", i - (RANGE / 2), numbers[i]);
	}

	int unstbl = get_standard_dev(RANGE, numbers) * 10;
	printf("unstableness: %d\n", unstbl);

	return 0;
}

int generate_number(int range, int rounds, float bound)
{
	int rn;
	float minr = 0.5 - (bound / 2);
	float maxr = 0.5 + (bound / 2);

	rn = rand() % range;

	for (int i = 0; i < rounds; i++) {
		bool in = rn > (range * minr) && rn < (range * maxr);

		rn += (in ? (rand() % (int)(range * minr)) : 0)
			* (rn < (range * 0.5) ? -1 : 1);
	}

	return rn;
}

static inline int is_in(int x, int from, int to)
{
	return x > from && x < to;
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