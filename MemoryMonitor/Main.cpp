#include <iostream>
#include <windows.h>
#include <Psapi.h>
#include <string.h>
#include <tchar.h>
#include <stdio.h>

void PrintProcessAndId(DWORD processID);
void PrintProcessAndId(DWORD processID);

int main()
{
	MEMORYSTATUSEX memory_info;
	memory_info.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memory_info);
	DWORDLONG total_virtual_memory = memory_info.ullTotalPageFile;
	DWORDLONG total_used_memory = memory_info.ullTotalPageFile - memory_info.ullAvailPageFile;
	std::cout << total_used_memory/1024/1024 << " MB";
	DWORD aProcess[1024], cbNeeded, cProcesses;
	unsigned int i;

	if (!EnumProcesses(aProcess, sizeof(aProcess), &cbNeeded))
	{
		return 1;
	}

	cProcesses  = cbNeeded / sizeof(DWORD);

	for (i = 0; i < cProcesses; i++)
	{
		if (aProcess[i] != 0)
		{
			PrintProcessAndId(aProcess[i]);
		}
		
	}
	std::cin.get();
	return 0;

}


void PrintProcessAndId(DWORD processID)
{
	PROCESS_MEMORY_COUNTERS pmc; 
	printf("\nProcess ID: %u\n", processID);

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

	if (NULL == hProcess)
	{
		return;
	}

	if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
	{
		printf("\t%u MB's\n", pmc.WorkingSetSize/1000000);
		
	}

}


