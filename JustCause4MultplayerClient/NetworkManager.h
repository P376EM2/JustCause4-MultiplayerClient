#pragma once

#include "Singleton.h"
#include "NetworkIncludes.h"

class NetworkManager : public Singleton<NetworkManager>
{
public:
	NetworkManager();
	~NetworkManager();
	NetworkSettings* GetNetworkSettings();
	NRtClientPtr getRealtimeClient();

	void Tick();
private:
	NetworkSettings* networkSettings;

protected:
	NRtClientPtr realtimeClient;
};

