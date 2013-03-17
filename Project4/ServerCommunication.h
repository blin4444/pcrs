#pragma once

using namespace System::Net::Http;

ref class ServerCommunication
{
public:
	ServerCommunication(void);
	int CheckToken(System::String^ token);
	int SendNewSession(System::String^, int reason);
private:
	//
};

