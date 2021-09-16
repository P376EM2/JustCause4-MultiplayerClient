#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
	networkSettings = new NetworkSettings();
	realtimeClient = networkSettings->GetClient()->createRtClient(DEFAULT_PORT);
}

NetworkManager::~NetworkManager()
{
	delete networkSettings;
}

NetworkSettings* NetworkManager::GetNetworkSettings()
{
	return networkSettings;
}

NRtClientPtr NetworkManager::getRealtimeClient()
{
	return realtimeClient;
}

void NetworkManager::Tick()
{
	networkSettings->GetClient()->tick();

	if(realtimeClient) realtimeClient->tick();
}
