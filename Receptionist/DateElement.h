#pragma once
#include "formelement.h"
#include "ElementType.h"
ref class DateElement :
public FormElement
{
public:

	DateElement(String^ id, String^ label, String^ placeholder)
	{
		this->id = id;
		this->label = label;
		this->placeHolder = placeholder;
	}

	virtual bool IsType(PCRS::ElementType type) override
	{
		return type == PCRS::DateType;
	}

	String^ sgDate;
	
	property String^ Value
    {
    public:
		String^ get() { return this->sgDate; }
        void set(String^ v)
		{
			this->sgDate = v;
		}
    }
};

