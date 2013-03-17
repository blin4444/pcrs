#pragma once
#include "formelement.h"
#include "ElementType.h"
ref class DateElement :
public FormElement
{
public:

	DateElement(String^ id, String^ label)
	{
		this->id = id;
		this->label = label;
		this->isRequired = false;
	}

	virtual bool IsType(PCRS::ElementType type) override
	{
		return type == PCRS::DateType;
	}

};

