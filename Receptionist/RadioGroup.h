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
		this->strings = gcnew System::ComponentModel::BindingList<String^>();
		this->isGender = false;
	}

	virtual bool IsType(PCRS::ElementType type) override
	{
		return type == PCRS::RadioGroupType;
	}

	bool isList;
	bool isGender;
	/*System::Windows::Forms::TableLayoutPanel^ container;
	System::Windows::Forms::ComboBox^ comboBox;*/

	System::ComponentModel::BindingList<String^>^ strings;
};

