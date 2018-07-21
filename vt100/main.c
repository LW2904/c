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
 * status_ functions are responsible for the top status bar.
 */
void status_draw();
void status_update();

/**
 * cursor_ functions, related to movement of the cursor.
 */
void curser_move_back();
void cursor_move(int x, int y);
void cursor_move_by(int delta_x, int delta_y);

/**
 * line_ functions provide abstractions over line operations and codes.
 */
void line_erase(int line);

/**
 * Utility functions.
 */
static inline int constrain_above(int orig, int min);

// The current X and Y coordinates of the cursor.
int cur_x = 0;
int cur_y = 0;

// The previous coordinates, for convenient cursor position restoring.
int last_x = 0;
int last_y = 0;

// Most recent warning reported by any function.
char *last_error = NULL;

int main()
{
	// Disable stdout buffering.
	setbuf(stdout, NULL);

	int i = 0;
	while (++i) {
		screen_clear();


		status_draw();
		nanosleep((struct timespec[]){{1, 0}}, NULL);
	}

	return 0;
}

void screen_clear()
{
	printf("\e[2J");

	// ESC[2J should do this by itself but... yeah.
	cursor_move(0, 0);
}

void cursor_move(int x, int y)
{
	last_x = cur_x;
	last_y = cur_y;

	cur_x = constrain_above(x, 0);
	cur_y = constrain_above(y, 0);

	if (cur_x != x || cur_y != y) {
		last_error = "attempted to move beyond cursor constraints";
	}

	printf("\e[%d;%dH", cur_x, cur_y);
}

void cursor_move_by(int delta_x, int delta_y)
{
	cursor_move(cur_x + delta_x, cur_y + delta_y);
}

void cursor_move_back()
{
	cursor_move(last_x, last_y);
}

void status_draw()
{
	// Since we need to move around to draw this, save beforehand.
	int sx = cur_x, sy = cur_y;

	cursor_move(0, 0);
	printf("%3d / %-3d | %s", sx, sy, last_error);
	cursor_move_back();
}

void status_update()
{
	line_erase(0);
	status_draw();
}

void line_erase(int line)
{
	int y = constrain_above(line, 0);

	if (y != line) {
		last_error = "attempted to erase foreign line";
	}

	cursor_move(0, y);
	printf("\e[2K");
	cursor_move_back();
}

/**
 * Return `orig` or `min` if it is not in the range of [min, Infinity[.
 */
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