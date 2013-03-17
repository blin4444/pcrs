#pragma once
using namespace System::Xml;
using namespace System::Drawing;
using namespace System::Windows::Forms;

#include "xmlguimaker.h"

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

	void Initialize()
	{
		labelFont = gcnew System::Drawing::Font("Segoe UI", 9);
		labelSize = System::Drawing::Size(90,30);
	}

	Panel^ CreateNewPanel()
	{
		Panel^ newPanel = gcnew Panel();
		lastControl = newPanel;
		newPanel->AutoSize = true;
		panel->Controls->Add(newPanel);
		return newPanel;
	}

	virtual void AddField(System::String^ text) override
	{
		Panel^ newPanel = CreateNewPanel();
		System::Drawing::Font^ textFont = gcnew System::Drawing::Font("Arial", 12);
		
		System::Drawing::Size size = System::Drawing::Size(200,40);

		Label^ label = CreateLabel(text);
			
		newPanel->Controls->Add(label);
		TextBox^ textBox = gcnew TextBox();
		textBox->Font = textFont;
		textBox->Size = size;
		PlaceToRight(label, textBox);

		newPanel->Controls->Add(textBox);
		
		newPanel->AutoSize = true;
	}

	virtual void AddGenderField() override
	{
		Panel^ newPanel = CreateNewPanel();
		newPanel->BackColor = Color::Beige;
		Label^ label = CreateLabel("Gender");
		newPanel->Controls->Add(label);
		ComboBox^ listBox = gcnew ComboBox();
		listBox->Items->Add("Unspecified");
		listBox->Items->Add("Male");
		listBox->Items->Add("Female");
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
		label->TextAlign = ContentAlignment::MiddleRight;
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

private:
	 System::Drawing::Size labelSize;
	 System::Drawing::Font^ labelFont;

	 FlowLayoutPanel^ panel;
};

