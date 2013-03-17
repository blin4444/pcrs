#pragma once
#include "formelement.h"
#include "ElementType.h"


ref class Section :
public FormElement
{
public:

	Section(String^ tableId)
	{
		this->id = tableId;
		this->label = nullptr;
		elements = gcnew System::Collections::Generic::List<FormElement^>();
	}

	virtual bool IsType(PCRS::ElementType type) override
	{
		return type == PCRS::SectionType;
	}

	System::Collections::Generic::List<FormElement^>^ elements;
};

