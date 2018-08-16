#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <X11/Xlib.h>

Display *display;

Window find_window(pid_t pid);
pid_t get_window_pid(Window window);
int is_window_visible(Window window);
int is_window_match(Window window, pid_t pid);
void search_children(pid_t pid, Window window, Window *out);
int get_window_name(Window window, char *title, int title_len);
unsigned char *get_window_property(Window window, Atom atom, size_t *num_items);


int main(int argc, char *argv[])
{
	const pid_t pid = atoi(argv[1]);

	if(!(display = XOpenDisplay(NULL))) {
		printf("error: failed opening display\n");
	}

	Window window;
	if (!(window = find_window(pid))) {
		printf("error: couldn't find window\n");

		return 1;
	}

	printf("window found: %d\n", (int)window);

	const int name_len = 256;
	char name[name_len];

	get_window_name(window, name, name_len);

	printf("window name: %s\n", name);

	return 0;
}

Window find_window(pid_t pid)
{
	Window root = RootWindow(display, 0), found = 0;

	search_children(pid, root, &found);

	if (found) {
		return found;
	}

	return 0;
}

void search_children(pid_t pid, Window window, Window *out)
{
	size_t num_children = 0;
	Window dummy, *children = NULL;

	int success = XQueryTree(display, window, &dummy, &dummy, &children,
		(unsigned *)&num_children);
	
	if (!success) {
		if (children)
			XFree(children);

		printf("error: failed getting children of %ld\n", window);

		return;
	}

	for (size_t i = 0; i < num_children; i++) {
		Window child = children[i];

		if (is_window_match(child, pid)) {
			*out = child;			

			return;
		}
	}

	for (size_t i = 0; i < num_children; i++) {
		search_children(pid, children[i], out);
	}
}

int is_window_match(Window window, pid_t pid)
{
	if (get_window_pid(window) != pid)
		return 0;

	if (!(is_window_visible(window)))
		return 0;

	return 1;
}

pid_t get_window_pid(Window window)
{
	size_t num_items;
	unsigned char *data;

	static Atom pid_atom = -1;

	if (pid_atom == (Atom)-1) {
		pid_atom = XInternAtom(display, "_NET_WM_PID", 0);
	}

	data = get_window_property(window, pid_atom, &num_items);

	pid_t pid = (num_items > 0) ? ((pid_t) *((unsigned long *)data)) : 0;

	XFree(data);
	
	return pid;
}


unsigned char *get_window_property(Window window, Atom atom, size_t *num_items)
{
	Atom actual_type;
	int actual_format;

	size_t bytes_after;
	static unsigned char *prop;

	int status = XGetWindowProperty(display, window, atom, 0, (~0L), 0,
		AnyPropertyType, &actual_type, &actual_format, num_items,
		&bytes_after, &prop);

	if (status != Success) {
		printf("error: failed getting window (%ld) property\n", window);

		return NULL;
	}

	return prop;
}

int is_window_visible(Window window)
{
	XWindowAttributes attr;
	int success = XGetWindowAttributes(display, window, &attr);

	if (!success) {
		printf("error: failed getting window (%ld) attributes\n",
			window);

		return 0;
	}

	if (attr.map_state != IsViewable) {
		return 0;
	}

	return 1;
}

int get_window_name(Window window, char *title, int title_len)
{
	static Atom net_name_atom = -1, name_atom = -1;

	if (name_atom == (Atom)-1)
		name_atom = XInternAtom(display, "WM_NAME", 0);
	if (net_name_atom == (Atom)-1)
		net_name_atom = XInternAtom(display, "_NET_WM_NAME", 0);

	 // http://standards.freedesktop.org/wm-spec/1.3/ar01s05.html
	 // Prefer _NET_WM_NAME if available, otherwise use WM_NAME

	size_t num_items = 0;

	unsigned char *prop = get_window_property(window, net_name_atom,
		&num_items);

	if (!num_items) {
		prop = get_window_property(window, name_atom, &num_items);
	}

	strcpy(title, (char *)prop);

	return 0;
}
