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
					Panel^ dummy = gcnew Panel();
					dummy->Size = System::Drawing::Size(1,20);
					panel->Controls->Add(dummy);
					panel->SetFlowBreak(dummy, true);
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
		newPanel->Margin = System::Windows::Forms::Padding(5);
		newPanel->Padding = System::Windows::Forms::Padding(5, 0, 5,0);
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
	 FlowLayoutPanel^ panel;
};

