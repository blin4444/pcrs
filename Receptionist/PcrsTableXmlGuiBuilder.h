#pragma once
#include "ElementType.h"
#include "Section.h"
#include "FormElement.h"
#include "RadioGroup.h"
#include "TextField.h"
#include "PcrsXmlGuiMaker.h"

using namespace System::Xml;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace std;
using namespace PCRS;


#include "xmlguimaker.h"

using namespace System;
#include "FormElement.h"

ref class PcrsTableXmlGuiMaker :
public XmlGuiMaker
{
public:

	PcrsTableXmlGuiMaker(TableLayoutPanel^ panel)
	{
		this->panel = panel;
		this->Initialize();
		row = 0;
		col = 0;
	}

	PcrsTableXmlGuiMaker(void)
	{
		this->Initialize();
	}

	virtual void SetPanel(TableLayoutPanel^ panel)
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
				//panel->SetFlowBreak(this->lastControl, true);
			}
			else if (element->IsType(SectionType))
			{

				FlowLayoutPanel^ panel = gcnew FlowLayoutPanel();
				panel->BackColor = Color::White;
				currentSection = (Section^) element;
				PcrsXmlGuiMaker^ guiMaker = gcnew PcrsXmlGuiMaker(panel);
				guiMaker->MakeFromElementList(currentSection->elements);
				panel->AutoSize = true;
				panel->Padding = System::Windows::Forms::Padding(30);
				panel->Dock = DockStyle::Top;
				//panel->Width = this->panel->Width;
				this->lastControl = panel;
				this->panel->Controls->Add(panel);
				if (this->lastControl != nullptr)
				{
					//panel->SetFlowBreak(this->lastControl, true);
				}
			}
			else if (element->IsType(RadioGroupType))
			{
				//RadioGroup^ radioGroup = (RadioGroup^) element;
				TableLayoutPanel^ panel = gcnew TableLayoutPanel();
				panel->AutoSize = true;
				panel->BackColor = Color::AliceBlue;
				this->panel->Controls->Add(panel);
				RadioGroup^ radioGroup = (RadioGroup^) element;
			}
			else if (element->IsType(TextFieldType))
			{
				this->AddField(((TextField^) element)->label);
			}
			NewRow();
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

	TableLayoutPanel^ CreateNewTablePanel()
	{
		TableLayoutPanel^ newPanel = gcnew TableLayoutPanel();
		lastControl = newPanel;
		newPanel->AutoSize = true;
		panel->Controls->Add(newPanel);
		return newPanel;
	}

	void NewRow()
	{
		this->panel->SetRow(lastControl, row++);
	}

	virtual void CreateBreak(bool isForce) override
	{
		/*if (lastControl != nullptr)
		{
			if (!isSeparateLines || isForce)
			{
				panel->SetFlowBreak(lastControl, true);
			}
		}*/
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
		listBox->DropDownWidth = 250;
		
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

	virtual void AddRadioGroup(RadioGroup^ radioGroup) override
	{
		/*if (isList)
		{
			 AddListRadioGroup(name);
		}
		else
		{
			 //AddRadioGroup(name, radioGroup);
		}*/
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

	int IncRow() 
	{
		return row++;
	}

protected:
	TableLayoutPanel^ panel;

private:

	 int row;
	 int col;
};

