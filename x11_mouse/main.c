#include <time.h>
#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

Screen *screen;
Display *display;

void slp(int delay);
void mouse_set(int x, int y);
void mouse_move(int x, int y);

int main()
{
	display = XOpenDisplay(0);
	screen = XScreenOfDisplay(display, XDefaultScreen(display));

	int width, height;
	get_screen_dimensions(&width, &height);

	
}

void get_screen_dimensions(int *width, int *height)
{
	*width = XWidthOfScreen(screen);
	*height = XHeightOfScreen(screen);
}

void mouse_move(int x, int y)
{
	XTestFakeRelativeMotionEvent(display, x, y, 1000);
	XFlush(display);
}

void mouse_set(int x, int y)
{
	XTestFakeMotionEvent(display, 0, x, y, 0);
	XFlush(display);
}

void slp(int delay)
{
	nanosleep((struct timespec[]){{ 0, (long)(delay * 1000) }}, NULL);
}