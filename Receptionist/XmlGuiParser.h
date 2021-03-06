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
#include "DateElement.h"
#include "ServerCommunication.h"

ref class XmlGuiParser
{
public:

	XmlGuiParser(void)
	{
		elements = gcnew System::Collections::Generic::List<FormElement^>();
		radioGroups = gcnew System::Collections::Generic::Dictionary<String^, FormElement^>();
		formName = nullptr;
	}

	void Parse(String^ file)
	{
		#if SERVER_SIDE
			ServerCommunication^ comm = gcnew ServerCommunication();
			String^ test = comm->GetXmlFile(file);
			String^ xml = comm->GetXmlFile(file);
			Console::Write(xml);
			Xml::XmlTextReader^ reader = gcnew Xml::XmlTextReader(gcnew IO::StringReader(xml));
		#else
			Xml::XmlTextReader^ reader = gcnew Xml::XmlTextReader("../server_side/client_information_form.xml");
		#endif

		String^ id;
		String^ label;
		String^ elementType;
		String^ style;
		bool isRequired;
		//vector<String^> radioOptions;
		bool isRadioList;
		Section^ currentSection;
		String^ type;
		String^ placeholder;
		String^ required;
		TextField^ textField;
		FormElement^ newElement;
		RadioGroup^ radioGroup;
		DateElement^ dateElement;

		bool isText;
		bool isNumber;
		bool isRadio;
		bool isList;
		bool isGender;
		bool isDate;

		bool isSIN;
		bool isPostalCode;
		bool isProvince;
		bool isTel;
		bool isEmail;
		bool isTextField;

		while (reader->Read()) 
		{
			newElement = nullptr;
			switch (reader->NodeType) 
			{
				case XmlNodeType::Element: // The node is an element.
					id = reader->GetAttribute("id");
					label = reader->GetAttribute("name");
					style = reader->GetAttribute("style");
					placeholder = reader->GetAttribute("placeholder");
					elementType = reader->Name;
					Console::Write("ELEMENT <" + elementType + id);
					Console::WriteLine(">");

					if (elementType == "form")
					{
						if (label != nullptr)
						{
							formName = label;
						}
					}
					else if (elementType == "Section" || elementType == "div")
					{
						currentSection = gcnew Section(id);
						elements->Add(currentSection);
					}
					else if (elementType == "Field" || elementType == "input")
					{
						if (id != nullptr)
						{
							type = reader->GetAttribute("type");
							if (type != nullptr)
							{
									
								isText = type == "text" || type == "string";
								isNumber = type == "number" || type == "integer";
								isRadio = type == "radio";
								isList = type == "list";
								isGender = type == "gender";
								isDate = type == "date";

								isSIN = type == "sin";
								isPostalCode = type == "postalcode";
								isProvince = type =="province";
								isTel = type == "tel";
								isEmail = type == "email";

								isTextField = isText || isNumber || isSIN || isPostalCode || isProvince || isTel || isEmail;

								if (isTextField)
								{
									textField = gcnew TextField(id, label, placeholder);
									textField->SetType(isNumber, isSIN, isPostalCode, isProvince, isTel, isEmail);
									newElement = textField;
								}
								else if (type == "checkbox")
								{
								}
								else if (isRadio || isList || isGender)
								{
									radioGroup = gcnew RadioGroup(id, label, placeholder);
									radioGroup->isGender = isGender;
									radioGroup->isList = isList;
									newElement = radioGroup;
									radioGroups->Add(id, radioGroup);
								}
								else if (isDate)
								{
									dateElement = gcnew DateElement(id, label, placeholder);
									newElement = dateElement;
								}
									
							}
						}
						//Ignoring fields with no ID
					}
					else if (elementType == "RadioGroup")
					{
					}
					else if (elementType == "br")
					{
						newElement = gcnew Break();
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

			if (newElement != nullptr)
			{
				newElement->placeHolder = placeholder;
				if (currentSection != nullptr)
				{
					currentSection->elements->Add(newElement);
				}
				else
				{
					elements->Add(newElement);
				}
			}
		}

		Console::WriteLine("test");
	}

	String^ formName;

	System::Collections::Generic::List<FormElement^>^ elements;

	System::Collections::Generic::Dictionary<String^, FormElement^>^ radioGroups;
};

