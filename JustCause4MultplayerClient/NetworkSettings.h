#pragma once
#include "nakama-cpp/ClientFactory.h"

using namespace Nakama;

class NetworkSettings
{
	public:
	NetworkSettings();
	~NetworkSettings();

	NClientPtr GetClient();
	NClientParameters GetParameters();
private:

protected:
	NClientParameters parameters;
	NClientPtr client;
};