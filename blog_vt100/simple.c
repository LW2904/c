#include <stdio.h>

#define ASCII_ESC 27

void erase_line();
void move_cursor(int x, int y);
void draw_graph(int *data, int data_len);

int main()
{
	setbuf(stdout, NULL);

	draw_graph((int[]){ 3, 4, 2, 5, 2 }, 5);

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

void draw_graph(int *data, int data_len)
{
	for (int i = 0; i < data_len; i++) {
		for (int j = data[i]; j >= data[i]; j--) {
			move_cursor(i + 1, 10 + j);
			putchar('#');
		}
	}
}