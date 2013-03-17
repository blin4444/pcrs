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
				this->AddField((TextField^) element);
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
		//Do nothing for table!
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

