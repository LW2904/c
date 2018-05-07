#include <stdio.h>

void handle_line(char **, int *, int *, int *, int *, int *, int *);

int main()
{
	int sqt = 0;	// open single quotes
	int dqt = 0;	// open double quotes
	int par = 0;	// open paratheses
	int brc = 0;	// open braces
	int brk = 0;	// open brackets
	int bcmt = 0;	// currently in a block comment

	size_t n = 0;
	char *buf = 0;

	while (getline(&buf, &n, stdin) != -1)
		handle_line(&buf, &sqt, &dqt, &par, &brc, &brk, &bcmt);

	printf("sqt: %d, dqt: %d, par: %d, brc: %d, brk: %d\n",
		sqt, dqt, par, brc, brk);

	if ((sqt + dqt + par + brc + brk) != 0)
		printf("a quote, brace, bracket or paranthesis was not closed");
	else
		ptinf("everything appears to be in order");
}

void handle_line(char **line, int *sqt, int *dqt, int *par, int *brc, int *brk,
	int *bcmt)
{
	char *ln = *line;
	char cur, prev, next;

	while ((cur = *ln++) != '\0') {
		next = *ln;
		prev = *(ln - 2); 

		if (prev == '\\')
			continue;

		switch (cur) {
		case '\'':
			*sqt += (*sqt % 2 == 0) ? 1 : -1;		
			break;
		case '"':
			*dqt += prev != '\'' ? (*dqt % 2 == 0) ? 1 : -1 : 0;
			break;
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
		default:
			break;
		}
	}
}