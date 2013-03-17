#pragma once
using namespace System::Xml;
using namespace System::Drawing;
using namespace System::Windows::Forms;

ref class XmlGuiMaker abstract 
{
public:

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

protected:
	bool isSeparateLines;
	Control^ lastControl;
};
