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
		this->strings->Add("Nothing available");
		this->isGender = false;
		this->index = 0;
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

	int index;

	property int Value
    {
    public:
		int get() { return this->index; }
        void set(int v)
		{
			this->index = v;
		}
    }
};

