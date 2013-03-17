#pragma once

using namespace System;

ref class ServerCommunication
{
public:
	ServerCommunication(void);
	int CheckToken(System::String^ token);
	int SendNewSession(System::String^, int reason);
private:
	HttpClient^ client;
};

