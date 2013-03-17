#pragma once
using namespace System::Xml;
using namespace System::Drawing;
#include "XmlGuiMaker.h"
#include "PcrsXmlGuiMaker.h"
#include "PcrsTableXmlGuiBuilder.h"
#include "XmlGuiParser.h"
#include "XmlOptionsParser.h"
#include <vector>
using namespace std;

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
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 21);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(1185, 496);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::Color::Black;
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"ReceptionistForm";
			this->Text = L"Receptionist";
			this->Load += gcnew System::EventHandler(this, &ReceptionistForm::ReceptionistForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	
	private:
	
		System::Void ReceptionistForm_Load(System::Object^  sender, System::EventArgs^  e) {

			/*FlowLayoutPanel^ panel = gcnew FlowLayoutPanel();
			panel->Padding = System::Windows::Forms::Padding(24);
			panel->AutoScroll = true;
			panel->AutoSize = true;
			panel->Dock = DockStyle::Fill;
			this->Controls->Add(panel);*/

			TableLayoutPanel^ panel = gcnew TableLayoutPanel();
			panel->Padding = System::Windows::Forms::Padding(24);
			panel->AutoScroll = true;
			panel->AutoSize = true;
			panel->Dock = DockStyle::Fill;
			this->Controls->Add(panel);

			auto maker = gcnew PcrsTableXmlGuiMaker(panel);
			XmlGuiParser^ guiParser = gcnew XmlGuiParser();
			XmlOptionsParser^ optionsParser = gcnew XmlOptionsParser(guiParser->radioGroups);

			bool isError = false;
			String^ caption;
			String^ message;
			try
			{
				guiParser->Parse("form.xml");

				maker->MakeFromElementList(guiParser->elements);
	
				optionsParser->Parse("options.xml");
			}
			catch (System::IO::FileNotFoundException^ ex)
			{
				isError = true;
				
				message = "An XML document describing the form for the receptionist could not be found. Please ensure that there is a form.xml and options.xml file in the program folder. " + ex->ToString();
				caption = "Could Not Retrieve Form";

			}
			catch (XmlException^ ex)
			{
				isError = true;
				
				message = "One or more of the XML documents describing the form for the receptionist is not well-formed. Please ensure that form.xml is valid XML. " + ex->ToString();
				caption = "Form Syntax Is Incorrect";
			}

			if (isError)
			{
				MessageBox::Show( this,
					message,
					caption,
					MessageBoxButtons::OK,
					MessageBoxIcon::Error);
			}
			else
			{
				FlowLayoutPanel^ newPanel = gcnew FlowLayoutPanel();
				Button^ submit = gcnew Button();
				submit->Anchor = AnchorStyles::Right;
				submit->AutoSize = true;
				submit->Font = gcnew System::Drawing::Font("Segoe UI", 12);
				submit->Text = "Submit";
				newPanel->Controls->Add(submit);
				
				panel->Controls->Add(newPanel);
				panel->SetRow(newPanel, maker->IncRow() + 1);
			}
		}
	};
}
