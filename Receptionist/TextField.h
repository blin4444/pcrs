#pragma once
using namespace System;
#include "formelement.h"
#include "ElementType.h"
#include "TextType.h"
using namespace PCRS;

ref class TextField :
public FormElement
{
public:
	TextField(String^ id, String^ label, String^ placeholder)
	{
		this->id = id;
		this->label = label;
		this->placeHolder = placeholder;
		this->textFieldType = TextType::Normal;
	}

	virtual bool IsType(PCRS::ElementType type) override
	{
		return type == PCRS::TextFieldType;
	}

	void SetType(bool isNumber, bool isSIN,
		bool isPostalCode,
		bool isProvince,
		bool isTel,
		bool isEmail)
	{
		if (isNumber)
		{
			this->textFieldType = TextType::Number;
		} 
		else if (isSIN)
		{
			this->textFieldType = TextType::SIN;
		}
		else if (isPostalCode)
		{
			this->textFieldType = TextType::PostalCode;
		}
		else if (isProvince)
		{
			this->textFieldType = TextType::PostalCode;
		}
		else if (isTel)
		{
			this->textFieldType = TextType::Telephone;
		}
		else if (isEmail)
		{
			this->textFieldType = TextType::Email;
		}
	}

	PCRS::TextType textFieldType;
	
	String^ value;

	property String^ Value
    {
    public:
        String^ get() { return this->value; }
        void set(String^ v) { this->value = v; }
    }

};

