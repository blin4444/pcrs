#pragma once
using namespace System;

#include "RadioGroup.h"

[XmlRoot("form")]
ref class Document
{
public:

	Document(void)
	{
	}

	
private:
		[XmlElement("Div")]
		System::Collections::Generic::List<RadioGroup^> div;
};

