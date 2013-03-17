#pragma once
#include "formelement.h"
#include "ElementType.h"
ref class Break :
public FormElement
{
public:

	Break(void)
	{
		this->id = nullptr;
		this->label = nullptr;
	}

	virtual bool IsType(PCRS::ElementType type) override
	{
		return type == PCRS::BreakType;
	}
};

