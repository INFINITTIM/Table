#pragma once

#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\main.cpp"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\Table.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\Record.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\ArrayTable.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\ScanTable.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\SortTable.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\HashTableUsedArray.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\HashTableUsedList.h"

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
			delete program;
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	protected:

	private:
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Button^ button2;
		   Program* program;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->button2 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(1229, 48);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(233, 76);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Создать таблицу";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(1229, 144);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(233, 45);
			this->textBox1->TabIndex = 1;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox2->Location = System::Drawing::Point(1229, 285);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(233, 45);
			this->textBox2->TabIndex = 2;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox2_TextChanged);
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox3->Location = System::Drawing::Point(1229, 214);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(233, 45);
			this->textBox3->TabIndex = 3;
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox3_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 25, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(1122, 139);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(85, 48);
			this->label1->TabIndex = 4;
			this->label1->Text = L"тип";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 25, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(1060, 280);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(147, 48);
			this->label2->TabIndex = 5;
			this->label2->Text = L"кол-во";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 25, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(1044, 211);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(163, 48);
			this->label3->TabIndex = 6;
			this->label3->Text = L"размер";
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(117, 57);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(552, 620);
			this->dataGridView1->TabIndex = 7;
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(1229, 354);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(233, 76);
			this->button2->TabIndex = 8;
			this->button2->Text = L"Отсортировать";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(173)), static_cast<System::Int32>(static_cast<System::Byte>(216)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->ClientSize = System::Drawing::Size(1516, 726);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
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
		void DisplayRecordsInGrid()
		{
			// Убираем выделение строк
			dataGridView1->RowHeadersVisible = false;

			// Запрещаем редактирование
			dataGridView1->ReadOnly = true;

			// Отключаем подсветку выбранных ячеек
			dataGridView1->DefaultCellStyle->SelectionBackColor = dataGridView1->DefaultCellStyle->BackColor;
			dataGridView1->DefaultCellStyle->SelectionForeColor = dataGridView1->DefaultCellStyle->ForeColor;

			// Автоматическая ширина колонок
			if (dataGridView1->Columns->Count == 0)
			{
				auto colKey = gcnew DataGridViewTextBoxColumn();
				colKey->Name = L"KeyColumn";
				colKey->HeaderText = L"Ключ";
				colKey->SortMode = DataGridViewColumnSortMode::NotSortable;
				colKey->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;

				auto colVal = gcnew DataGridViewTextBoxColumn();
				colVal->Name = L"ValueColumn";
				colVal->HeaderText = L"Значение";
				colVal->SortMode = DataGridViewColumnSortMode::NotSortable;
				colVal->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;

				dataGridView1->Columns->Add(colKey);
				dataGridView1->Columns->Add(colVal);
			}

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
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox3_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		program->Sort(SelectS);
		DisplayRecordsInGrid();
	}
};
}
