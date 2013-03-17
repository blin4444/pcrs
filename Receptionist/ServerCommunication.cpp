#include "ServerCommunication.h"

ServerCommunication::ServerCommunication(void)
{
	client = gcnew HttpClient();
}

String^ ServerCommunication::sendRequest(String^ host, String^ path, Collections::Generic::List<KeyValue^>^ args, String^ result)
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
	result = resultContent->ReadAsStringAsync()->Result;

	return result;
}

String^ ServerCommunication::GetXmlFile(System::String^ file)
{
	Collections::Generic::List<KeyValue^>^ args = gcnew Collections::Generic::List<KeyValue^>();
	args->Add(gcnew KeyValue("file", file));
	String^ result;
	result = sendRequest("localhost:9999", "getxml", args, result);
	return result;
}

int ServerCommunication::GetCodeFromResult(String^ result)
{
	return Convert::ToInt32(result[0])-48;
}

int ServerCommunication::SubmitUserInfo(Collections::Generic::List<KeyValue^>^ args)
{
	String^ result;
	result = sendRequest("localhost:9999", "register", args, result);
	return GetCodeFromResult(result);
}