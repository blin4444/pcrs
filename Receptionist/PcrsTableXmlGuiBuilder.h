#pragma once
using namespace System::Xml;
using namespace System::Drawing;
using namespace System::Windows::Forms;

#include "pcrsxmlguibuilder.h"
ref class PcrsTableXmlGuiBuilder :
public PcrsXmlGuiBuilder
{
public:

	PcrsTableXmlGuiBuilder(TableLayoutPanel^ panel)
	{
		this->panel = panel;
		this->currentCol = 0;
		this->currentRow = 0;
	}

	PcrsTableXmlGuiBuilder(void)
	{
	}

	virtual void AddField(System::String^ text) override
	{
		using namespace System::Drawing;
		System::Drawing::Font^ textFont = gcnew System::Drawing::Font("Arial", 24);
		System::Drawing::Font^ labelFont = gcnew System::Drawing::Font("Segoe UI", 24);
		System::Drawing::Size size = System::Drawing::Size(400,40);
		Label^ label = gcnew Label();
		//label->Size = size;
		label->AutoSize = true;
		label->Text = text;
		label->Font = labelFont;
			
		panel->Controls->Add(label);
		panel->SetRow(label, currentRow);
		panel->SetColumn(label, currentCol++);
		TextBox^ textBox = gcnew TextBox();

		textBox->Font = textFont;
		//textBox->Size = size;
		textBox->Dock = DockStyle::Fill;
		//textBox->Text = text;
		panel->Controls->Add(textBox);
		panel->SetColumn(textBox, currentCol++);
		panel->SetRow(textBox, currentRow);
			
	}

private:
	int currentRow;
	int currentCol;

	TableLayoutPanel^ panel;
};

