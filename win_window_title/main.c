#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <tlhelp32.h>

struct handle_data {
	HWND window_handle;
	unsigned long process_id;
};

HWND find_window(unsigned long process_id);
unsigned long get_process_id(const char *name);
__stdcall int enum_windows_callback(HWND handle, void *param);

HWND find_window(unsigned long process_id)
{
	struct handle_data data = { 0, process_id };
	EnumWindows((WNDENUMPROC)enum_windows_callback, (LPARAM)&data);

	return data.window_handle;
}

__stdcall int enum_windows_callback(HWND handle, void *param)
{
	struct handle_data *data = (struct handle_data *)param;

	unsigned long process_id = 0;
	GetWindowThreadProcessId(handle, &process_id);

	if (process_id != data->process_id)
		return 1;

	data->window_handle = handle;
	return 0;
}

unsigned long get_process_id(const char *name)
{
	unsigned long proc_id = 0;
	HANDLE proc_list = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 entry = { 0 };
	entry.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(proc_list, &entry)) {
		goto end;
	}

	while (Process32Next(proc_list, &entry)) {
		if (_stricmp((char *)entry.szExeFile, name) == 0) {
			proc_id = (unsigned long)entry.th32ProcessID;

			goto end;
		}
	}

end:
	CloseHandle(proc_list);

	return proc_id;
}

int main()
{
	HANDLE window = find_window(get_process_id("osu!.exe"));

	const int title_len = 64;
	char *title = malloc(title_len);
	GetWindowText(window, title, title_len);

	printf("%s\n", title);

	return 0;
}
