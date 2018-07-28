#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <tlhelp32.h>
#include <inttypes.h>

#define READ_SIZE 4096
#define SIGNATURE "\xDB\x5D\xE8\x8B\x45\xE8\xA3"

void *find_time_address();
unsigned long get_process_id(const char *name);
void *find_pattern(HANDLE process, unsigned char pattern[]);

HANDLE game_proc;

int main()
{
	DWORD proc_id;
	if (!(proc_id = get_process_id("osu!.exe"))) {
		printf("error: couldn't find process\n");
		return EXIT_FAILURE;
	}

	printf("found process with id %ld\n", proc_id);

	if (!(game_proc = OpenProcess(PROCESS_VM_READ, 0, proc_id))) {
		printf("error: failed to get handle to process\n");
		return EXIT_FAILURE;
	}

	printf("got handle to process\n");

	void *time_address = NULL;
	if (!(time_address = find_time_address())) {
		printf("error: couldn't find time address\n");
		return EXIT_FAILURE;
	}

	printf("found time address: %#x\n", (unsigned)(intptr_t)time_address);

	return 0;
}

unsigned long get_process_id(const char *name)
{
	DWORD proc_id = 0;
	HANDLE proc_list = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 entry = { 0 };
	entry.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(proc_list, &entry)) {
		goto end;
	}

	while (Process32Next(proc_list, &entry)) {
		if (strcmp((char *)entry.szExeFile, name) == 0) {
			proc_id = entry.th32ProcessID;

			goto end;
		}
	}

end:
	CloseHandle(proc_list);

	return proc_id;
}

void *find_pattern(HANDLE process, unsigned char pattern[])
{
	bool hit = false;
	const size_t read_size = 4096;
	const size_t signature_size = 4;

	unsigned char chunk[READ_SIZE];

	for (size_t i = 0; i < INT_MAX; i += read_size - signature_size) {
		ReadProcessMemory(process, (void *)i, &chunk, read_size, NULL);

		for (size_t a = 0; a < read_size; a++) {
			hit = true;

			for (size_t j = 0; j < signature_size && hit; j++) {
				if (chunk[a + j] != pattern[j]) {
					hit = false;
				}
			}

			if (hit) {
				return (void *)(i + a + sizeof(SIGNATURE) - 1);
			}
		}
	}

	return NULL;
}

void *find_time_address()
{
	void *time_address = NULL;
	void *time_ptr = find_pattern(game_proc, (unsigned char *)(SIGNATURE));

	printf("time pointer at %#x\n", (unsigned)(intptr_t)time_ptr);

	if (!ReadProcessMemory(game_proc, time_ptr, &time_address, sizeof(DWORD), NULL)) {
		return NULL;
	}

	return time_address;
}
