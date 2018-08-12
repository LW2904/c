#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

Window root;
Screen *screen;
Display *display;

void get_window_terminal();

int main()
{
	display = XOpenDisplay(0);
	root = XDefaultRootWindow(display);
	screen = XScreenOfDisplay(display, XDefaultScreen(display));

	get_window_terminal();
}

void get_screen_dimensions(int *width, int *height)
{
	*width = XWidthOfScreen(screen);
	*height = XHeightOfScreen(screen);
}

void get_window_terminal()
{
	Atom property = XInternAtom(display, "_NET_CLIENT_LIST", 1);

	Atom type;
	int format;

	unsigned char *data = 0;
	unsigned long items, bytes;

	int status = XGetWindowProperty(display, root, property, 0L, (~0L), 0,
		0L, &type, &format, &items, &bytes, &data);

	if (status >= Success && items) {
		char *name = malloc(128);		
		long *array = (long *)data;

		for (size_t i = 0; i < items; i++) {
			printf("%#x\n", (unsigned)array[i]);

			Window w = (Window)array[i];

			status = XFetchName(display, w, &name);

			printf("name: %s (%d)\n", name, status);

			// if (status >= Success) {
			// 	printf("%s\n", name);
			// }

			XFree(name);
		}

		XFree(data);
	}
}