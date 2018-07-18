#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <inttypes.h>

// Address: 0x1874341C + 85
#define MAP_ADDRESS 0x18743471

int get_mapname(char **name);
unsigned long get_process_id(const char *name);

DWORD game_proc_id = 0;
HANDLE game_proc = NULL;

int main()
{
	if (!(game_proc_id = get_process_id("osu!.exe"))) {
		printf("error: couldn't find process");
		return EXIT_FAILURE;
	}
		
	printf("found process with id %ld\n", game_proc_id);

	if (!(game_proc = OpenProcess(PROCESS_VM_READ, 0, game_proc_id))) {
		printf("error: failed to get handle to process\n");
		return EXIT_FAILURE;
	}

	printf("got handle to process\n");

	char *name = NULL;
	if (!(get_mapname(&name))) {
		printf("error: failed reading map\n");
		return EXIT_FAILURE;
	}

	printf("%s", name);

	return 0;
}

unsigned long get_process_id(const char *name)
{
	DWORD proc_id = NULL;
	HANDLE proc_list = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 entry = { 0 };
	entry.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(proc_list, &entry)) {
		goto end;
	}

	while (Process32Next(proc_list, &entry)) {
		if (_stricmp((char *)entry.szExeFile, name) == 0) {
			proc_id = entry.th32ProcessID;

			goto end;
		}
	}

end:
	CloseHandle(proc_list);

	return proc_id;
}

int get_mapname(char **name)
{
	const size_t size = 1024;
	unsigned char buf[size];

	const void *map_addr = (void *)MAP_ADDRESS;
	if (!(ReadProcessMemory(game_proc, map_addr, &buf, size, NULL))) {
		printf("error: %d", GetLastError());
		return 0;
	}

	size_t len;
	for (len = 0; len < size; len++) {
		if (buf[len] == ']') {
			len += 2;
			break;
		}
	}

	*name = malloc(len);
	memcpy((void *)(*name), (void *)buf, len);

	(*name)[len - 1] = '\0';

	return len;
}