#pragma once

#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\main.cpp"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\Table.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\Record.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\ArrayTable.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\ScanTable.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\SortTable.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\HashTableUsedArray.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\HashTableUsedList.h"

#include "SortType.h"

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

	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	protected:

	private:
		System::ComponentModel::Container^ components;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ textBox7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label10;


		   Program* program;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			   this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->button3 = (gcnew System::Windows::Forms::Button());
			   this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			   this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			   this->label4 = (gcnew System::Windows::Forms::Label());
			   this->label5 = (gcnew System::Windows::Forms::Label());
			   this->button4 = (gcnew System::Windows::Forms::Button());
			   this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			   this->label6 = (gcnew System::Windows::Forms::Label());
			   this->label7 = (gcnew System::Windows::Forms::Label());
			   this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			   this->label8 = (gcnew System::Windows::Forms::Label());
			   this->label9 = (gcnew System::Windows::Forms::Label());
			   this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			   this->button5 = (gcnew System::Windows::Forms::Button());
			   this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			   this->label10 = (gcnew System::Windows::Forms::Label());
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
			   this->label1->Location = System::Drawing::Point(1073, 139);
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
			   this->button2->Location = System::Drawing::Point(974, 48);
			   this->button2->Name = L"button2";
			   this->button2->Size = System::Drawing::Size(233, 76);
			   this->button2->TabIndex = 8;
			   this->button2->Text = L"Отсортировать";
			   this->button2->UseVisualStyleBackColor = true;
			   this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			   // 
			   // button3
			   // 
			   this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button3->Location = System::Drawing::Point(1229, 453);
			   this->button3->Name = L"button3";
			   this->button3->Size = System::Drawing::Size(233, 76);
			   this->button3->TabIndex = 9;
			   this->button3->Text = L"Добавить эл-т";
			   this->button3->UseVisualStyleBackColor = true;
			   this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			   // 
			   // textBox4
			   // 
			   this->textBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->textBox4->Location = System::Drawing::Point(1362, 581);
			   this->textBox4->Name = L"textBox4";
			   this->textBox4->Size = System::Drawing::Size(100, 45);
			   this->textBox4->TabIndex = 10;
			   this->textBox4->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox4_TextChanged);
			   // 
			   // textBox5
			   // 
			   this->textBox5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->textBox5->Location = System::Drawing::Point(1229, 581);
			   this->textBox5->Name = L"textBox5";
			   this->textBox5->Size = System::Drawing::Size(100, 45);
			   this->textBox5->TabIndex = 11;
			   this->textBox5->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox5_TextChanged);
			   // 
			   // label4
			   // 
			   this->label4->AutoSize = true;
			   this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label4->Location = System::Drawing::Point(1247, 549);
			   this->label4->Name = L"label4";
			   this->label4->Size = System::Drawing::Size(57, 29);
			   this->label4->TabIndex = 12;
			   this->label4->Text = L"Key";
			   // 
			   // label5
			   // 
			   this->label5->AutoSize = true;
			   this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label5->Location = System::Drawing::Point(1387, 549);
			   this->label5->Name = L"label5";
			   this->label5->Size = System::Drawing::Size(50, 29);
			   this->label5->TabIndex = 13;
			   this->label5->Text = L"Val";
			   // 
			   // button4
			   // 
			   this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button4->Location = System::Drawing::Point(963, 453);
			   this->button4->Name = L"button4";
			   this->button4->Size = System::Drawing::Size(233, 76);
			   this->button4->TabIndex = 14;
			   this->button4->Text = L"Удалить эл-т";
			   this->button4->UseVisualStyleBackColor = true;
			   this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			   // 
			   // textBox6
			   // 
			   this->textBox6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->textBox6->Location = System::Drawing::Point(1031, 581);
			   this->textBox6->Name = L"textBox6";
			   this->textBox6->Size = System::Drawing::Size(100, 45);
			   this->textBox6->TabIndex = 15;
			   this->textBox6->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox6_TextChanged);
			   // 
			   // label6
			   // 
			   this->label6->AutoSize = true;
			   this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label6->Location = System::Drawing::Point(1047, 549);
			   this->label6->Name = L"label6";
			   this->label6->Size = System::Drawing::Size(57, 29);
			   this->label6->TabIndex = 16;
			   this->label6->Text = L"Key";
			   // 
			   // label7
			   // 
			   this->label7->AutoSize = true;
			   this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label7->Location = System::Drawing::Point(1074, 649);
			   this->label7->Name = L"label7";
			   this->label7->Size = System::Drawing::Size(312, 78);
			   this->label7->TabIndex = 17;
			   this->label7->Text = L"Эффективность: 0\r\n\r\n";
			   this->label7->Click += gcnew System::EventHandler(this, &MyForm::label7_Click);
			   // 
			   // textBox7
			   // 
			   this->textBox7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->textBox7->Location = System::Drawing::Point(1229, 354);
			   this->textBox7->Name = L"textBox7";
			   this->textBox7->Size = System::Drawing::Size(233, 45);
			   this->textBox7->TabIndex = 18;
			   this->textBox7->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox7_TextChanged);
			   // 
			   // label8
			   // 
			   this->label8->AutoSize = true;
			   this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 25, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label8->Location = System::Drawing::Point(845, 349);
			   this->label8->Name = L"label8";
			   this->label8->Size = System::Drawing::Size(351, 48);
			   this->label8->TabIndex = 19;
			   this->label8->Text = L"макс. зн-е ключа";
			   // 
			   // label9
			   // 
			   this->label9->AutoSize = true;
			   this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label9->Location = System::Drawing::Point(707, 649);
			   this->label9->Name = L"label9";
			   this->label9->Size = System::Drawing::Size(256, 78);
			   this->label9->TabIndex = 20;
			   this->label9->Text = L"Кол-во эл-ов: 0\r\n\r\n";
			   // 
			   // comboBox1
			   // 
			   this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			   this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->comboBox1->FormattingEnabled = true;
			   this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				   L"Неотсорт. табл.", L"Отсорт. табл.", L"Хэш-табл. М.",
					   L"Хэш-табл. Л."
			   });
			   this->comboBox1->Location = System::Drawing::Point(1176, 141);
			   this->comboBox1->Name = L"comboBox1";
			   this->comboBox1->Size = System::Drawing::Size(286, 46);
			   this->comboBox1->TabIndex = 21;
			   // 
			   // button5
			   // 
			   this->button5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button5->Location = System::Drawing::Point(698, 453);
			   this->button5->Name = L"button5";
			   this->button5->Size = System::Drawing::Size(233, 76);
			   this->button5->TabIndex = 22;
			   this->button5->Text = L"Найти элемент";
			   this->button5->UseVisualStyleBackColor = true;
			   this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			   // 
			   // textBox1
			   // 
			   this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->textBox1->Location = System::Drawing::Point(765, 581);
			   this->textBox1->Name = L"textBox1";
			   this->textBox1->Size = System::Drawing::Size(100, 45);
			   this->textBox1->TabIndex = 23;
			   // 
			   // label10
			   // 
			   this->label10->AutoSize = true;
			   this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label10->Location = System::Drawing::Point(782, 549);
			   this->label10->Name = L"label10";
			   this->label10->Size = System::Drawing::Size(57, 29);
			   this->label10->TabIndex = 24;
			   this->label10->Text = L"Key";
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(173)), static_cast<System::Int32>(static_cast<System::Byte>(216)),
				   static_cast<System::Int32>(static_cast<System::Byte>(230)));
			   this->ClientSize = System::Drawing::Size(1516, 726);
			   this->Controls->Add(this->label10);
			   this->Controls->Add(this->textBox1);
			   this->Controls->Add(this->button5);
			   this->Controls->Add(this->comboBox1);
			   this->Controls->Add(this->label9);
			   this->Controls->Add(this->label8);
			   this->Controls->Add(this->textBox7);
			   this->Controls->Add(this->label7);
			   this->Controls->Add(this->label6);
			   this->Controls->Add(this->textBox6);
			   this->Controls->Add(this->button4);
			   this->Controls->Add(this->label5);
			   this->Controls->Add(this->label4);
			   this->Controls->Add(this->textBox5);
			   this->Controls->Add(this->textBox4);
			   this->Controls->Add(this->button3);
			   this->Controls->Add(this->button2);
			   this->Controls->Add(this->dataGridView1);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->textBox3);
			   this->Controls->Add(this->textBox2);
			   this->Controls->Add(this->button1);
			   this->Name = L"MyForm";
			   this->Text = L"MyForm";
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
		   System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
			   int tableType = comboBox1->SelectedIndex;
			   int size = 0;
			   int count = 0;
			   int maxkey = 0;

			   try {
				   //tableType = System::Convert::ToInt32(textBox1->Text);
				   size = System::Convert::ToInt32(textBox3->Text);
				   count = System::Convert::ToInt32(textBox2->Text);
				   maxkey = System::Convert::ToInt32(textBox7->Text);
			   }
			   catch (...) {
				   MessageBox::Show("Проверьте правильность входных данных");
				   return;
			   }

			   program->CreateTable(tableType, size);
			   program->FillRandom(count, maxkey);
			   // Отобразить таблицу
			   DisplayRecordsInGrid();
			   UpdateLabel7();
		   }
		   void UpdateLabel7()
		   {
			   // Предположим, что значение для label7 зависит от какого-то свойства программы,
			   // например, от текущего количества элементов или состояния.
			   // Например, можно показывать текущий размер таблицы:
			   int eff = program->GetEff(); // Предположим, что есть такой метод
			   int dc = program->GetDC();
			   label7->Text = gcnew String("Эффективность: " + eff.ToString());
			   label9->Text = gcnew String("Кол-во эл-ов: " + dc.ToString());
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

			   for (size_t i = 0; i < records.size(); ++i)
			   {
				   auto rec = records[i];
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
		if (program->GetType() == 0)
		{
			// Создаем диалог
			SortTypeDialog^ sortDialog = gcnew SortTypeDialog();

			// Показываем модальное окно
			if (sortDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				// Получаем выбранный тип
				auto sortType = sortDialog->selectedSortType;

				// В зависимости от выбора вызываем нужную сортировку
				switch (sortType)
				{
				case SortTypeDialog::SortType::Merge:
					program->Sort(MergeS); // Предположим, что у вас есть такие методы
					break;
				case SortTypeDialog::SortType::Selection:
					program->Sort(SelectS);
					break;
				case SortTypeDialog::SortType::Quick:
					program->Sort(QuickS);
					break;
				default:
					// ничего не делать
					break;
				}

				// Обновляем отображение после сортировки
				DisplayRecordsInGrid();
				UpdateLabel7();
				//textBox1->Text = "1";
				comboBox1->SelectedIndex = 1;
			}
		}

	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!program->IsCreateTable()) {
			MessageBox::Show("Сначала создайте таблицу");
			return;
		}

		try {
			int key = System::Convert::ToInt32(textBox5->Text);
			int val = System::Convert::ToInt32(textBox4->Text);
			program->Insert(key, val);
			// Обновляем отображение
			DisplayRecordsInGrid();
			UpdateLabel7();
			// Очистка полей
			textBox4->Clear();
			textBox5->Clear();
		}
		catch (...) {
			MessageBox::Show("Ошибка при добавлении");
		}
	}
	private: System::Void textBox5_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox4_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	int key = System::Convert::ToInt32(textBox6->Text);
	program->RemoveElementByKey(key);
	DisplayRecordsInGrid();
	UpdateLabel7();
	textBox6->Clear();
}
private: System::Void textBox6_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label7_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox7_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		int key = System::Convert::ToInt32(textBox1->Text);
		auto records = program->GetAllRecords();

		// Ищем индекс строки с нужным ключом
		int index = -1;
		for (size_t i = 0; i < records.size(); ++i) {
			if (records[i].key == key) {
				index = static_cast<int>(i);
				break;
			}
		}

		if (program->FindElementByKey(key)) {
			// Делаем выделение нужной строки
			dataGridView1->ClearSelection();
			dataGridView1->Rows[index]->Selected = true;

			// Прокручиваем DataGridView к выбранной строке
			dataGridView1->FirstDisplayedScrollingRowIndex = index;
		}
		else {
			MessageBox::Show("Элемент с таким ключом не найден");
		}
	}
	catch (...) {
		MessageBox::Show("Ошибка при поиске");
	}
	DisplayRecordsInGrid();
	UpdateLabel7();
	// Очистка поля поиска
	textBox1->Clear();
}
};
}
