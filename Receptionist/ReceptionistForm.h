#pragma once
using namespace System::Xml;
using namespace System::Drawing;
#include "XmlGuiMaker.h"
#include "PcrsXmlGuiMaker.h"
#include "PcrsTableXmlGuiBuilder.h"
#include "XmlGuiParser.h"
#include "XmlOptionsParser.h"
#include <vector>
#include "ServerCommunication.h"
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

	protected: 

	protected: 

	protected: 

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
			this->ClientSize = System::Drawing::Size(1000, 480);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::Color::Black;
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"ReceptionistForm";
			this->Text = L"Client Information Form";
			this->Load += gcnew System::EventHandler(this, &ReceptionistForm::ReceptionistForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion

	private:

		Label^ output;
		XmlGuiParser^ guiParser;

		String^ GetData()
		{
			String^ placeholder;
			String^ sgId;
			String^ sgValue;
			ServerCommunication^ sCom = gcnew ServerCommunication();
			for each (FormElement^ rootFormElement in guiParser->elements)
			{
				if (rootFormElement->IsType(PCRS::SectionType))
				{
					Collections::Generic::List<KeyValue^>^ args = gcnew Collections::Generic::List<KeyValue^>();
					args->Add(gcnew KeyValue("sectionID", rootFormElement->id));
					auto section = (Section^) rootFormElement;
					for each (FormElement^ formElement in section->elements)
					{
						sgValue = nullptr;
						placeholder = nullptr;
						placeholder = formElement->placeHolder;
						sgId = formElement->id;

						if (formElement->IsType(PCRS::RadioGroupType))
						{
							auto radioGroup = (RadioGroup^) formElement;
							int value = radioGroup->Value;
							if (!radioGroup->isGender && value != -1)
							{
								value--;
							}
							sgValue = value.ToString();
						}
						else if (formElement->IsType(PCRS::TextFieldType))
						{
							auto textField = (TextField^) formElement;
							sgValue = textField->Value;
						}
						else if (formElement->IsType(PCRS::DateType))
						{
							auto date = (DateElement^) formElement;
							sgValue = date->Value;

						}
						else if (formElement->IsType(PCRS::BreakType))
						{
							continue;
						}

						if (sgValue == nullptr && placeholder != nullptr)
						{
							sgValue = placeholder;
						}

						args->Add(gcnew KeyValue(sgId, sgValue));
						Console::WriteLine(sgId + ": " + sgValue);
					}
					return sCom->SubmitUserInfo(args);
				}
			}
		}

		System::Void btnSubmit_Click(System::Object^  sender, System::EventArgs^  e)
		{
			String^ result = GetData();
			int resultCode = Convert::ToInt32(result[0])-48;
			switch(resultCode)
			{
			case 0:
				ReceptionistForm::ForeColor = Color::Green;
				ReceptionistForm::output->Text = "Success! User token is: " + result;
				break;
			default:
				ReceptionistForm::output->Text = result;
				ReceptionistForm::ForeColor = Color::Red;
				break;
			}
		}

		System::Void ReceptionistForm_Load(System::Object^  sender, System::EventArgs^  e) {

			/*FlowLayoutPanel^ panel = gcnew FlowLayoutPanel();
			panel->Padding = System::Windows::Forms::Padding(24);
			panel->AutoScroll = true;
			panel->AutoSize = true;
			panel->Dock = DockStyle::Fill;
			this->Controls->Add(panel);*/

			TableLayoutPanel^ panel = gcnew TableLayoutPanel();
			//panel->Padding = System::Windows::Forms::Padding(24);
			panel->AutoScroll = true;
			//panel->AutoSize = true;
			panel->Dock = DockStyle::Fill;
			this->Controls->Add(panel);

			auto maker = gcnew PcrsTableXmlGuiMaker(panel);
			guiParser = gcnew XmlGuiParser();
			XmlOptionsParser^ optionsParser = gcnew XmlOptionsParser(guiParser->radioGroups);

			bool isError = false;
			String^ caption;
			String^ message;
			try
			{
				guiParser->Parse("client_information_form.xml");
				if (guiParser->formName != nullptr)
				{
					this->Text = guiParser->formName;
				}

				maker->MakeFromElementList(guiParser->elements);

				optionsParser->Parse("remote_generated_xml");
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
			catch (ArgumentNullException^ ex)
			{
				isError = true;

				message = "At least one of the elements in an XML file describing the form is missing an attribute. Please check form.xml and/or options.xml." + ex->ToString();
				caption = "Form Element Missing Attribute";
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
				Panel^ newPanel = gcnew Panel();
				newPanel->AutoSize = true;
				//newPanel->BackColor = Color::Beige;
				newPanel->Dock = DockStyle::Right;
				newPanel->Size = System::Drawing::Size(300, 120);
				newPanel->Anchor = AnchorStyles::Top;
				Button^ submit = gcnew Button();

				//submit->Anchor = AnchorStyles::Right;

				submit->Font = gcnew System::Drawing::Font("Segoe UI", 12);
				submit->Text = "Submit";
				//submit->Size = System::Drawing::Size(300, 40);
				submit->AutoSize = true;
				submit->Click += gcnew System::EventHandler(this, &ReceptionistForm::btnSubmit_Click);
				newPanel->Controls->Add(submit);

				panel->Controls->Add(newPanel);
				panel->SetRow(newPanel, maker->IncRow());

				Label^ output_text = gcnew Label();
				output_text->Text = "";
				output_text->Font = gcnew System::Drawing::Font("Segoe UI", 12);
				output_text->Anchor = AnchorStyles::Right;
				this->output = output_text;

				Panel^ output_panel = gcnew Panel();
				output_panel->Size = System::Drawing::Size(100, 120);
				output_panel->Controls->Add(output_text);
				output_panel->Anchor = AnchorStyles::Top;
				panel->Controls->Add(output_panel);
				panel->SetRow(output_panel, maker->IncRow());
			}
		}
	private: System::Void maskedTextBox1_MaskInputRejected(System::Object^  sender, System::Windows::Forms::MaskInputRejectedEventArgs^  e) {
			 }
private: System::Void maskedTextBox1_Validated(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}
