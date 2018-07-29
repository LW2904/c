#include <stdio.h>

#define ASCII_ESC 27

void erase_line();
void move_cursor(int x, int y);
void draw_line(int x_from, int y_from, int x_to, int y_to);

int main()
{
	setbuf(stdout, NULL);

	draw_line(1, 1, 3, 2);

	return 1;
}

void move_cursor(int x, int y)
{
	printf("%c[%d;%dH", ASCII_ESC, y, x);
}

void erase_line()
{
	printf("%c[2K", ASCII_ESC);
}

void draw_line(int x_from, int y_from, int x_to, int y_to)
{
	int width = x_to - x_from + 1;
	int slope = ((y_to - y_from + 1) / width) * 1000;

	// for (int i = 0; i <= width; i++) {

	// }

	printf("%d / %d\n", width, slope);
}