#include <windows.h>

#define ON_WINDOWS

static inline void send_keypress(char key, int down);

int main()
{
	send_keypress('a', 1);
	Sleep(100);
	send_keypress('a', 0);	
}

static inline void send_keypress(char key, int down)
{
#ifdef ON_LINUX
	int keycode = XKeysymToKeycode(display, key);

	XTestFakeKeyEvent(display, keycode, down, CurrentTime);

	XFlush(display);
#endif /* ON_LINUX */

#ifdef ON_WINDOWS
	INPUT in;

	in.type = INPUT_KEYBOARD;

	in.ki.wVk = 0;
	in.ki.time = 0;
	in.ki.wScan = key;
	in.ki.dwExtraInfo = 0;
	in.ki.dwFlags = KEYEVENTF_UNICODE | (down ? 0 : KEYEVENTF_KEYUP);

	SendInput(1, &in, sizeof(INPUT));
#endif /* ON_WINDOWS */
}