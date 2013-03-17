#include "ServerCommunication.h"

ServerCommunication::ServerCommunication(void)
{
}

int ServerCommunication::CheckToken(System::String^ token)
{
	int resultCode = 0;
	HttpClient^ client = gcnew HttpClient();
	HttpRequestMessage^ message = gcnew HttpRequestMessage();
	System::Uri^ server_uri = gcnew System::Uri("http://localhost:9999/validate/");
	StringContent^ content = gcnew System::Net::Http::StringContent("");
	message->Headers->Add("token", token);
	message->RequestUri = server_uri;
	message->Content = content;
	message->Method = HttpMethod::Post;
	auto task = client->SendAsync(message);

	task->Wait();
	HttpResponseMessage^ result = task->Result;
	resultCode = (int)result->StatusCode;

	return resultCode;
}

int ServerCommunication::SendNewSession(System::String^ token, int reason)
{
	HttpClient^ client = gcnew HttpClient();
	HttpRequestMessage^ message = gcnew HttpRequestMessage();
	System::Uri^ server_uri = gcnew System::Uri("http://localhost:9999/validate/");
	StringContent^ content = gcnew System::Net::Http::StringContent("");
	message->Headers->Add("token", token);
	message->Headers->Add("reason_id", System::Convert::ToString(reason));
	message->RequestUri = server_uri;
	message->Content = content;
	message->Method = HttpMethod::Post;
	auto task = client->SendAsync(message);

	task->Wait();
	HttpResponseMessage^ result = task->Result;
	resultCode = (int)result->StatusCode;

	return resultCode;
}
