#include <sstream>

using namespace std;

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
	HttpResponseMessage^ response = task->Result;
	HttpContent^ resultContent = response->Content;
	System::String^ result = resultContent->ReadAsStringAsync()->Result;

	resultCode = System::Convert::ToInt32(result[0])-48;
	return resultCode;
}

int ServerCommunication::SendNewSession(System::String^ token, int reason)
{
	int resultCode = 0;
	HttpClient^ client = gcnew HttpClient();
	HttpRequestMessage^ message = gcnew HttpRequestMessage();
	System::Uri^ server_uri = gcnew System::Uri("http://localhost:9999/signin/");
	StringContent^ content = gcnew System::Net::Http::StringContent("");
	message->Headers->Add("token", token);
	message->Headers->Add("reason_id", System::Convert::ToString(reason));
	message->RequestUri = server_uri;
	message->Content = content;
	message->Method = HttpMethod::Post;
	auto task = client->SendAsync(message);

	task->Wait();
	HttpResponseMessage^ response = task->Result;
	HttpContent^ resultContent = response->Content;
	System::String^ result = resultContent->ReadAsStringAsync()->Result;

	resultCode = System::Convert::ToInt32(result[0])-48;
	return resultCode;
}
