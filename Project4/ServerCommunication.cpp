#include "ServerCommunication.h"

ServerCommunication::ServerCommunication(void)
{
}

int ServerCommunication::CheckToken(System::String^ token)
{
	HttpClient^ client = gcnew HttpClient();
	HttpRequestMessage^ message = gcnew HttpRequestMessage();
	System::Uri^ server_uri = gcnew System::Uri("http://localhost:9999/validate/");
	StringContent^ content = gcnew System::Net::Http::StringContent("");
	message->Headers->Add("token", token);
	message->RequestUri = server_uri;
	message->Content = content;
	message->Method = HttpMethod::Post;
	client->SendAsync(message);
	

	return 0;
}

int ServerCommunication::SendNewSession(System::String^, int reason)
{
	return 0;
}
