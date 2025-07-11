#pragma once
#include "globals.h"
#include <msclr\marshal_cppstd.h>


namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::RichTextBox^ searchBox;
	public: System::Windows::Forms::Button^ searchButton;
	protected:


	public: System::Windows::Forms::RichTextBox^ dataReturnBox;
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
			this->searchBox = (gcnew System::Windows::Forms::RichTextBox());
			this->searchButton = (gcnew System::Windows::Forms::Button());
			this->dataReturnBox = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// searchBox
			// 
			this->searchBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->searchBox->Location = System::Drawing::Point(289, 73);
			this->searchBox->Name = L"searchBox";
			this->searchBox->Size = System::Drawing::Size(134, 40);
			this->searchBox->TabIndex = 0;
			this->searchBox->Text = L"";
			this->searchBox->TextChanged += gcnew System::EventHandler(this, &Form1::richTextBox1_TextChanged);
			// 
			// searchButton
			// 
			this->searchButton->Location = System::Drawing::Point(488, 73);
			this->searchButton->Name = L"searchButton";
			this->searchButton->Size = System::Drawing::Size(108, 40);
			this->searchButton->TabIndex = 1;
			this->searchButton->Text = L"Search";
			this->searchButton->UseVisualStyleBackColor = true;
			this->searchButton->Click += gcnew System::EventHandler(this, &Form1::searchButton_Click);
			// 
			// dataReturnBox
			// 
			this->dataReturnBox->Location = System::Drawing::Point(154, 175);
			this->dataReturnBox->Name = L"dataReturnBox";
			this->dataReturnBox->Size = System::Drawing::Size(622, 359);
			this->dataReturnBox->TabIndex = 2;
			this->dataReturnBox->Text = L"";
			this->dataReturnBox->TextChanged += gcnew System::EventHandler(this, &Form1::dataReturnBox_TextChanged);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(921, 571);
			this->Controls->Add(this->dataReturnBox);
			this->Controls->Add(this->searchButton);
			this->Controls->Add(this->searchBox);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void richTextBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void searchButton_Click(System::Object^ sender, System::EventArgs^ e) {
		print("Search Button Clicked\n");
		//convert text box content to a string to work with
		msclr::interop::marshal_context context;
		searchItem = context.marshal_as<std::string>(searchBox->Text);
		print("Search Item assigned as:%s\n",searchItem.c_str());
		//format string for searching by replaces spaces with _
		std::regex space(" ");
		searchItem=std::regex_replace(searchItem, space, "_");
		//search url for web/wiki page to scrape
		std::string url = "https://warframe.fandom.com/wiki/" + searchItem;
		print("Searching for url:%s\n", url.c_str());
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		std::string WebpageData = "";
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &WebpageData);
		curl_easy_perform(curl);
		//Clear new lines from webdata "\n"
		std::regex n("\\n");
		WebpageData=std::regex_replace(WebpageData, n, "");
		WebpageData = Aquisition(WebpageData);
		//print("%s\n",WebpageData.c_str());
		String^ dataBoxContent= gcnew String(WebpageData.c_str());
		dataReturnBox->Text = dataBoxContent;
		
	}
	private: System::Void dataReturnBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
};

}
