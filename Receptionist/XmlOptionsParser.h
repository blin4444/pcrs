#pragma once
#include <vector>
#include "FormElement.h"
using namespace System;
using namespace System::Xml;
using namespace std;
//using namespace System::Xml::Serialization;
#include "Section.h"
#include "TextField.h"
#include "RadioGroup.h"
#include "Break.h"
#include "ElementType.h"
#include "ServerCommunication.h"

#define SERVER_SIDE 1

ref class XmlOptionsParser
{
public:

	XmlOptionsParser(System::Collections::Generic::Dictionary<String^, FormElement^>^ radioGroups)
	{
		this->radioGroups = radioGroups;
	}

	void Parse(String^ file)
	{
#if SERVER_SIDE
		ServerCommunication^ comm = gcnew ServerCommunication();
		String^ xml = comm->GetXmlFile(file);
		Console::Write(xml);
		Xml::XmlTextReader^ reader = gcnew Xml::XmlTextReader(gcnew IO::StringReader(xml));
#else
		Xml::XmlTextReader^ reader = gcnew Xml::XmlTextReader("options.xml");
#endif
		String^ elementType;
		String^ sectionId;
		String^ id;
		String^ value;
		String^ type;
		RadioGroup^ radioGroup;


			while (reader->Read()) 
			{

				switch (reader->NodeType) 
				{
					case XmlNodeType::Element: // The node is an element.
						elementType = reader->Name;
						id = reader->GetAttribute("id");
						value = reader->GetAttribute("value");

						if (elementType == "Section" || elementType == "div")
						{
							radioGroup = nullptr;
							sectionId = id;
							FormElement^ element = radioGroups[id];
							if (element->IsType(PCRS::RadioGroupType))
							{
								radioGroup = (RadioGroup^) element;
							}
						}
						else if (elementType == "Item" || elementType == "input")
						{
							if (value != nullptr && radioGroup != nullptr)
							{
								radioGroup->strings->Add(value);
							}
						}
						break;
					case XmlNodeType::Text: //Display the text in each element.
						/*if (elementType == "Radio")
						{
							radioOptions.push_back(reader->Value);
						}*/
						Console::WriteLine ("VALUE" + reader->Value);
						break;
					case XmlNodeType::EndElement: //Display the end of the element.
						/*if (elementType == "RadioGroup")
						{

							radioOptions.clear();
						}*/
						Console::Write("END </" + reader->Name);
						Console::WriteLine(">");
						break;
				}
			}

	}

	System::Collections::Generic::Dictionary<String^, FormElement^>^ radioGroups;
};

