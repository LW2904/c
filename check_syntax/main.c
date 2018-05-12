#include <stdio.h>

struct syntax {
	int sqt;	// open single quotes?
	int dqt;	// open double quotes?
	int par;	// open parentheses
	int brc;	// open braces
	int brk;	// open brackets
	int bcmt;	// in a block comment?
	int lcmt; 	// in a line comment?
};

void handle_char(char *, struct syntax *);
void handle_line(char **, struct syntax *);

int main()
{
	struct syntax syn = { 0, 0, 0, 0, 0, 0, 0 };

	size_t n = 0;
	char *buf = 0;

	while (getline(&buf, &n, stdin) != EOF)
		handle_line(&buf, &syn);

	printf("\nsqt: %d, dqt: %d, par: %d, brc: %d, brk: %d\n",
		syn.sqt, syn.dqt, syn.par, syn.brc, syn.brk);
}

void handle_line(char **line, struct syntax *syn)
{
	char *walker;
	char *ln = *line;

	while (*(walker = ln++) != 0)
		handle_char(walker, syn);
}

void handle_char(char *cur, struct syntax *syn)
{
	if (*(cur - 1) == '\\' && *(cur - 2) != '\\')
		return;

	if (*cur == '/' && *(cur + 1) == '*')
		syn->bcmt = 1;
	if (*(cur - 2) == '*' && *(cur - 1) == '/')
		syn->bcmt = 0;

	if (syn->bcmt)
		return;

	if (*cur == '/' && *(cur + 1) == '/')
		syn->lcmt = 1;
	if (syn->lcmt && *cur == '\n')
		syn->lcmt = 0;

	if (syn->lcmt)
		return;

	switch(*cur) {
	case '\'':
		syn->sqt = syn->dqt ? syn->sqt : !syn->sqt;
		break;
	case '"':
		syn->dqt = syn->sqt ? syn->dqt : !syn->dqt;
		break;
	}

	if (syn->sqt || syn->dqt)
		return;

	switch(*cur) {
	case '(':
		syn->par++;
		break;
	case ')':
		syn->par--;
		break;
	case '{':
		syn->brc++;
		break;
	case '}':
		syn->brc--;
		break;
	case '[':
		syn->brk++;
		break;
	case ']':
		syn->brk--;
		break;
	}
}
