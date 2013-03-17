#pragma once
using namespace System;
#include "formelement.h"
#include "ElementType.h"
ref class TextField :
public FormElement
{
public:
	TextField(String^ id, String^ label, String^ placeholder)
	{
		this->id = id;
		this->label = label;
		this->placeHolder = placeholder;
		this->isNumber = false;
	}

	virtual bool IsType(PCRS::ElementType type) override
	{
		return type == PCRS::TextFieldType;
	}

	bool isNumber;
	
	String^ value;

	property String^ Value
    {
    public:
        String^ get() { return this->value; }
        void set(String^ v) { this->value = v; }
    }

};

