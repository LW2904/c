#include <stdio.h>

void handle_line(char **, int *, int *, int *, int *, int *, int *);

int line_number = 0;
int column_number = 0;

int main()
{
	int sqt = 0;	// open single quote?
	int dqt = 0;	// open double quote?
	int par = 0;	// open paratheses
	int brc = 0;	// open braces
	int brk = 0;	// open brackets

	int bcmt = 0;	// currently in a block comment?

	size_t n = 0;
	char *buf = 0;

	while (getline(&buf, &n, stdin) != -1)
		handle_line(&buf, &sqt, &dqt, &par, &brc, &brk, &bcmt);

	printf("sqt: %d, dqt: %d, par: %d, brc: %d, brk: %d\n",
		sqt, dqt, par, brc, brk);

	if ((sqt + dqt + par + brc + brk) != 0)
		printf("check failed\n");
}

void handle_line(char **line, int *sqt, int *dqt, int *par, int *brc, int *brk,
	int *bcmt)
{
	line_number++;

	int lcmt = 0;	// currently in a line comment?

	char *ln = *line;
	char cur, prev, next;

	while ((cur = *ln++) != '\0') {
		column_number++;

		if (cur == '\n')
			column_number = 0;

		next = *ln;
		prev = *(ln - 2);

		printf("Ln %d, Col %d - %c/%c/%c\n",
			line_number, column_number, prev, cur, next);

		if (prev == '\\') {
			printf("skipping escaped %s\n", &cur);
			continue;
		}

		if (cur == '*' && prev == '/')
			*bcmt = 1;
		if (cur == '/' && prev == '*')
			*bcmt = 0;
		
		if (*bcmt) {
			printf("currently in a block comment\n");
			continue;
		}

		if (cur == '/' && prev == '/')
			lcmt = 1;
		if (lcmt && cur == '\n')
			lcmt = 0;

		if (lcmt) {
			printf("currently in a line comment\n");
			continue;
		}

		switch (cur) {
		case '\'':
			*sqt = !(*sqt);		
			break;
		case '"':
			*dqt = prev == '\'' ? *dqt : !(*dqt);
			break;
		}

		if (*sqt || *dqt) {
			printf("open single or double quote (%d, %d)\n",
				*sqt, *dqt);
			continue;
		}

		switch (cur) {
		case '(': (*par)++;
			break;
		case ')': (*par)--;
			break;
		case '{': (*brc)++;
			break;
		case '}': (*brc)--;
			break;
		case '[': (*brk)++;
			break;
		case ']': (*brk)--;
			break;
		}
	}
}