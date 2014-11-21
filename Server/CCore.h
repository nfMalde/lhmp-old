#ifndef CCORE_H
#define	CCORE_H

#ifndef _WIN32
typedef unsigned char byte;
#endif

#include "CNetworkManager.h"
#include "CTickManager.h"
#include "CPlayerPool.h"
#include "CVehiclePool.h"
#include "CScripts.h"
#include "CConsole.h"
#include "CGameMode.h"
#include "CTimerPool.h"
#include "CDoorPool.h"
#include "CLog.h"

class CCore
{
private:
	bool				m_bIsRunning;
	CNetworkManager		m_cNetworkManager;
	CTickManager		m_cTickManager;
	CPlayerPool			m_cPlayerPool;
	CVehiclePool		m_cVehiclePool;
	CScripts			m_cScripts;
	CConsole			m_cConsole;
	CGameMode			m_cGameMode;
	CTimerPool			m_cTimerPool;
	CDoorPool			m_cDoorPool;
	CLog				m_cLog;
	char				m_cMapName[200];
	//strPlayer*			m_pPlayers;

public:
	CCore();
	~CCore();
	bool	Init(int,int,std::string,std::string,std::string, int);
	void	Pulse();
	bool	IsRunning();
	void	OnSecondElapsed();
	//strPlayer* GetPlayers();
	CNetworkManager*	GetNetworkManager();
	CTickManager*		GetTickManager();
	CPlayerPool*		GetPlayerPool();
	CVehiclePool*		GetVehiclePool();
	CScripts*			GetScripts();
	CConsole*			GetConsole();
	CGameMode*			GetGameMode();
	CTimerPool*			GetTimerPool();
	CDoorPool*			GetDoorPool();
	CLog*				GetLog();

	void				SetDefaultMap(char*);
	char*				GetDefaultMap();
};
#endif