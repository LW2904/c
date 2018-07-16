#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <tlhelp32.h>
#include <inttypes.h>

#define READ_SIZE 4096
#define SIGNATURE "\xDB\x5D\xE8\x8B\x45\xE8\xA3"

int get_process_id(const char *name);

int main()
{

}

int get_process_id(const char *name)
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