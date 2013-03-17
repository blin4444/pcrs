#include "ServerCommunication.h"

ServerCommunication::ServerCommunication(void)
{
	client = gcnew HttpClient();
}

int ServerCommunication::sendRequest(String^ host, String^ path, Collections::Generic::List<KeyValue^>^ args)
{
	int resultCode = 0;
	HttpRequestMessage^ message = gcnew HttpRequestMessage();
	System::Uri^ server_uri = gcnew System::Uri("http://" + host + "/" + path + "/");
	StringContent^ content = gcnew System::Net::Http::StringContent("");
	for each (KeyValue^ arg in args)
	{
		message->Headers->Add(arg->key, arg->value);
	}
	message->RequestUri = server_uri;
	message->Content = content;
	message->Method = HttpMethod::Post;
	auto task = client->SendAsync(message);

	task->Wait();
	HttpResponseMessage^ response = task->Result;
	HttpContent^ resultContent = response->Content;
	System::String^ result = resultContent->ReadAsStringAsync()->Result;
	resultCode = Convert::ToInt32(result[0])-48;

	return resultCode;
}

int ServerCommunication::CheckToken(System::String^ token)
{
	Collections::Generic::List<KeyValue^>^ args = gcnew Collections::Generic::List<KeyValue^>();
	args->Add(gcnew KeyValue("token", token));
	return sendRequest("localhost:9999", "validate", args);
}

int ServerCommunication::SendNewSession(System::String^ token, int reason)
{
	Collections::Generic::List<KeyValue^>^ args = gcnew Collections::Generic::List<KeyValue^>();
	args->Add(gcnew KeyValue("token", token));
	args->Add(gcnew KeyValue("reason_id", System::Convert::ToString(reason)));
	return sendRequest("localhost:9999", "signin", args);
}