#pragma once
#include "FormElement.h"
#include "RadioGroup.h"
using namespace System;
using namespace System::Xml;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace std;
#include <vector>

ref class XmlGuiMaker abstract 
{
public:

	virtual void Initialize()
	{
		this->InitFontsSizes();
	}

	virtual void InitFontsSizes()
	{
		labelFont = gcnew System::Drawing::Font("Segoe UI", 12);
		labelSize = System::Drawing::Size(120,40);
		textBoxSize = System::Drawing::Size(140,40);
		textBoxFont = gcnew System::Drawing::Font("Segoe UI", 11);
	}

	virtual void MakeFromElementList(System::Collections::Generic::List<FormElement^>^ list) = 0;
	
	virtual void AddField(System::String^ text) = 0;

	Panel^ CreateNewPanel(Panel^ panel)
	{
		Panel^ newPanel = gcnew Panel();
		lastControl = newPanel;
		newPanel->AutoSize = true;
		panel->Controls->Add(newPanel);
		return newPanel;
	}

	virtual void AddGenderField(Panel^ panel, RadioGroup^ radioGroup)
	{
		Panel^ newPanel = CreateNewPanel(panel);
		Label^ label = CreateLabel("Gender");
		newPanel->Controls->Add(label);
		ComboBox^ listBox = gcnew ComboBox();
		listBox->Name = radioGroup->id;
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

	virtual void SetSeparateLines(bool isSeparateLines)
	{
		this->isSeparateLines = isSeparateLines;
	}

	virtual bool GetSeparateLines()
	{
		return this->isSeparateLines;
	}

	virtual void CreateBreak(bool isForce) = 0;

	virtual void PlaceToRight(Control^ left, Control^ right) 
	{
		right->SetBounds(left->Bounds.Width + 10,0, right->Bounds.Width, right->Bounds.Height);
	}

	virtual Label^ CreateLabel(System::String^ text)
	{
		Label^ label = gcnew Label();
		label->Text = text;
		return label;
	}

	virtual void AddRadioGroup(RadioGroup^ radioGroup) = 0;

protected:
	bool isSeparateLines;
	Control^ lastControl;

	System::Drawing::Size textBoxSize;
	System::Drawing::Font^ textBoxFont;
	System::Drawing::Size labelSize;
	  System::Drawing::Font^ labelFont;
};
