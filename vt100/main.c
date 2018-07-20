#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DRAW_CHAR '#'

#define ENMY_W 10
#define ENMY_H 10

void clear_screen(void);
void print_message(char *msg);
void move_cursor(int x, int y);
void draw_vertical_line(short length);
void draw_horizontal_line(short length);
void draw_enemy(short width, short height);
void move_cursor_by(short delta_x, short delta_y);

int cur_x;
int cur_y;

int term_height;

int main()
{
	setbuf(stdout, NULL);

	cur_x = cur_y = 0;

	int i = 0;
	while (++i) {
		clear_screen();

		move_cursor_by(i + ENMY_W, (i * 2) + ENMY_H);

		draw_enemy(ENMY_W, ENMY_H);

		sleep(1);
	}

	return 0;
}

void clear_screen()
{
	printf("\e[2J");

	move_cursor(0, 0);
}

void move_cursor(int x, int y)
{
	if (x < 0 || y < 0) print_message("constraint error\n");

	if (x < 0) x = 0;
	if (y < 0) y = 0;

	cur_x = x;
	cur_y = y;

	printf("\e[%d;%dH", x, y);

	// char *buf = malloc(256);
	// sprintf(buf, "\e[%d;%dH\n", x, y);

	// puts(buf);
	// free(buf);
}

void move_cursor_by(short delta_x, short delta_y)
{
	move_cursor(cur_x + delta_x, cur_y + delta_y);
}

void draw_enemy(short width, short height)
{
	int old_x = cur_x, old_y = cur_y;

	draw_vertical_line(height + 1);

	// move_cursor_by((width / 2) * -1, (height / 2) * -1);

	// draw_line(width);

	// move_cursor_by(0, -1);

	// // for (int i = 0; i < height - 2; i++) {
	// // 	putchar(DRAW_CHAR);
	// // 	move_cursor_by(width - 1, 0);

	// // 	putchar(DRAW_CHAR);
	// // 	move_cursor_by((width - 1) * -1, -1);
	// // }

	// draw_line(width);

	// move_cursor(old_x, old_y);
}

void draw_horizontal_line(short length)
{
	int old_x = cur_x, old_y = cur_y;

	for (int i = 0; i < length; i++) {
		putchar(DRAW_CHAR);
	}

	move_cursor(old_x, old_y);
}

void draw_vertical_line(short length)
{
	int old_x = cur_x, old_y = cur_y;

	for (int i = 0; i < length; i++) {
		putchar(DRAW_CHAR);

		move_cursor_by(0, (-1));
	}

	move_cursor(old_x, old_y);	
}

void print_message(char *msg)
{
	int old_x = cur_x, old_y = cur_y;
	
	move_cursor(0, 0);

	printf("%s", msg);

	move_cursor(old_x, old_y);	
}