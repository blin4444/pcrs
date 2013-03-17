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

ref class XmlGuiParser
{
public:

	XmlGuiParser(void)
	{
		elements = gcnew System::Collections::Generic::List<FormElement^>();
		radioGroups = gcnew System::Collections::Generic::Dictionary<String^, FormElement^>();
	}

	void Parse(String^ file)
	{
		Xml::XmlTextReader^ reader = gcnew Xml::XmlTextReader(file);

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

		while (reader->Read()) 
		{
			newElement = nullptr;
			switch (reader->NodeType) 
			{
				case XmlNodeType::Element: // The node is an element.
					id = reader->GetAttribute("id");
					label = reader->GetAttribute("name");
					style = reader->GetAttribute("style");
					required = reader->GetAttribute("required");
					isRequired = (required != nullptr && required == "true");
					placeholder = reader->GetAttribute("placeholder");
					elementType = reader->Name;
					Console::Write("ELEMENT <" + elementType + id);
					Console::WriteLine(">");
					if (elementType == "Section" || elementType == "div")
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
									

								bool isText = type == "text" || type == "string";
								bool isNumber = type == "number" || type == "integer";
								bool isRadio = type == "radio";
								bool isList = type == "list";
								bool isGender = type == "gender";
								bool isDate = type == "date";
								if (isText || isNumber)
								{
									textField = gcnew TextField(id, label);
									textField->isNumber = isNumber;
									newElement = textField;
								}
								else if (type == "checkbox")
								{
								}
								else if (isRadio || isList || isGender)
								{
									radioGroup = gcnew RadioGroup(id, label);
									radioGroup->isGender = isGender;
									radioGroup->isList = isList;
									newElement = radioGroup;
									radioGroups->Add(id, radioGroup);
								}
								else if (isDate)
								{
									dateElement = gcnew DateElement(id, label);
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

	System::Collections::Generic::List<FormElement^>^ elements;

	System::Collections::Generic::Dictionary<String^, FormElement^>^ radioGroups;
};

