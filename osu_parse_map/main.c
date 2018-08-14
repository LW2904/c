#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main()
{
	FILE *stream;
	char line[MAX_LINE_LENGTH];

	if (!(stream = fopen("map.osu", "r"))) {
		return 0;
	}

	size_t len = 0;
	while (fgets(line, sizeof(line), stream)) {
		if (line[0] == '[' && line[(len = strlen(line)) - 2] == ']')
			printf("(%d, %d, %d, %d) SECTION: %s", len, line[len - 2], line[len - 1], line[len], line);
	}

	return 0;
}