#include <stdio.h>

void handle_line(char **, int *);
void handle_char(char, char, char *, int *, int *, int *);

int main()
{
	size_t n = 0;
	char *buf = 0;

	int block = 0;

	while (getline(&buf, &n, stdin) != -1) {
		handle_line(&buf, &block);
	}
}

void handle_line(char **line, int *block)
{
	int lncmt = 0;		/* in a line comment */
	int in_qts = 0;		/* in a quoted string */
	char *ln = *line;
	char cur, prev, next;

	while ((cur = *ln++) != '\0') {
		next = *ln;

		handle_char(cur, next, &prev, &lncmt, block, &in_qts);
	}
}

void handle_char(char cur, char next, char *prev, int *lncmt, int *block,
	int *in_qts)
{
	if (cur == '"' && (!(*prev) || *prev != '\\'))
		*in_qts = !(*in_qts);

	if (!(*block) && !(*in_qts) && cur == '/' && next == '*')
		*block = 1;

	if (!(*in_qts) && cur == '/' && next == '/')
		*lncmt = 1;
	if (!(*in_qts) && cur == '\n' && *lncmt)
		*lncmt = 0;

	if (*lncmt || *block) {
		if (!(*in_qts) && cur == '/' && *prev == '*')
			*block = 0;

		*prev = cur;
		return;
	}

	putchar(cur);
}