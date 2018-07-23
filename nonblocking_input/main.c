#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

int main(int argc, char** argv)
{
	int kdesc, bytes;
	struct input_event data;

	const char *keyboard = "/dev/input/event3";

	kdesc = open(keyboard, O_RDONLY | O_NONBLOCK);
	if (kdesc == -1) {
		printf("error opening %s\n", keyboard);
		return -1;
	}

	while(1) {
		if (!(read(kdesc, &data, sizeof(data)))) {
			// Nothing to read, go to sleep for 0.5s.
			nanosleep((struct timespec[]){{ 0, 500000000L }}, NULL);
		}

		if (data.value != 1 || !data.code) {
			// Discard, we don't care about this event.
			continue;
		}

		switch (data.code) {
		case KEY_SPACE: printf("space!\n");
			break;
		case KEY_F:  printf("f\n");
			break;
		case KEY_J : printf("j\n");
			break;
		}
	}

	return 0;
}