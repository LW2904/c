#include <stdio.h>

int partial_match(char *base, char *partial);

int main()
{
	int m = partial_match("Chroma - I (Lude) [Heavenly].osu",
		"Chroma - I [Heavenly]");

	printf("%d\n", m);
}

int partial_match(char *base, char *partial)
{
	int i = 0;
	int m = 0;
	while (*base) {
		char c = partial[i];
		if (c == '.') {
			i++;
			continue;
		}

		if (*base++ == c) {
			i++;
			m++;
		}
	}

	return m;
}