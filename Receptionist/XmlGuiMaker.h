#pragma once
#include "FormElement.h"
using namespace System;
using namespace System::Xml;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace std;
#include <vector>

ref class XmlGuiMaker abstract 
{
public:

	virtual void MakeFromElementList(System::Collections::Generic::List<FormElement^>^ list) = 0;
	
	virtual void AddField(System::String^ text) = 0;

	virtual void AddGenderField() = 0;

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

	//virtual void AddRadioGroup(String^ name, std::vector<String^>& radioGroup, bool isList) = 0;

protected:
	bool isSeparateLines;
	Control^ lastControl;
};
