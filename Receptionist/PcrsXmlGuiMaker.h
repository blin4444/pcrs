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
				panel->BackColor = Color::White;
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
					this->AddGenderField(radioGroup);
				}
				else
				{
					this->AddRadioGroup(radioGroup);
				}
			}
			else if (element->IsType(TextFieldType))
			{
				this->AddField(((TextField^) element));
			}
			else if (element->IsType(DateType))
			{
				this->AddDateTimeControl((DateElement^) element);
			}
		} 
	}

	virtual Panel^ CreateNewPanel() override
	{
		Panel^ newPanel = gcnew Panel();
		lastControl = newPanel;
		newPanel->AutoSize = true;
		panel->Controls->Add(newPanel);
		return newPanel;
	}

	virtual void AddGenderField(RadioGroup^ radioGroup)
	{
		Panel^ newPanel = CreateNewPanel();
		Label^ label = CreateLabel("Gender");
		newPanel->Controls->Add(label);
		ComboBox^ listBox = gcnew ComboBox();
		listBox->Name = radioGroup->id;
		listBox->AutoSize = true;
		listBox->Items->Add("Unspecified");
		listBox->Items->Add("Male");
		listBox->Items->Add("Female");
		listBox->Font = GetTextBoxFont();
		listBox->Size = GetTextBoxSize();
		listBox->SelectedIndex = 0;
		listBox->DataBindings->Add("SelectedIndex", radioGroup, "Value", false, DataSourceUpdateMode::OnPropertyChanged);
		listBox->DropDownStyle = ComboBoxStyle::DropDownList;
		PlaceToRight(label, listBox);
		newPanel->Controls->Add(listBox);
	}

	TableLayoutPanel^ CreateNewTablePanel() 
	{
		TableLayoutPanel^ newPanel = gcnew TableLayoutPanel();
		lastControl = newPanel;
		newPanel->AutoSize = true;
		panel->Controls->Add(newPanel);
		return newPanel;
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
		Panel^ newPanel = CreateNewPanel();
		Label^ label = CreateLabel(radioGroup->label);
		newPanel->Controls->Add(label);
		//newPanel->SetFlowBreak(label, true);
		ComboBox^ listBox = gcnew ComboBox();

		listBox->DataSource = radioGroup->strings;
		//listBox->AutoSize = true;
		listBox->Width = 300;
		listBox->Name = radioGroup->id;
		listBox->DropDownWidth = 450;
		listBox->DataBindings->Add("SelectedIndex", radioGroup, "Value", false, DataSourceUpdateMode::OnPropertyChanged);

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
		Panel^ newPanel = CreateNewPanel();
		Label^ label = CreateLabel(date->label);
		// Create a new DateTimePicker control and initialize it.
		DateTimePicker^ dateTimePicker = gcnew DateTimePicker;
		dateTimePicker->Name = date->id;
		dateTimePicker->Size = GetTextBoxSize();

		// Set the MinDate and MaxDate.
		dateTimePicker->MinDate = DateTime(1800,1,1);
		dateTimePicker->MaxDate = DateTime::Today;

		// Set the CustomFormat string.
		//dateTimePicker->CustomFormat = "MMMM dd, yyyy - dddd";
		dateTimePicker->CustomFormat = "yyyy-MM-dd";
		dateTimePicker->Format = DateTimePickerFormat::Custom;

		// Show the CheckBox and display the control as an up-down control.
		//dateTimePicker->ShowCheckBox = true;
		//dateTimePicker->ShowUpDown = true;
		newPanel->Controls->Add(label);
		PlaceToRight(label, dateTimePicker);
		newPanel->Controls->Add(dateTimePicker);
	}
	
private:
	 System::Drawing::Size labelSize;
	  System::Drawing::Font^ labelFont;

	 System::Drawing::Size textBoxSize;
	 System::Drawing::Font^ textBoxFont;

	 FlowLayoutPanel^ panel;
};

