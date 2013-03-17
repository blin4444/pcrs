#pragma once
#include "ElementType.h"
using namespace System;
using namespace System::Xml;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace PCRS;


ref class FormElement abstract
{
public:

	virtual bool IsType(PCRS::ElementType type) = 0;

	String^ id;
	String^ label; 
	bool isRequired;
	String^ placeHolder;
	String^ value;

	property String^ Value
    {
    public:
        String^ get() { return this->value; }
        void set(String^ v) { this->value = v; }
    }
};

