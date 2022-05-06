#include <windows.h>

typedef NTSTATUS(NTAPI* NtSuspendProcess)(IN HANDLE ProcessHandle);

static NtSuspendProcess pfnNtSuspendProcess = (NtSuspendProcess)GetProcAddress(
	GetModuleHandle(L"ntdll"), "NtSuspendProcess");

static inline NTSTATUS SuspendProcess(DWORD pid)
{
	HANDLE processHandle = OpenProcess(PROCESS_SUSPEND_RESUME, FALSE, pid);
	NTSTATUS status = pfnNtSuspendProcess(processHandle);
	CloseHandle(processHandle);
	return status;
}

int main(int argc, char *argv[])
{
	if (argc == 2) {
		DWORD pid = atoi(argv[1]);
		return SuspendProcess(pid);
	}
}