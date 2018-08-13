#ifndef _MEMORY_GUARD_
#define _MEMORY_GUARD_

#include <iostream>
#include <Windows.h>

class Player;

class MemoryManagement 
{ // base class yahurd

public:
	MemoryManagement();
	~MemoryManagement();
	
	bool Open (const char* pp);
	bool Close(				 );
	
	virtual bool	Aimbot	(bool dewei);
	virtual bool	Visuals (bool dewei);
	virtual bool	Bhop	(bool dewei);
	virtual int ReadPosition();

protected:
	int	   ProcessId = NULL;
	HANDLE hProcess  = NULL;
	DWORD  client	 = NULL;
	DWORD  engine	 = NULL;
	bool   off = false;

private:
	bool GetProcessByName(const char* p  );
	int	 GetModuleBase	 (LPCSTR t_module);
	
};

class Player : public MemoryManagement
{
public:
	Player();
	~Player();
	int		GetLocalPlayer();
	int		ReadPosition();
	bool Aimbot  (bool dewei) override;
	bool Visuals (bool dewei) override;
	bool Bhop	 (bool dewei) override;

	
protected: 
	struct m_vecPosition {
		int x, y, z;
	};

	int m_health, m_team, m_Armor;

	bool m_validPlayer, m_isAlive;

private:
	


};


extern MemoryManagement* process;
extern Player* xp;
#endif