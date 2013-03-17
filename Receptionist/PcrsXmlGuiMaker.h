#pragma once
using namespace System::Xml;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace std;

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

	void MakeFromElementList(System::Collections::Generic::List<FormElement^>^ list)
	{
		for each (FormElement^ element in list)
		{
			
		}
	}

	void Initialize()
	{
		labelFont = gcnew System::Drawing::Font("Segoe UI", 12);
		labelSize = System::Drawing::Size(120,40);
		textBoxSize = System::Drawing::Size(130,40);
		textBoxFont = gcnew System::Drawing::Font("Segoe UI", 11);
	}

	Panel^ CreateNewPanel()
	{
		Panel^ newPanel = gcnew Panel();
		lastControl = newPanel;
		newPanel->AutoSize = true;
		panel->Controls->Add(newPanel);
		return newPanel;
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
		Panel^ newPanel = CreateNewPanel();
		Label^ label = CreateLabel(text);
			
		newPanel->Controls->Add(label);
		TextBox^ textBox = gcnew TextBox();
		textBox->Font = textBoxFont;
		textBox->Size = textBoxSize;
		PlaceToRight(label, textBox);

		newPanel->Controls->Add(textBox);
		
		newPanel->AutoSize = true;
	}

	virtual void AddGenderField() override
	{
		Panel^ newPanel = CreateNewPanel();
		Label^ label = CreateLabel("Gender");
		newPanel->Controls->Add(label);
		ComboBox^ listBox = gcnew ComboBox();
		listBox->Items->Add("Unspecified");
		listBox->Items->Add("Male");
		listBox->Items->Add("Female");
		listBox->Font = textBoxFont;
		listBox->Size = textBoxSize;
		listBox->SelectedIndex = 0;
		listBox->DropDownStyle = ComboBoxStyle::DropDownList;
		PlaceToRight(label, listBox);
		newPanel->Controls->Add(listBox);
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

	/*virtual void AddRadioGroup(String^ name, vector<String^>& radioGroup, bool isList) override
	{
		if (isList)
		{
			 AddListRadioGroup(name, radioGroup);
		}
		else
		{
			 AddRadioGroup(name, radioGroup);
		}
	}
	*/
	/*virtual void AddListRadioGroup(String^ name, vector<String^>& radioGroup)
	{
		/*Panel^ newPanel = CreateNewPanel();
		Label^ label = CreateLabel(name);
		newPanel->Controls->Add(label);
		//newPanel->SetFlowBreak(label, true);
		ComboBox^ listBox = gcnew ComboBox();
		
		for (vector<String^>::iterator it = radioGroup.begin(); it != radioGroup.end(); it++)
		{
			listBox->Items->Add(*it);
		}
		listBox->Font = textBoxFont;
		listBox->Size = textBoxSize;
		listBox->SelectedIndex = 0;
		listBox->DropDownStyle = ComboBoxStyle::DropDownList;
		PlaceToRight(label, listBox);
		newPanel->Controls->Add(listBox);
	}*/

	/*virtual void AddRadioGroup(String^ name, vector<String^>& radioGroup)
	{
		TableLayoutPanel^ newPanel = CreateNewTablePanel();
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
		newPanel->Controls->Add(newPanel);
	}*/
	
private:
	 System::Drawing::Size labelSize;
	  System::Drawing::Font^ labelFont;

	 System::Drawing::Size textBoxSize;
	 System::Drawing::Font^ textBoxFont;

	 FlowLayoutPanel^ panel;
};

