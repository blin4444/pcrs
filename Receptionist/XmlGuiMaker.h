#pragma once
using namespace System::Xml;
using namespace System::Drawing;
using namespace System::Windows::Forms;

ref class XmlGuiMaker abstract 
{
public:

	/*XmlGuiMaker(Panel^ panel)
	{
		this->panel = panel;
		isSeparateLines = false;
	}

	XmlGuiMaker(void)
	{
		isSeparateLines = false;
	}*/
	Panel^ CreateNewPanel()
	{
		Panel^ newPanel = gcnew Panel();
		lastControl = newPanel;
		panel->Controls->Add(newPanel);
		return newPanel;
	}

	virtual void AddField(System::String^ text) = 0;

	virtual void AddGenderField() = 0;

	virtual void SetSeparateLines(bool isSeparateLines)
	{
		this->isSeparateLines = isSeparateLines;
	}

	virtual void PlaceToRight(Control^ left, Control^ right) 
	{
		right->SetBounds(left->Bounds.Width + 10,0, right->Bounds.Width, right->Bounds.Height);
	}

protected:
	Panel^ panel;
	bool isSeparateLines;
	Control^ lastControl;
};
