#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <tlhelp32.h>
#include <inttypes.h>

#define TIME_ADDRESS 		0x011E59EC // TimeAddress
#define TIME_ADDRESS_PTR 	0xEC591E01 // P->TimeAddress

unsigned long get_process_id(const char *name);
static inline size_t rpm(HANDLE proc, void *addr, int8_t **chunk, size_t size);

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

	size_t read = 0;
	// int32_t time = 0;
	intptr_t timeaddr = 0;

	ReadProcessMemory(proc, (void *)TIME_ADDRESS_PTR, &timeaddr,
		sizeof(intptr_t), &read);

	printf("read: %d (%#x)\n", read, (unsigned)timeaddr);

	/*ReadProcessMemory(proc, (void *)TIME_ADDRESS, &time,
		sizeof(int32_t), &read);

	printf("read: %d (%d)\n", read, time);*/
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