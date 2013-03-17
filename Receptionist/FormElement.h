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
	//String^ style;
	//String^ type;
	bool isRequired;
	
};

