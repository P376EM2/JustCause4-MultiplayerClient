#include "NetworkSettings.h"

NetworkSettings::NetworkSettings()
{
	parameters.serverKey = "defaultkey";
	parameters.host = "127.0.0.1";
	parameters.port = DEFAULT_PORT;
	client = createDefaultClient(parameters);
}

NetworkSettings::~NetworkSettings()
{
	
}

NClientPtr NetworkSettings::GetClient()
{
	return client;
}

NClientParameters NetworkSettings::GetParameters()
{
	return parameters;
}
