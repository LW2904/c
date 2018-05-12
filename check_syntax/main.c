#include <stdio.h>

struct comment {
	int line;
	int block;
};

struct walker {
	char cur;
	char prev;
	char next;
};

void handle_line(char **, struct comment *);
void handle_char(struct walker *, struct comment *);

int main()
{
	struct comment cmt = { 0, 0 };

	size_t n = 0;
	char *buf = 0;

	while (getline(&buf, &n, stdin) != EOF)
		handle_line(&buf, &cmt);
}

void handle_line(char **line, struct comment *cmt)
{
	char cur;
	char *ln = *line;

	while ((cur = *ln++) != 0) {
		struct walker step = { cur, *ln - 2, *ln };

		handle_char(&step, &cmt);
	}
}

void handle_char(struct walker *step, struct comment *cmt)
{
	if (step->prev == '\\')
		return;

	if (step->cur == '/' && step->next == '*')
		cmt->block = 1;
	if (step->cur == '*' && step->next == '/')
		cmt->block = 0;

	if (cmt->block)
		return;

	if (step->cur == '/' && step->next == '/')
		cmt->line = 1;
	if (cmt->line && step->cur == '\n')
		cmt->line = 0;

	if (cmt->line)
		return;

	putchar(cmt->line);
}