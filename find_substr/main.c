#include <stdio.h>

#define MAXLEN 100;

int any(char *, char *);

int main()
{
	printf("%d\n", any("test", "s"));
}

int any(char *base, char *sub)
{
	int i, j, k = 0;

	while (sub[k] != '\0')
		k++;

	for (i = 0; base[i] != '\0'; i++) {	
		for (j = 0; sub[j] != '\0' && base[j + i] == sub[j]; j++)
			;

		if (j == k) return i;
	}

	return -1;
}