#pragma once
#include "ElementType.h"
#include "Section.h"
#include "FormElement.h"
#include "RadioGroup.h"
#include "TextField.h"
#include "DateElement.h"

using namespace System::Xml;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace std;
using namespace PCRS;


#include "xmlguimaker.h"

using namespace System;
#include "FormElement.h"

ref class PcrsXmlGuiMaker :
public XmlGuiMaker
{
public:

	PcrsXmlGuiMaker(FlowLayoutPanel^ panel)
	{
		this->panel = panel;
		this->Initialize();
	}

	PcrsXmlGuiMaker(void)
	{
		this->Initialize();
	}

	virtual void SetPanel(FlowLayoutPanel^ panel)
	{
		this->panel = panel;
	}

	virtual void MakeFromElementList(System::Collections::Generic::List<FormElement^>^ list) override
	{
		Section^ currentSection;
		for each (FormElement^ element in list)
		{
			if (element->IsType(BreakType))
			{
				if (this->lastControl != nullptr)
				{
					panel->SetFlowBreak(this->lastControl, true);
				}
			}
			else if (element->IsType(SectionType))
			{

				FlowLayoutPanel^ panel = gcnew FlowLayoutPanel();
				panel->BackColor = Color::Beige;
				currentSection = (Section^) element;
				PcrsXmlGuiMaker^ guiMaker = gcnew PcrsXmlGuiMaker(panel);
				guiMaker->MakeFromElementList(currentSection->elements);
				panel->AutoSize = true;
				panel->Padding = System::Windows::Forms::Padding(30, 30, 30, 40);
				panel->Dock = DockStyle::Top;
				//panel->Width = this->panel->Width;
				this->lastControl = panel;
				this->panel->Controls->Add(panel);
				if (this->lastControl != nullptr)
				{
					panel->SetFlowBreak(this->lastControl, true);
				}
			}
			else if (element->IsType(RadioGroupType))
			{
				
				/*TableLayoutPanel^ panel = gcnew TableLayoutPanel();
				panel->AutoSize = true;
				this->panel->Controls->Add(panel);
				RadioGroup^ radioGroup = (RadioGroup^) element;
				radioGroup->container = panel;*/
				RadioGroup^ radioGroup = (RadioGroup^) element;
				if (radioGroup->isGender)
				{
					this->AddGenderField(this->panel, radioGroup);
				}
				else
				{
					this->AddRadioGroup(radioGroup);
				}
			}
			else if (element->IsType(TextFieldType))
			{
				this->AddField(((TextField^) element)->label);
			}
			else if (element->IsType(DateType))
			{
				this->AddDateTimeControl((DateElement^) element);
			}
		} 
	}

	TableLayoutPanel^ CreateNewTablePanel() 
	{
		TableLayoutPanel^ newPanel = gcnew TableLayoutPanel();
		lastControl = newPanel;
		newPanel->AutoSize = true;
		panel->Controls->Add(newPanel);
		return newPanel;
	}

	virtual void AddField(System::String^ text) override
	{
		Panel^ newPanel = CreateNewPanel(panel);
		Label^ label = CreateLabel(text);
			
		newPanel->Controls->Add(label);
		TextBox^ textBox = gcnew TextBox();
		textBox->Font = textBoxFont;
		textBox->Size = textBoxSize;
		PlaceToRight(label, textBox);

		newPanel->Controls->Add(textBox);
		
		newPanel->AutoSize = true;
	}

	virtual Label^ CreateLabel(System::String^ text) override
	{
		Label^ label = gcnew Label();
		label->Font = labelFont;
		label->Text = text;
		label->Size = labelSize;
		label->ForeColor = Color::Gray;
		label->TextAlign = ContentAlignment::TopRight;
		/*if (isSeparateLines)
		{
			label->Size = size;
		}
		else
		{
			label->Size = labelSize;
		}*/
		return label;
	}

	virtual void CreateBreak(bool isForce) override
	{
		if (lastControl != nullptr)
		{
			if (!isSeparateLines || isForce)
			{
				panel->SetFlowBreak(lastControl, true);
			}
		}
	}

	virtual void AddRadioGroup(RadioGroup^ radioGroup) override
	{
		if (radioGroup->isList)
		{
			 AddListRadioGroup(radioGroup);
		}
		else
		{
			 //AddRadioGroup(name, radioGroup);
		}
	}
	
	virtual void AddListRadioGroup(RadioGroup^ radioGroup)
	{
		Panel^ newPanel = CreateNewPanel(panel);
		Label^ label = CreateLabel(radioGroup->label);
		newPanel->Controls->Add(label);
		//newPanel->SetFlowBreak(label, true);
		ComboBox^ listBox = gcnew ComboBox();
		
		listBox->DataSource = radioGroup->strings;
		//listBox->AutoSize = true;
		listBox->Width = 300;
		listBox->Name = radioGroup->id;
		listBox->DropDownWidth = 450;

		/*for (vector<String^>::iterator it = radioGroup.begin(); it != radioGroup.end(); it++)
		{
			listBox->Items->Add(*it);
		}*/
		listBox->Font = textBoxFont;
		//listBox->Size = textBoxSize;
		//listBox->SelectedIndex = 0;
		listBox->DropDownStyle = ComboBoxStyle::DropDownList;
		PlaceToRight(label, listBox);
		newPanel->Controls->Add(listBox);
	}

	virtual void AddRadioGroup(String^ name)
	{
		/*TableLayoutPanel^ newPanel = CreateNewTablePanel();
		Label^ label = CreateLabel(name);
		newPanel->Controls->Add(label);
		int row = 1;

		for (vector<String^>::iterator it = radioGroup.begin(); it != radioGroup.end(); it++)
		{
			RadioButton^ radioButton = gcnew RadioButton();
			radioButton->Text = *it;
			newPanel->Controls->Add(radioButton);
			newPanel->SetRow(radioButton, row);
			row++;
		}
		newPanel->Controls->Add(newPanel);*/
	}

	void AddDateTimeControl(DateElement^ date)
	{
		Panel^ newPanel = CreateNewPanel(panel);
		// Create a new DateTimePicker control and initialize it.
		DateTimePicker^ dateTimePicker = gcnew DateTimePicker;
		dateTimePicker->Name = date->id;

		// Set the MinDate and MaxDate.
		dateTimePicker->MinDate = DateTime(1985,6,20);
		dateTimePicker->MaxDate = DateTime::Today;

		// Set the CustomFormat string.
		//dateTimePicker->CustomFormat = "MMMM dd, yyyy - dddd";
		dateTimePicker->CustomFormat = "yyyy-mm-dd";
		dateTimePicker->Format = DateTimePickerFormat::Custom;

		// Show the CheckBox and display the control as an up-down control.
		dateTimePicker->ShowCheckBox = true;
		dateTimePicker->ShowUpDown = true;
		newPanel->Controls->Add(dateTimePicker);
	}
	
private:
	 System::Drawing::Size labelSize;
	  System::Drawing::Font^ labelFont;

	 System::Drawing::Size textBoxSize;
	 System::Drawing::Font^ textBoxFont;

	 FlowLayoutPanel^ panel;
};

