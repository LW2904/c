#include <stdio.h>

#include <X11/Xlib.h>

int main()
{
        Display *display = XOpenDisplay(NULL);

        int sym = XKeysymToKeycode(display, 'a');

        printf("%d\n", sym);
}