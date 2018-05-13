#include <stdio.h>

#define MAXCOL 5
#define MAXCHAR 20

void fold_line_char(char *, int);
void fold_line_word(char *, int);

int main()
{
	size_t n = 0;
	char *buf = 0;

	while (getline(&buf, &n, stdin) != -1)
		fold_line_word(buf, MAXCHAR);
}

void fold_line_char(char *ln, int max)
{
	char c;
	int i = 0;

	while ((c = *ln++) != '\0') {
		if (i >= max) {
			i = 0;
			putchar('\n');
		}

		putchar(c);

		i++;
	}
}

void fold_line_word(char *ln, int max)
{
	int i = 0;

	while (*ln++ != '\0') {
		if (i >= max && *(ln - 2) == ' ') {
			i = 0;
			putchar('\n');
		}

		putchar(*(ln - 1));

		i++;
	}
}