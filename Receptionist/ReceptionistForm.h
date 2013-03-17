#pragma once
using namespace System::Xml;
using namespace System::Drawing;
#include "XmlGuiMaker.h"
#include "PcrsXmlGuiMaker.h"

namespace Receptionist {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	/// <summary>
	/// Summary for Receptionist
	/// </summary>
	public ref class ReceptionistForm : public System::Windows::Forms::Form
	{
	public:
		ReceptionistForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ReceptionistForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// ReceptionistForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(790, 307);
			this->ForeColor = System::Drawing::Color::Black;
			this->Name = L"ReceptionistForm";
			this->Text = L"Receptionist";
			this->Load += gcnew System::EventHandler(this, &ReceptionistForm::ReceptionistForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	
	private:
		int currentRow;
		int currentCol;
		
		Control^ lastControl;
		bool isSeparateLines;

		

		

		void AddFieldToFlowLayout()
		{
			
		}
	
		System::Void ReceptionistForm_Load(System::Object^  sender, System::EventArgs^  e) {
		Xml::XmlTextReader^ reader = gcnew Xml::XmlTextReader("form.xml");
		
			/*TableLayoutPanel^ panel = gcnew TableLayoutPanel();
			panel->AutoScroll = true;
			panel->Dock = DockStyle::Fill;*/
			isSeparateLines = false;

			FlowLayoutPanel^ panel = gcnew FlowLayoutPanel();
			panel->AutoScroll = true;
			panel->Dock = DockStyle::Fill;
			this->Controls->Add(panel);

			currentRow = 0;
			currentCol = 0;

			String^ id;
			String^ elementType;
			String^ type;
			XmlGuiMaker^ maker = gcnew PcrsXmlGuiMaker(panel);
			while (reader->Read()) 
			{
				switch (reader->NodeType) 
				{
					case XmlNodeType::Element: // The node is an element.
						id = reader->GetAttribute("id");
						type = reader->GetAttribute("type");
						elementType = reader->Name;
						Console::Write("ELEMENT <" + elementType + id);
						Console::WriteLine(">");
						if (elementType == "Section")
						{
							if (type != nullptr)
							{
								isSeparateLines = type->Contains("separate");
							}
						}
						else if (elementType == "Field")
						{
							if (id != nullptr)
							{
								if (id == "Gender")
								{
									maker->AddGenderField();
								}
								else
								{
									maker->AddField(id);
								}
								if (isSeparateLines)
								{
									panel->SetFlowBreak(lastControl, true);
								}
							}
							//Ignoring fields with no ID
						}
						else if (elementType == "br")
						{
							currentRow++;
							currentCol = 0;
							if (lastControl != nullptr)
							{
								if (!isSeparateLines)
								{
									panel->SetFlowBreak(lastControl, true);
								}
							}
						}
						break;
					case XmlNodeType::Text: //Display the text in each element.
						Console::WriteLine ("VALUE" + reader->Value);
						break;
					case XmlNodeType::EndElement: //Display the end of the element.
						Console::Write("END </" + reader->Name);
						Console::WriteLine(">");
						break;
				}
			}
		}
	};
}
