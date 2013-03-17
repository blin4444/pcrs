#pragma once

using namespace System;
using namespace System::Net::Http;

ref class KeyValue {
	public:
		KeyValue(String^ key, String^ value)
		{
			this->key = key;
			this->value = value;
		}
		String^ key;
		String^ value;
};

ref class ServerCommunication
{
public:
	ServerCommunication(void);
	int CheckToken(System::String^ token);
	int SendNewSession(System::String^, int reason);
	int sendRequest(String^ host, String^ path, Collections::Generic::List<KeyValue^>^ args);
private:
	HttpClient^ client;
};

