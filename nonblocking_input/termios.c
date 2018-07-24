#include <stdio.h>
#include <termios.h>

void restore_keyboard();
void set_keyboard_nonblock();

void restore_keyboard(struct termios *initial)
{
	tcsetattr(0, TCSANOW, initial);
}

void set_keyboard_nonblock(struct termios *initial)
{
	struct termios new;
	tcgetattr(0, initial);

	new = *initial;

	new.c_lflag &= ~ECHO;
	new.c_lflag &= ~ISIG;
	new.c_lflag &= ~ICANON;

	new.c_cc[VMIN] = 0;
	new.c_cc[VTIME] = 0;

	tcsetattr(0, TCSANOW, &new);
}

int main()
{
	char c = 0;
	struct termios term_settings;

	set_keyboard_nonblock(&term_settings);

	while ((c = getchar()) != 'q') {
		if (c < 0)
			continue;

		printf("read: %c", c);
	}

	restore_keyboard(&term_settings);
}