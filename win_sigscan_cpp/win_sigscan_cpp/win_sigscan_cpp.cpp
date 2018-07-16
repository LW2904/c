#include "stdafx.h"

#include <stdbool.h>
#include <tlhelp32.h>
#include <inttypes.h>

#define READ_SIZE 4096
#define SIGNATURE "\xDB\x5D\xE8\x8B\x45\xE8\xA3"

DWORD find_time_address(HANDLE *process);
DWORD get_process_id(const wchar_t *name);
DWORD find_pattern(HANDLE *process, const unsigned char *signature);

int main()
{
	DWORD game_proc_id;
	if (!(game_proc_id = get_process_id(L"osu!.exe"))) {
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

	DWORD time_address = NULL;
	if (!(time_address = find_time_address(&game_proc))) {
		printf("error: couldn't get address\n");
		return EXIT_FAILURE;
	}

	printf("%#x\n", time_address);

	return 0;
}

DWORD get_process_id(const wchar_t *name)
{
	// store process ID in here to return later.
	DWORD process_id = NULL;

	// iterate process list for "osu!.exe"
	HANDLE process_list = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	PROCESSENTRY32 entry = { 0 };
	entry.dwSize = sizeof PROCESSENTRY32;

	if (Process32First(process_list, &entry)) {
		while (Process32Next(process_list, &entry)) {
			if (_wcsicmp(entry.szExeFile, name) == 0) {
				process_id = entry.th32ProcessID;
			}
		}
	}

	CloseHandle(process_list);

	return process_id;
}

DWORD find_pattern(HANDLE *process, const unsigned char *signature)
{
	const size_t signature_size = sizeof(signature);
	const size_t read_size = 4096;
	bool hit = false;

	unsigned char chunk[read_size];

	for (size_t i = 0; i < INT_MAX; i += read_size - signature_size) {
		if (!ReadProcessMemory(*process, LPCVOID(i), &chunk, read_size, NULL)) {
			continue;
		}

		for (size_t a = 0; a < read_size; a++) {
			hit = true;

			for (size_t j = 0; j < signature_size && hit; j++) {
				if (chunk[a + j] != signature[j]) {
					hit = false;
				}
			}

			if (hit) {
				return (i + a);
			}
		}
	}

	return NULL;
}

DWORD find_time_address(HANDLE *process)
{
	DWORD time_address = NULL;
	DWORD time_address_ptr = find_pattern(process, (PBYTE)SIGNATURE) + sizeof(SIGNATURE) - 1;

	if (!ReadProcessMemory(*process, (LPCVOID)time_address_ptr, &time_address, sizeof(DWORD), NULL)) {
		return NULL;
	}

	return time_address;
}