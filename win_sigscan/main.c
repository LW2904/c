#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <tlhelp32.h>
#include <inttypes.h>

#define DEBUG true
#define READ_SIZE 4096
#define SIGNATURE "\xDB\x5D\xE8\x8B\x45\xE8\xA3"

unsigned long get_process_id(const char *name);
void *find_pattern(HANDLE *process, const unsigned char *signature);
inline size_t rpm(HANDLE proc, void *addr, int8_t **chunk, size_t size);

int main()
{
	DWORD proc_id;
	if (!(proc_id = get_process_id("osu!.exe"))) {
		printf("error: couldn't find process");
		return EXIT_FAILURE;
	}
		
	printf("found process with id %ld\n", proc_id);

	HANDLE proc = NULL;
	if (!(proc = OpenProcess(PROCESS_VM_READ, 0, proc_id))) {
		printf("error: failed to get handle to process\n");
		return EXIT_FAILURE;
	}

	printf("got handle to process\n");

	void *addr = find_pattern(proc, SIGNATURE);

	printf("found address: %#x", (unsigned long)addr);

	return 0;
}

void *find_pattern(HANDLE *process, const unsigned char *signature)
{
	bool hit = false;
	const size_t read_size = 4096;
	const size_t signature_size = sizeof(signature);

	unsigned char chunk[read_size];

	// Get chunks of reasonable size from process memory.
	for (size_t i = 0; i < INT_MAX; i += read_size - signature_size) {
		if (rpm(process, (void *)i, &chunk, read_size) != read_size) {
			printf("failed reading %#x\n", (unsigned long)i);

			continue;
		}

		// Iterate over chunk...
		for (size_t j = 0; a < read_size; j++) {
			hit = true;

			printf("%#x ", chunk[j]);

			// ...to check if a part of it matches the signature.
			for (size_t k = 0; k < signature_size && hit; k++) {
				if (signature[k] != chunk[j + k]) {
					hit = false;
				}
			}

			if (hit) {
				return (void *)(i + j);
			}
		}
	}

	return NULL;
}

inline size_t rpm(HANDLE proc, void *addr, int8_t **chunk, size_t size)
{
	size_t read = 0;

	if (!(ReadProcessMemory(proc, addr, chunk, size, &read))) {
		printf("ReadProcessMemory error: %d\n", GetLastError());
	}

	return read;
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