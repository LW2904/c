#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define ISNUM '0'
#define BUFSIZE 100

double pop(void);
void push(double);
int getch(void);
void ungetch(int);
int getop(char *);

int main()
{
	int type;
	double op2;
	char s[BUFSIZE];

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case ISNUM:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '\n':
			printf("\t%.8g\n", pop()); 
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
}

int getop(char s[])
{
	int i, c;
	
	while ((*s = c = getch()) == ' ' || c == '\t')
		;

	*(s + 1) = '\0';

	if (!isdigit(c) && c != '.')
		return c;

	if (isdigit(c))
		while (isdigit(*(++s) = c = getch()))
 			;

	if (c == '.')
		while (isdigit(*(++s) = c = getch()))
			;

	*s = '\0';

	if (c != EOF)
		ungetch(c);

	return ISNUM;
} 

int bufp = 0;
char buf[BUFSIZE];

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		return (void) printf("ungetch: buffer full\n");

	buf[bufp++] = c;
}

int stackp = 0;
double stack[BUFSIZE];

void push(double i)
{
	if (stackp > BUFSIZE)
		return (void) printf("push: stack full\n");

	stack[stackp++] = i;
}

double pop(void)
{
	if (!stackp)
		return printf("pop: stack empty\n");

	return stack[--stackp];
}