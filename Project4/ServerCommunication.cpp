#include "ServerCommunication.h"

ServerCommunication::ServerCommunication(void)
{
	client = gcnew HttpClient();
}

int ServerCommunication::sendRequest(String^ host, String^ path, Collections::Generic::List<String^[]>^ args)
{
	int resultCode = 0;
	HttpRequestMessage^ message = gcnew HttpRequestMessage();
	System::Uri^ server_uri = gcnew System::Uri("http://" + host + "/" path);
	StringContent^ content = gcnew System::Net::Http::StringContent("");
	for each (String^[] arg in args)
	{
		message->Headers->Add(arg[0], arg[1]);
	}
	message->RequestUri = server_uri;
	message->Content = content;
	message->Method = HttpMethod::Post;
	auto task = client->SendAsync(message);

	task->Wait();
	HttpResponseMessage^ response = task->Result;
	HttpContent^ resultContent = response->Content;
	System::String^ result = resultContent->ReadAsStringAsync()->Result;

	return resultCode;
}

int ServerCommunication::CheckToken(System::String^ token)
{
	Collections::Generic::List<String^[]>^ args = new Collections::Generic::List<String^[]>()
	args.add({"token", token)});
	return sendRequest("localhost:9999", "validate", args);
}

int ServerCommunication::SendNewSession(System::String^ token, int reason)
{
	Collections::Generic::List<String^[]>^ args = new Collections::Generic::List<String^[]>()
	args.add({"token", token});
	args.add(reason_id", System::Convert::ToString(reason));
	return sendRequest("localhost:9999", "validate", args);
}
