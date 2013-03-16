#pragma once
using namespace System::Xml;
using namespace System::Drawing;

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
			// Receptionist
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(790, 307);
			this->Name = L"Receptionist";
			this->Text = L"Receptionist";
			this->Load += gcnew System::EventHandler(this, &ReceptionistForm::ReceptionistForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	
	private:
		int currentRow;

		void AddField(TableLayoutPanel^ panel, System::String^ text)
		{
			using namespace System::Drawing;
			System::Drawing::Font^ textFont = gcnew System::Drawing::Font("Arial", 24);
			System::Drawing::Font^ labelFont = gcnew System::Drawing::Font("Segoe UI", 24);
			System::Drawing::Size size = System::Drawing::Size(400,40);
			Label^ label = gcnew Label();
			label->Size = size;
			label->Text = text;
			label->Font = labelFont;
			
			panel->Controls->Add(label);
			panel->SetRow(label, currentRow);
			panel->SetColumn(label, 0);
			TextBox^ textBox = gcnew TextBox();
			textBox->Font = textFont;
			//textBox->Size = size;
			textBox->Dock = DockStyle::Fill;
			//textBox->Text = text;
			panel->Controls->Add(textBox);
			panel->SetColumn(textBox, 1);
			panel->SetRow(textBox, currentRow);
			
			//panel->SetFlowBreak(textBox, true);
		}
	
		System::Void ReceptionistForm_Load(System::Object^  sender, System::EventArgs^  e) {
		Xml::XmlTextReader^ reader = gcnew Xml::XmlTextReader("form.xml");
		
			TableLayoutPanel^ panel = gcnew TableLayoutPanel();
			panel->AutoScroll = true;
			panel->Dock = DockStyle::Fill;
			this->Controls->Add(panel);

			currentRow = 0;

			String^ id;
			String^ elementType;
			while (reader->Read()) 
			{
				switch (reader->NodeType) 
				{
					case XmlNodeType::Element: // The node is an element.
						id = reader->GetAttribute("id");
						elementType = reader->Name;
						Console::Write("ELEMENT <" + elementType + id);
						Console::WriteLine(">");
						if (elementType == "Field")
						{
							AddField(panel, id);
						}
						else if (elementType == "Break")
						{
							currentRow++;
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
