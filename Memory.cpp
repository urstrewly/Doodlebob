#include "Memory.h"
#include <TlHelp32.h>

MemoryManagement::MemoryManagement()
{
}

MemoryManagement::~MemoryManagement()
{

	CloseHandle(hProcess);
	hProcess  = INVALID_HANDLE_VALUE;
	ProcessId = NULL;
}

bool MemoryManagement::GetProcessByName(const char * p)
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (snapshot == INVALID_HANDLE_VALUE)
		return false;

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{

			if (strcmp(entry.szExeFile, p) == 0)
			{
				ProcessId = entry.th32ProcessID;
				
				if (!ProcessId)
					return false;

				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);

				if (hProcess == INVALID_HANDLE_VALUE)
					return false;

				CloseHandle(snapshot);
				return true;
			}
		}
	}

	CloseHandle(snapshot);
	return false;
}

int MemoryManagement::GetModuleBase(LPCSTR t_module)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessId);

	MODULEENTRY32 entry;
	entry.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(snapshot, &entry) == TRUE)
	{
		while (Module32Next(snapshot, &entry) == TRUE)
		{
			
			if (strcmp(entry.szModule, t_module) == 0)
			{
				std::cout << t_module << "-> " << entry.szModule << std::endl;
				return((DWORD)entry.modBaseAddr);
			}
		}
	}

	std::cout << "Unable to find->" << t_module << std::endl;

	CloseHandle(snapshot);
	entry.modBaseAddr = 0;
	return 0;
}

bool MemoryManagement::Open(const char* pp)
{
	if (!GetProcessByName(pp))
		return false;
	
	std::cout << hProcess << std::endl;
	std::cout << ProcessId << std::endl;

	client = GetModuleBase("client_panorama.dll");
	engine = GetModuleBase("engine.dll");

	std::cout << client << " " << engine << std::endl;
	return true;
}

bool MemoryManagement::Close()
{
	CloseHandle(hProcess);
	return true;
}

// Vfunc def - future menu will input 1 or 0 for parameters 
bool MemoryManagement::Aimbot(bool dewei)
{
	if (off == dewei)
		return false;
	
	
}

bool MemoryManagement::Visuals(bool dewei)
{
	if (off == dewei)
		return false;
	

}

bool MemoryManagement::Bhop(bool dewei)
{
	if (off == dewei)
		return false;

	xp->Bhop(dewei);
}

int MemoryManagement::ReadPosition()
{
	return 0;
}

Player::Player()
{
}

Player::~Player()
{
}

// Vfunc override
int Player::GetLocalPlayer()
{
	return 0;
}

int Player::ReadPosition()
{
	// rpm player xyz fill out struct in class

	return 0;
}

bool Player::Aimbot(bool dewei)
{
	if (dewei != true) 
		return false;

	return true;
}

bool Player::Visuals(bool dewei)
{
	if (dewei != true)
		return false;

	return true;
}

bool Player::Bhop(bool dewei)
{
	if (dewei != true)
		return false;

	std::cout << "polymorphism worked" << std::endl;
	return true;
}
