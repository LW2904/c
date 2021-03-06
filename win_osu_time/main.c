#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <tlhelp32.h>
#include <inttypes.h>

#define TIME_ADDRESS 0x00A859EC 	// TimeAddress
#define TIME_ADDRESS_PTR 0x0683CBF6 + 1	// P->TimeAddress

#define TIME_PTR_SIGNATURE "\xDB\x5D\xE8\x8B\x45\xE8\xA3"

void *find_address(unsigned char* signature);
unsigned long get_process_id(const char *name);
static inline size_t rpm(void *addr, void *chunk, size_t size);

HANDLE proc;

int main()
{
	DWORD proc_id;
	if (!(proc_id = get_process_id("osu!.exe"))) {
		printf("error: couldn't find process");
		return EXIT_FAILURE;
	}
		
	printf("found process with id %ld\n", proc_id);

	proc = NULL;
	if (!(proc = OpenProcess(PROCESS_VM_READ, 0, proc_id))) {
		printf("error: failed to get handle to process\n");
		return EXIT_FAILURE;
	}

	printf("got handle to process\n");

	void *timeaddr = find_address((unsigned char *)TIME_PTR_SIGNATURE);

	printf("time ptr: %#x\n", timeaddr);

	// size_t read = 0;
	// int32_t time = 0;
	// void *timeaddr = 0;

	// read = rpm((void *)(TIME_ADDRESS_PTR), &timeaddr, sizeof(intptr_t));

	// printf("read: %d (%#x)\n", read, (unsigned)(intptr_t)timeaddr);

	// read = rpm((void *)(intptr_t)(unsigned)(intptr_t)timeaddr, &time,
	// 	sizeof(int32_t));

	// printf("read: %d (%d)\n", read, time);
}

static inline size_t rpm(void *addr, void *chunk, size_t size)
{
	size_t read = 0;

	if (!(ReadProcessMemory(proc, addr, chunk, size, &read))) {
		printf("reading %d at %#x failed: %d\n", size, (intptr_t)chunk,
			GetLastError());
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

void *find_address(unsigned char *signature)
{
	const size_t chunk_size = 4096;
	// Disregard terminating \0.
	const size_t sig_size = sizeof(signature) - 1;

	unsigned char *chunk = malloc(chunk_size);

	for (size_t i = 0; i < INT_MAX; i += chunk_size) {
		size_t read = rpm((void *)(intptr_t)i, &chunk, chunk_size);
	}

	return NULL;
}