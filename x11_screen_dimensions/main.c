#include <stdio.h>
#include <X11/Xlib.h>

Window root;
Screen *screen;
Display *display;

void getWindowTerminal();

int main()
{
	display = XOpenDisplay(0);
	root = XDefaultRootWindow(display);
	screen = XScreenOfDisplay(display, XDefaultScreen(display));

	getWindowTerminal();
}

void get_screen_dimensions(int *width, int *height)
{
	*width = XWidthOfScreen(screen);
	*height = XHeightOfScreen(screen);
}

void getWindowTerminal()
{
    Atom a = XInternAtom(display, "_NET_CLIENT_LIST", 1);
    Atom actualType;
    int format;
    unsigned long numItems, bytesAfter;
    unsigned char *data = 0;
    int status = XGetWindowProperty(display, root, a, 0L, (~0L), 0,
                                AnyPropertyType, &actualType, &format, &numItems,
                                &bytesAfter, &data);

    if (status >= Success && numItems)
    {
        long *array = (long*) data;
        for (unsigned long k = 0; k < numItems; k++)
        {
            // get window Id:
            Window w = (Window) array[k];

            char* name = '\0';
            status = XFetchName(display, w, &name);
            if (status >= Success)
            {
		    printf("%s\n", name);
            }
            XFree(name);
        }
        XFree(data);
    }
}