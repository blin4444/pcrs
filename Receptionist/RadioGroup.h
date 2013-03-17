#pragma once
#include "formelement.h"
#include "ElementType.h"
ref class RadioGroup :
public FormElement
{
public:
	RadioGroup(String^ id, String^ label)
	{
		this->id = id;
		this->label = label;
		this->isRequired = false;
		this->isList = false;
	}

	virtual bool IsType(PCRS::ElementType type) override
	{
		return type == PCRS::RadioGroupType;
	}

	bool isList;
	System::Windows::Forms::ContainerControl^ container;
};

