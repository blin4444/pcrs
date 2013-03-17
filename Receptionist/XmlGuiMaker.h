#pragma once
#include "FormElement.h"
#include "RadioGroup.h"
using namespace System;
using namespace System::Xml;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace std;
#include <vector>
#include "TextField.h"

ref class XmlGuiMaker abstract 
{
public:

	virtual void Initialize()
	{
		InitFontsSizes();
	}

	virtual void InitFontsSizes()
	{
		labelFont = gcnew System::Drawing::Font("Segoe UI", 12);
		labelSize = System::Drawing::Size(120, 40);
		textBoxSize = System::Drawing::Size(140, 40);
		textBoxFont = gcnew System::Drawing::Font("Segoe UI", 11);
	}

	virtual void MakeFromElementList(System::Collections::Generic::List<FormElement^>^ list) = 0;

	virtual Panel^ CreateNewPanel() = 0;

	virtual void AddField(TextField^ textField)
	{
		Panel^ newPanel = CreateNewPanel();
		Label^ label = CreateLabel(textField->label);
			
		newPanel->Controls->Add(label);
		TextBox^ textBox = gcnew TextBox();
		textBox->DataBindings->Add("Text", textField, "Value", false, DataSourceUpdateMode::OnPropertyChanged);
		textBox->Font = ((XmlGuiMaker^) this)->GetTextBoxFont();
		textBox->Size = ((XmlGuiMaker^) this)->GetTextBoxSize();
		PlaceToRight(label, textBox);

		newPanel->Controls->Add(textBox);
		
		newPanel->AutoSize = true;
	}

	virtual Label^ CreateLabel(System::String^ text)
	{
		Label^ label = gcnew Label();
		label->Font = ((XmlGuiMaker^) this)->GetLabelFont();
		label->Text = text;
		label->Size =  ((XmlGuiMaker^) this)->GetLabelSize();
		label->ForeColor = Color::Gray;
		label->TextAlign = ContentAlignment::TopRight;

		return label;
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

	/*virtual Label^ CreateLabel(System::String^ text)
	{
		Label^ label = gcnew Label();
		label->Text = text;
		return label;
	}*/

	virtual void AddRadioGroup(RadioGroup^ radioGroup) = 0;

	System::Drawing::Size GetTextBoxSize()
	{
		return textBoxSize;
	}

	System::Drawing::Size GetLabelSize()
	{
		return labelSize;
	}

	System::Drawing::Font^ GetTextBoxFont()
	{
		return textBoxFont;
	}

	System::Drawing::Font^ GetLabelFont()
	{
		return labelFont;
	}	

protected:
	bool isSeparateLines;
	Control^ lastControl;

private:
	System::Drawing::Size textBoxSize;
	System::Drawing::Font^ textBoxFont;
	System::Drawing::Size labelSize;
	System::Drawing::Font^ labelFont;
};
