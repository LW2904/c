#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DRAW_CHAR '#'


// void print_message(char *msg);
// void move_cursor(int x, int y);
// void draw_vertical_line(short length);
// void draw_horizontal_line(short length);
// void draw_enemy(short width, short height);
// void move_cursor_by(short delta_x, short delta_y);

/**
 * screen_ functions operate on the terminal as one construct.
 */
void screen_clear(void);

/**
 * cursor_ functions, related to movement of the cursor.
 */
void cursor_move(int x, int y, int back);
void cursor_move_by(int delta_x, int delta_y);

/**
 * Utility functions.
 */
static inline int constrain_above(int orig, int min);

int cur_x;
int cur_y;

int main()
{
	// Disable stdout buffering.
	setbuf(stdout, NULL);

	// 0/0 is home.
	cur_x = cur_y = 0;

	int i = 0;
	while (++i) {
		screen_clear();

		cursor_move_by(i, i);

		cursor_move(0, 0, 1);

		sleep(1);
	}

	return 0;
}

void screen_clear()
{
	printf("\e[2J");

	cursor_move(0, 0, 0);
}

void cursor_move(int x, int y, int back)
{
	static int old_x = 0;
	static int old_y = 0;

	if (back) {
		printf("%d / %d", old_x, old_y);
		return cursor_move(old_x, old_y, 0);
	}

	old_x = x;
	old_y = y;

	cur_x = constrain_above(x, 0);
	cur_y = constrain_above(y, 0);

	printf("\e[%d;%dH", x, y);
}

void cursor_move_by(int delta_x, int delta_y)
{
	cursor_move(cur_x + delta_x, cur_y + delta_y, 0);
}

void status_pos_update()
{

}

static inline int constrain_above(int orig, int min)
{
	return orig < min ? min : orig;
}

// void draw_enemy(short width, short height)
// {
// 	int old_x = cur_x, old_y = cur_y;

// 	draw_vertical_line(height + 1);

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

// 	// move_cursor(old_x, old_y);
// }

// void draw_horizontal_line(short length)
// {
// 	int old_x = cur_x, old_y = cur_y;

// 	for (int i = 0; i < length; i++) {
// 		putchar(DRAW_CHAR);
// 	}

// 	move_cursor(old_x, old_y);
// }

// void draw_vertical_line(short length)
// {
// 	int old_x = cur_x, old_y = cur_y;

// 	for (int i = 0; i < length; i++) {
// 		putchar(DRAW_CHAR);

// 		move_cursor_by(0, (-1));
// 	}

// 	move_cursor(old_x, old_y);	
// }

// void print_message(char *msg)
// {
// 	int old_x = cur_x, old_y = cur_y;
	
// 	move_cursor(0, 0);

// 	printf("%s", msg);

// 	move_cursor(old_x, old_y);	
// }