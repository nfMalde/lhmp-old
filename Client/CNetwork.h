#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <string.h>

typedef void(*callback)(char*);

#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"
#include "RakSleep.h"
#include "TCPInterface.h"
#include <iostream>
#include "../shared/structures.h"

#include "FileListTransfer.h"

struct sHttpRequest
{
	int type;
	char buff[400];
	void* callback;
};
class CNetworkManager
{
private:
	RakNet::RakPeerInterface	*peer;
	RakNet::Packet				*packet;
	RakNet::SocketDescriptor	sd;
	char						CONNECT_IP[100];
	int							CONNECT_PORT;
	char						NickName[100];
	char						m_pServerName[255];

	bool						isConnected;

	RakNet::FileListTransfer*	transferPlugin;
public:
	CNetworkManager();
	~CNetworkManager();
	bool ConnectServer();
	void GetConnectInfo();
	void ProceedLHMP(RakNet::Packet* packet,RakNet::TimeMS timestamp = 0);
	void ValidateIP();
	void Pulse();
	void SendServerMessage(RakNet::BitStream*,PacketPriority ,PacketReliability);
	RakNet::RakPeerInterface* GetPeer();
	char* GetNick();
	RakNet::RakPeerInterface* ReturnPeer();
	bool IsConnected();

	char*	GetServerName();

	void httpRequest(int type, char* url, void* callback);
};
#endif