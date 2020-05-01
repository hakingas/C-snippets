// Program enumerates processes and lists it's full path.
//

#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <processthreadsapi.h>
#include <handleapi.h>
#include <psapi.h>

using namespace std;

int main()
{
	DWORD pid = 0;
	/* Create toolhelp snapshot */
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 process;
	ZeroMemory(&process, sizeof(process));
	process.dwSize = sizeof(process);

	/* Walkthrough all processes */
	if (Process32First(snapshot, &process)) {
		while (Process32Next(snapshot, &process))
		{
			/* compare process name to the name given as a parameter
			 * to this function */
			//cout << "Process name: " << process.szExeFile << " and id: " << process.th32ProcessID << endl;
			pid = process.th32ProcessID;
			wcout << "Process name: " << process.szExeFile << endl;
			if (pid != 0) {
				DWORD ProcessCount;
				DWORD cbNeeded;
				DWORD ProcessId[1024] = {0};

				EnumProcesses(ProcessId, sizeof(ProcessId), &cbNeeded);
				ProcessCount = cbNeeded / sizeof(DWORD);

				HMODULE hModule;
				TCHAR    filename[MAX_PATH] = {0};

				HANDLE prochandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);


				if (prochandle)
				{
					BOOL modulehandle = EnumProcessModules(prochandle, &hModule, sizeof(hModule), &cbNeeded);
					DWORD modulename = GetModuleFileNameEx(prochandle, hModule, filename, MAX_PATH);
					if (filename[0] != '\0') {
						wcout << "\tModulefilename: " << filename << endl;
					}
				}
			}
		}
	}
	CloseHandle(snapshot);
	//CloseHandle(snapshot);


	// Process not found if it gets here

    cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
