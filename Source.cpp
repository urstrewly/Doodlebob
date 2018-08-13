#include <iostream>
#include "Memory.h"

MemoryManagement* process = new MemoryManagement();
Player* xp				  = new Player();

int main()
{

	if (!process->Open("csgo.exe"))
		return -1;
	
	process->Bhop(true);

	int a;
	std::cin >> a;
}