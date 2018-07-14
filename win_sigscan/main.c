#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <tlhelp32.h>
#include <inttypes.h>

#define READ_SIZE 4096
#define SIGNATURE "\xDB\x5D\xE8\x8B\x45\xE8\xA3"

DWORD get_process_id(char *name);
void *find_address(HANDLE *process, char *signature);

int main()
{
	DWORD game_proc_id;
	if (!(game_proc_id = get_process_id("osu!.exe"))) {
		printf("error: couldn't find process");
		return EXIT_FAILURE;
	}

	printf("found process with id %ld\n", game_proc_id);

	HANDLE game_proc = NULL;
	if (!(game_proc = OpenProcess(PROCESS_VM_READ, 0, game_proc_id))) {
		printf("error: failed to get handle to process\n");
		return EXIT_FAILURE;
	}

	printf("got handle to process\n");

	void *time_address = NULL;
	if (!(time_address = find_address(&game_proc, SIGNATURE))) {
		printf("error: couldn't find address\n");
		return EXIT_FAILURE;
	}

	printf("found time address %#x", time_address);

	return 0;
}

DWORD get_process_id(char *name)
{
	DWORD proc_id;
	HANDLE proc_list = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 entry = {0};
	entry.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(proc_list, &entry)) {
		CloseHandle(proc_list);

		return 0;
	}

	while (Process32Next(proc_list, &entry)) {
		if (strcmp((char *)entry.szExeFile, name) == 0) {
			proc_id = entry.th32ProcessID;
		}
	}

	CloseHandle(proc_list);

	return proc_id;
}

void *find_address(HANDLE *process, char *signature)
{
	bool found = true;
	const size_t read_size = READ_SIZE;
	const size_t sig_size = sizeof(signature);

	size_t read;
	int8_t *chunk;

	for (size_t i = 0; i < INT_MAX; i += read_size) {
		chunk = malloc(read_size);

		if (!(ReadProcessMemory(*process, (void *)i, chunk, read_size,
			&read)))
		{
			printf("error: failed to read chunk at %#x", i);
			printf(" (error: %d, %d read)\n", GetLastError(), read);

			continue;
		}
 
		printf("read chunk at %#x (%d read)\n", i, i, read);

		for (size_t j = 0; j < read_size; j++) {
			found = true;

			for (size_t k = 0; k < sig_size; k++) {
				if (chunk[k + j] != signature[k])
					found = false;
			}

			if (found) {
				return (void *)(i + j);
			}
		}
	}

	return 0;
}