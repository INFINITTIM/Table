#pragma once


#include <vector>
#include <string>
#include <msclr\marshal_cppstd.h>

#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\Record.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\Table.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\ArrayTable.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\ScanTable.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\SortTable.h"
#include "../Table/main.cpp"

namespace CppWinForm1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			program = new Program();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: Program* program;


	protected:

	private:
		System::ComponentModel::Container ^components;
		void DisplayRecordsInGrid()
		{
			dataGridView1->Rows->Clear();

			auto records = program->GetAllRecords();

			for each (auto rec in records)
			{
				array<System::String^>^ row = gcnew array<System::String^>(2);
				row[0] = gcnew System::String(std::to_string(rec.key).c_str());
				row[1] = gcnew System::String(std::to_string(rec.val).c_str());
				dataGridView1->Rows->Add(row);
			}
		}

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->SuspendLayout();

			this->dataGridView1->Location = System::Drawing::Point(20, 20);
			this->dataGridView1->Size = System::Drawing::Size(600, 400);
			this->dataGridView1->Columns->Add(gcnew DataGridViewTextBoxColumn());
			this->dataGridView1->Columns->Add(gcnew DataGridViewTextBoxColumn());
			this->dataGridView1->Columns[0]->Name = L"Ключ";
			this->dataGridView1->Columns[0]->HeaderText = L"Ключ";
			this->dataGridView1->Columns[1]->Name = L"Значение";
			this->dataGridView1->Columns[1]->HeaderText = L"Значение";
			this->Controls->Add(this->dataGridView1);






			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(1189, 30);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(200, 68);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Создать таблицу";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(1189, 117);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(170, 45);
			this->textBox1->TabIndex = 1;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox2->Location = System::Drawing::Point(1189, 181);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(170, 45);
			this->textBox2->TabIndex = 2;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox2_TextChanged);
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox3->Location = System::Drawing::Point(1189, 246);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(170, 45);
			this->textBox3->TabIndex = 3;
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox3_TextChanged);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(210)), static_cast<System::Int32>(static_cast<System::Byte>(235)),
				static_cast<System::Int32>(static_cast<System::Byte>(245)));
			this->ClientSize = System::Drawing::Size(1420, 720);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		int tableType = 0;
		int size = 0;
		int count = 0;

		try {
			tableType = System::Convert::ToInt32(textBox1->Text);
			size = System::Convert::ToInt32(textBox2->Text);
			count = System::Convert::ToInt32(textBox3->Text);
		}
		catch (...) {
			MessageBox::Show("Проверьте правильность входных данных");
			return;
		}

		program->CreateTable(tableType, size);
		program->FillRandom(count, 1000);
		// Отобразить таблицу
		DisplayRecordsInGrid();
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox3_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
