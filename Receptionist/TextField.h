#pragma once
using namespace System;
#include "formelement.h"
#include "ElementType.h"
ref class TextField :
public FormElement
{
public:
	TextField(String^ id, String^ label)
	{
		this->id = id;
		this->label = label;
		this->isRequired = false;
		this->isNumber = false;
	}

	virtual bool IsType(PCRS::ElementType type) override
	{
		return type == PCRS::TextFieldType;
	}

	bool isNumber;

};

