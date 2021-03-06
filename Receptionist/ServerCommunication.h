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
	String^ GetXmlFile(System::String^ file);
	String^ SubmitUserInfo(Collections::Generic::List<KeyValue^>^ args);
	String^ sendRequest(String^ host, String^ path, Collections::Generic::List<KeyValue^>^ args, String^ result);
private:
	HttpClient^ client;
};