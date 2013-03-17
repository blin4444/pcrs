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
#include "DateElement.h"

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
		labelSize = System::Drawing::Size(120,40);
		textBoxSize = System::Drawing::Size(170,40);
		textBoxFont = gcnew System::Drawing::Font("Segoe UI", 11);
	}

	virtual void MakeFromElementList(System::Collections::Generic::List<FormElement^>^ list) = 0;

	virtual Panel^ CreateNewPanel() = 0;

	virtual void AddField(TextField^ textField)
	{
		Panel^ newPanel = CreateNewPanel();
		
		Label^ label = CreateLabel(textField->label);
			
		newPanel->Controls->Add(label);

		TextBoxBase^ textBox;
		bool isMask = textField->textFieldType != PCRS::TextType::Normal;
		if (isMask)
		{
			textBox = gcnew MaskedTextBox();
			HandleMask(textField, (MaskedTextBox^) textBox);
		}
		else
		{
			textBox = gcnew TextBox();
		}
		textBox->DataBindings->Add("Text", textField, "Value", false, DataSourceUpdateMode::OnPropertyChanged);
		textBox->Font = ((XmlGuiMaker^) this)->GetTextBoxFont();
		textBox->Size = ((XmlGuiMaker^) this)->GetTextBoxSize();
		PlaceToRight(label, textBox);
		newPanel->Controls->Add(textBox);
		newPanel->AutoSize = true;
	}

	void HandleMask(TextField^ textField, MaskedTextBox^ maskedTextBox)
	{
		maskedTextBox->ValidatingType = String::typeid;
		maskedTextBox->MaskInputRejected += gcnew System::Windows::Forms::MaskInputRejectedEventHandler(this, &XmlGuiMaker::maskedTextBox_MaskInputRejected);
		maskedTextBox->TypeValidationCompleted += gcnew System::Windows::Forms::TypeValidationEventHandler(this, &XmlGuiMaker::maskedTextBox_MaskInputAccepted);
		//maskedTextBox->Validated += gcnew System::EventHandler(this, &XmlGuiMaker::maskedTextBox_Validated);

		switch (textField->textFieldType)
		{
			case Telephone:
				maskedTextBox->Mask = "(999)-000-0000";
				break;
		}
	}

	System::Void maskedTextBox_MaskInputRejected(System::Object^ sender, System::Windows::Forms::MaskInputRejectedEventArgs^  e) {
		MaskedTextBox^ maskedTextBox = (MaskedTextBox^) sender;
		//maskedTextBox->BackColor = Color::LightPink;
	}

	System::Void maskedTextBox_MaskInputAccepted(System::Object^ sender, System::Windows::Forms::TypeValidationEventArgs^  e) {
		MaskedTextBox^ maskedTextBox = (MaskedTextBox^) sender;
		//maskedTextBox->BackColor = Color::LightGreen;
	}

	System::Void maskedTextBox_Validated(System::Object^ sender, System::EventArgs^ e)
	{
		MaskedTextBox^ maskedTextBox = (MaskedTextBox^) sender;
		//maskedTextBox->BackColor = Color::LightGreen;
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

		listBox->DataBindings->Add("SelectedIndex", radioGroup, "Value", false, DataSourceUpdateMode::OnPropertyChanged);
		listBox->DropDownStyle = ComboBoxStyle::DropDownList;
		PlaceToRight(label, listBox);
		newPanel->Controls->Add(listBox);
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
		dateTimePicker->CustomFormat = "yyyy-MM-dd";
		dateTimePicker->Format = DateTimePickerFormat::Custom;

		dateTimePicker->DataBindings->Add("Text", date, "Value", false, DataSourceUpdateMode::OnPropertyChanged);
		newPanel->Controls->Add(label);
		PlaceToRight(label, dateTimePicker);
		newPanel->Controls->Add(dateTimePicker);
	}

	virtual Label^ CreateLabel(System::String^ text)
	{
		Label^ label = gcnew Label();
		label->Font = ((XmlGuiMaker^) this)->GetLabelFont();
		label->Text = text;
		label->Size =  ((XmlGuiMaker^) this)->GetLabelSize();
		label->ForeColor = Color::Gray;
		label->TextAlign = ContentAlignment::TopLeft;

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
		right->SetBounds(left->Bounds.Width + 5,0, right->Bounds.Width, right->Bounds.Height);
	}

	virtual void PlaceUnder(Control^ top, Control^ bottom) 
	{
		bottom->SetBounds(0, top->Bounds.Height + 5, bottom->Bounds.Width, bottom->Bounds.Height);
	}

	virtual void AddRadioGroup(RadioGroup^ radioGroup)
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
		label->AutoSize = true;
		//label->Dock = DockStyle::Fill;
		newPanel->Controls->Add(label);
		ComboBox^ listBox = gcnew ComboBox();

		listBox->DataSource = radioGroup->strings;
		radioGroup->strings->Add("");
		listBox->Width = 300;
		listBox->Name = radioGroup->id;
		listBox->DropDownWidth = 450;
		
		listBox->DataBindings->Add("SelectedIndex", radioGroup, "Value", false, DataSourceUpdateMode::OnPropertyChanged);
		listBox->Font = textBoxFont;
		listBox->DropDownStyle = ComboBoxStyle::DropDownList;
		PlaceUnder(label, listBox);
		newPanel->Controls->Add(listBox);
	}

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
