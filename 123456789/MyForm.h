#pragma once

#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\main.cpp"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\Table.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\Record.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\ArrayTable.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\ScanTable.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\SortTable.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\HashTableUsedArray.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\HashTableUsedList.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\Tree.h"
#include "C:\Users\wwwti\OneDrive\Рабочий стол\VSProjects\Table\Table\TreeBalance.h"
#include <sstream>
#include <msclr/marshal_cppstd.h>

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
            normalTree = nullptr;
            balancedTree = nullptr;
            foundNodeKey = -1;
        }

    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
            if (normalTree) delete normalTree;
            if (balancedTree) delete balancedTree;
        }

    private:
        System::ComponentModel::Container^ components;
        TreeTable<int, int>* normalTree;
        TreeBalance<int, int>* balancedTree;
        int foundNodeKey; // Для хранения ключа найденного узла

        // Элементы управления
        System::Windows::Forms::GroupBox^ groupBoxTree;
        System::Windows::Forms::RadioButton^ radioButtonNormalTree;
        System::Windows::Forms::RadioButton^ radioButtonBalancedTree;
        System::Windows::Forms::TextBox^ textBoxNodeCount;
        System::Windows::Forms::TextBox^ textBoxMaxKey;
        System::Windows::Forms::Label^ labelNodeCount;
        System::Windows::Forms::Label^ labelMaxKey;
        System::Windows::Forms::Button^ buttonCreateTree;
        System::Windows::Forms::RichTextBox^ richTextBoxTree;
        System::Windows::Forms::GroupBox^ groupBoxOperations;
        System::Windows::Forms::Label^ labelKey;
        System::Windows::Forms::TextBox^ textBoxKey;
        System::Windows::Forms::Button^ buttonAdd;
        System::Windows::Forms::Button^ buttonDelete;
        System::Windows::Forms::Button^ buttonSearch; // Новая кнопка поиска

        // Новые элементы
        System::Windows::Forms::Label^ labelEff;
        System::Windows::Forms::GroupBox^ groupBoxRange;
        System::Windows::Forms::Label^ labelFrom;
        System::Windows::Forms::Label^ labelTo;
        System::Windows::Forms::Label^ labelStep;
        System::Windows::Forms::TextBox^ textBoxFrom;
        System::Windows::Forms::TextBox^ textBoxTo;
        System::Windows::Forms::TextBox^ textBoxStep;
        System::Windows::Forms::Button^ buttonAddRange;

        template <typename TTree>
        void FillTree(TTree* tree, int nodeCount, int maxKey) {
            Random^ rand = gcnew Random();
            int inserted = 0;
            while (inserted < nodeCount) {
                int key = rand->Next(1, maxKey + 1);
                try {
                    if (tree->Insert(Record<int, int>{key, 0})) {
                        inserted++;
                    }
                }
                catch (...) {
                    // Игнорируем повторяющиеся ключи
                }
            }
        }

        void UpdateTreeView() {
            try {
                std::stringstream ss;
                if (normalTree) {
                    normalTree->printTree(ss);
                }
                else if (balancedTree) {
                    balancedTree->printTree(ss);
                }
                else {
                    richTextBoxTree->Text = "Дерево не создано!";
                    return;
                }

                // Преобразуем вывод дерева в строку
                std::string treeStr = ss.str();
                std::string resultStr = treeStr;

                // Если есть найденный узел, подсветим его
                if (foundNodeKey != -1) {
                    std::string keyStr = std::to_string(foundNodeKey);
                    size_t start_pos = 0;
                    bool found = false;

                    // Ищем точное вхождение ключа (с границами слова)
                    while ((start_pos = treeStr.find(keyStr, start_pos)) != std::string::npos) {
                        // Проверяем границы слова
                        bool is_word_boundary = true;
                        if (start_pos > 0) {
                            char prev_char = treeStr[start_pos - 1];
                            is_word_boundary &= !std::isdigit(prev_char) && prev_char != '.';
                        }
                        if (start_pos + keyStr.length() < treeStr.length()) {
                            char next_char = treeStr[start_pos + keyStr.length()];
                            is_word_boundary &= !std::isdigit(next_char) && next_char != '.';
                        }

                        if (is_word_boundary) {
                            // Вставляем маркеры вокруг найденного ключа
                            resultStr = treeStr;
                            resultStr.insert(start_pos + keyStr.length(), " <<<");
                            resultStr.insert(start_pos, ">>> ");
                            found = true;
                            break;
                        }
                        start_pos += keyStr.length();
                    }

                    if (!found) {
                        // Если не нашли - сбрасываем подсветку
                        foundNodeKey = -1;
                    }
                }

                richTextBoxTree->Text = gcnew String(resultStr.c_str());
            }
            catch (...) {
                richTextBoxTree->Text = "Ошибка при отображении дерева!";
            }
        }

        void UpdateEfficiency() {
            int eff = 0;
            if (normalTree) eff = normalTree->getEff();
            else if (balancedTree) eff = balancedTree->getEff();
            labelEff->Text = "Эффективность: " + eff.ToString();
        }

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->groupBoxTree = (gcnew System::Windows::Forms::GroupBox());
            this->radioButtonBalancedTree = (gcnew System::Windows::Forms::RadioButton());
            this->radioButtonNormalTree = (gcnew System::Windows::Forms::RadioButton());
            this->textBoxNodeCount = (gcnew System::Windows::Forms::TextBox());
            this->textBoxMaxKey = (gcnew System::Windows::Forms::TextBox());
            this->labelNodeCount = (gcnew System::Windows::Forms::Label());
            this->labelMaxKey = (gcnew System::Windows::Forms::Label());
            this->buttonCreateTree = (gcnew System::Windows::Forms::Button());
            this->richTextBoxTree = (gcnew System::Windows::Forms::RichTextBox());
            this->groupBoxOperations = (gcnew System::Windows::Forms::GroupBox());
            this->buttonSearch = (gcnew System::Windows::Forms::Button()); // Новая кнопка
            this->buttonDelete = (gcnew System::Windows::Forms::Button());
            this->buttonAdd = (gcnew System::Windows::Forms::Button());
            this->textBoxKey = (gcnew System::Windows::Forms::TextBox());
            this->labelKey = (gcnew System::Windows::Forms::Label());
            this->labelEff = (gcnew System::Windows::Forms::Label());
            this->groupBoxRange = (gcnew System::Windows::Forms::GroupBox());
            this->textBoxFrom = (gcnew System::Windows::Forms::TextBox());
            this->textBoxTo = (gcnew System::Windows::Forms::TextBox());
            this->textBoxStep = (gcnew System::Windows::Forms::TextBox());
            this->labelFrom = (gcnew System::Windows::Forms::Label());
            this->labelTo = (gcnew System::Windows::Forms::Label());
            this->labelStep = (gcnew System::Windows::Forms::Label());
            this->buttonAddRange = (gcnew System::Windows::Forms::Button());
            this->groupBoxTree->SuspendLayout();
            this->groupBoxOperations->SuspendLayout();
            this->groupBoxRange->SuspendLayout();
            this->SuspendLayout();
            // 
            // groupBoxTree
            // 
            this->groupBoxTree->Controls->Add(this->radioButtonBalancedTree);
            this->groupBoxTree->Controls->Add(this->radioButtonNormalTree);
            this->groupBoxTree->Controls->Add(this->textBoxNodeCount);
            this->groupBoxTree->Controls->Add(this->textBoxMaxKey);
            this->groupBoxTree->Controls->Add(this->labelNodeCount);
            this->groupBoxTree->Controls->Add(this->labelMaxKey);
            this->groupBoxTree->Controls->Add(this->buttonCreateTree);
            this->groupBoxTree->Location = System::Drawing::Point(20, 20);
            this->groupBoxTree->Name = L"groupBoxTree";
            this->groupBoxTree->Size = System::Drawing::Size(300, 180);
            this->groupBoxTree->TabIndex = 0;
            this->groupBoxTree->TabStop = false;
            this->groupBoxTree->Text = L"Создание дерева";
            // 
            // radioButtonBalancedTree
            // 
            this->radioButtonBalancedTree->AutoSize = true;
            this->radioButtonBalancedTree->Location = System::Drawing::Point(20, 60);
            this->radioButtonBalancedTree->Name = L"radioButtonBalancedTree";
            this->radioButtonBalancedTree->Size = System::Drawing::Size(207, 20);
            this->radioButtonBalancedTree->TabIndex = 1;
            this->radioButtonBalancedTree->Text = L"Сбалансированное дерево";
            this->radioButtonBalancedTree->UseVisualStyleBackColor = true;
            // 
            // radioButtonNormalTree
            // 
            this->radioButtonNormalTree->AutoSize = true;
            this->radioButtonNormalTree->Checked = true;
            this->radioButtonNormalTree->Location = System::Drawing::Point(20, 30);
            this->radioButtonNormalTree->Name = L"radioButtonNormalTree";
            this->radioButtonNormalTree->Size = System::Drawing::Size(138, 20);
            this->radioButtonNormalTree->TabIndex = 0;
            this->radioButtonNormalTree->TabStop = true;
            this->radioButtonNormalTree->Text = L"Обычное дерево";
            this->radioButtonNormalTree->UseVisualStyleBackColor = true;
            // 
            // textBoxNodeCount
            // 
            this->textBoxNodeCount->Location = System::Drawing::Point(180, 90);
            this->textBoxNodeCount->Name = L"textBoxNodeCount";
            this->textBoxNodeCount->Size = System::Drawing::Size(100, 22);
            this->textBoxNodeCount->TabIndex = 2;
            this->textBoxNodeCount->Text = L"10";
            // 
            // textBoxMaxKey
            // 
            this->textBoxMaxKey->Location = System::Drawing::Point(180, 120);
            this->textBoxMaxKey->Name = L"textBoxMaxKey";
            this->textBoxMaxKey->Size = System::Drawing::Size(100, 22);
            this->textBoxMaxKey->TabIndex = 3;
            this->textBoxMaxKey->Text = L"100";
            // 
            // labelNodeCount
            // 
            this->labelNodeCount->AutoSize = true;
            this->labelNodeCount->Location = System::Drawing::Point(20, 93);
            this->labelNodeCount->Name = L"labelNodeCount";
            this->labelNodeCount->Size = System::Drawing::Size(131, 16);
            this->labelNodeCount->TabIndex = 4;
            this->labelNodeCount->Text = L"Количество узлов:";
            // 
            // labelMaxKey
            // 
            this->labelMaxKey->AutoSize = true;
            this->labelMaxKey->Location = System::Drawing::Point(20, 123);
            this->labelMaxKey->Name = L"labelMaxKey";
            this->labelMaxKey->Size = System::Drawing::Size(144, 16);
            this->labelMaxKey->TabIndex = 5;
            this->labelMaxKey->Text = L"Максимальный ключ:";
            // 
            // buttonCreateTree
            // 
            this->buttonCreateTree->Location = System::Drawing::Point(20, 150);
            this->buttonCreateTree->Name = L"buttonCreateTree";
            this->buttonCreateTree->Size = System::Drawing::Size(260, 30);
            this->buttonCreateTree->TabIndex = 6;
            this->buttonCreateTree->Text = L"Создать дерево";
            this->buttonCreateTree->UseVisualStyleBackColor = true;
            this->buttonCreateTree->Click += gcnew System::EventHandler(this, &MyForm::buttonCreateTree_Click);
            // 
            // richTextBoxTree
            // 
            this->richTextBoxTree->Font = (gcnew System::Drawing::Font(L"Courier New", 10));
            this->richTextBoxTree->Location = System::Drawing::Point(350, 20);
            this->richTextBoxTree->Name = L"richTextBoxTree";
            this->richTextBoxTree->ReadOnly = true;
            this->richTextBoxTree->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
            this->richTextBoxTree->Size = System::Drawing::Size(730, 450);
            this->richTextBoxTree->TabIndex = 1;
            this->richTextBoxTree->Text = L"";
            // 
            // groupBoxOperations
            // 
            this->groupBoxOperations->Controls->Add(this->buttonSearch); // Добавляем кнопку поиска
            this->groupBoxOperations->Controls->Add(this->buttonDelete);
            this->groupBoxOperations->Controls->Add(this->buttonAdd);
            this->groupBoxOperations->Controls->Add(this->textBoxKey);
            this->groupBoxOperations->Controls->Add(this->labelKey);
            this->groupBoxOperations->Location = System::Drawing::Point(20, 220);
            this->groupBoxOperations->Name = L"groupBoxOperations";
            this->groupBoxOperations->Size = System::Drawing::Size(300, 180);
            this->groupBoxOperations->TabIndex = 2;
            this->groupBoxOperations->TabStop = false;
            this->groupBoxOperations->Text = L"Управление узлами";
            // 
            // buttonSearch
            // 
            this->buttonSearch->Location = System::Drawing::Point(20, 140);
            this->buttonSearch->Name = L"buttonSearch";
            this->buttonSearch->Size = System::Drawing::Size(260, 30);
            this->buttonSearch->TabIndex = 6;
            this->buttonSearch->Text = L"Поиск по ключу";
            this->buttonSearch->UseVisualStyleBackColor = true;
            this->buttonSearch->Click += gcnew System::EventHandler(this, &MyForm::buttonSearch_Click);
            // 
            // buttonDelete
            // 
            this->buttonDelete->Location = System::Drawing::Point(150, 98);
            this->buttonDelete->Name = L"buttonDelete";
            this->buttonDelete->Size = System::Drawing::Size(130, 30);
            this->buttonDelete->TabIndex = 5;
            this->buttonDelete->Text = L"Удалить";
            this->buttonDelete->UseVisualStyleBackColor = true;
            this->buttonDelete->Click += gcnew System::EventHandler(this, &MyForm::buttonDelete_Click);
            // 
            // buttonAdd
            // 
            this->buttonAdd->Location = System::Drawing::Point(20, 98);
            this->buttonAdd->Name = L"buttonAdd";
            this->buttonAdd->Size = System::Drawing::Size(120, 30);
            this->buttonAdd->TabIndex = 4;
            this->buttonAdd->Text = L"Добавить";
            this->buttonAdd->UseVisualStyleBackColor = true;
            this->buttonAdd->Click += gcnew System::EventHandler(this, &MyForm::buttonAdd_Click);
            // 
            // textBoxKey
            // 
            this->textBoxKey->Location = System::Drawing::Point(180, 30);
            this->textBoxKey->Name = L"textBoxKey";
            this->textBoxKey->Size = System::Drawing::Size(100, 22);
            this->textBoxKey->TabIndex = 2;
            this->textBoxKey->Text = L"0";
            // 
            // labelKey
            // 
            this->labelKey->AutoSize = true;
            this->labelKey->Location = System::Drawing::Point(20, 33);
            this->labelKey->Name = L"labelKey";
            this->labelKey->Size = System::Drawing::Size(44, 16);
            this->labelKey->TabIndex = 0;
            this->labelKey->Text = L"Ключ:";
            // 
            // labelEff
            // 
            this->labelEff->AutoSize = true;
            this->labelEff->Location = System::Drawing::Point(20, 420);
            this->labelEff->Name = L"labelEff";
            this->labelEff->Size = System::Drawing::Size(112, 16);
            this->labelEff->TabIndex = 3;
            this->labelEff->Text = L"Эффективность: 0";
            // 
            // groupBoxRange
            // 
            this->groupBoxRange->Controls->Add(this->buttonAddRange);
            this->groupBoxRange->Controls->Add(this->labelStep);
            this->groupBoxRange->Controls->Add(this->labelTo);
            this->groupBoxRange->Controls->Add(this->labelFrom);
            this->groupBoxRange->Controls->Add(this->textBoxStep);
            this->groupBoxRange->Controls->Add(this->textBoxTo);
            this->groupBoxRange->Controls->Add(this->textBoxFrom);
            this->groupBoxRange->Location = System::Drawing::Point(20, 450);
            this->groupBoxRange->Name = L"groupBoxRange";
            this->groupBoxRange->Size = System::Drawing::Size(300, 120);
            this->groupBoxRange->TabIndex = 4;
            this->groupBoxRange->TabStop = false;
            this->groupBoxRange->Text = L"Добавление диапазона";
            // 
            // textBoxFrom
            // 
            this->textBoxFrom->Location = System::Drawing::Point(50, 25);
            this->textBoxFrom->Name = L"textBoxFrom";
            this->textBoxFrom->Size = System::Drawing::Size(60, 22);
            this->textBoxFrom->TabIndex = 0;
            this->textBoxFrom->Text = L"1";
            // 
            // textBoxTo
            // 
            this->textBoxTo->Location = System::Drawing::Point(50, 55);
            this->textBoxTo->Name = L"textBoxTo";
            this->textBoxTo->Size = System::Drawing::Size(60, 22);
            this->textBoxTo->TabIndex = 1;
            this->textBoxTo->Text = L"10";
            // 
            // textBoxStep
            // 
            this->textBoxStep->Location = System::Drawing::Point(50, 85);
            this->textBoxStep->Name = L"textBoxStep";
            this->textBoxStep->Size = System::Drawing::Size(60, 22);
            this->textBoxStep->TabIndex = 2;
            this->textBoxStep->Text = L"1";
            // 
            // labelFrom
            // 
            this->labelFrom->AutoSize = true;
            this->labelFrom->Location = System::Drawing::Point(10, 28);
            this->labelFrom->Name = L"labelFrom";
            this->labelFrom->Size = System::Drawing::Size(24, 16);
            this->labelFrom->TabIndex = 3;
            this->labelFrom->Text = L"От:";
            // 
            // labelTo
            // 
            this->labelTo->AutoSize = true;
            this->labelTo->Location = System::Drawing::Point(10, 58);
            this->labelTo->Name = L"labelTo";
            this->labelTo->Size = System::Drawing::Size(28, 16);
            this->labelTo->TabIndex = 4;
            this->labelTo->Text = L"До:";
            // 
            // labelStep
            // 
            this->labelStep->AutoSize = true;
            this->labelStep->Location = System::Drawing::Point(10, 88);
            this->labelStep->Name = L"labelStep";
            this->labelStep->Size = System::Drawing::Size(35, 16);
            this->labelStep->TabIndex = 5;
            this->labelStep->Text = L"Шаг:";
            // 
            // buttonAddRange
            // 
            this->buttonAddRange->Location = System::Drawing::Point(180, 55);
            this->buttonAddRange->Name = L"buttonAddRange";
            this->buttonAddRange->Size = System::Drawing::Size(100, 30);
            this->buttonAddRange->TabIndex = 6;
            this->buttonAddRange->Text = L"Добавить";
            this->buttonAddRange->UseVisualStyleBackColor = true;
            this->buttonAddRange->Click += gcnew System::EventHandler(this, &MyForm::buttonAddRange_Click);
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1111, 590);
            this->Controls->Add(this->groupBoxRange);
            this->Controls->Add(this->labelEff);
            this->Controls->Add(this->groupBoxOperations);
            this->Controls->Add(this->richTextBoxTree);
            this->Controls->Add(this->groupBoxTree);
            this->Name = L"MyForm";
            this->Text = L"Демонстрация деревьев";
            this->groupBoxTree->ResumeLayout(false);
            this->groupBoxTree->PerformLayout();
            this->groupBoxOperations->ResumeLayout(false);
            this->groupBoxOperations->PerformLayout();
            this->groupBoxRange->ResumeLayout(false);
            this->groupBoxRange->PerformLayout();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private:
        System::Void buttonCreateTree_Click(System::Object^ sender, System::EventArgs^ e) {
            try {
                int nodeCount = Convert::ToInt32(textBoxNodeCount->Text);
                int maxKey = Convert::ToInt32(textBoxMaxKey->Text);
                foundNodeKey = -1; // Сбрасываем найденный узел

                if (normalTree) {
                    delete normalTree;
                    normalTree = nullptr;
                }
                if (balancedTree) {
                    delete balancedTree;
                    balancedTree = nullptr;
                }

                if (radioButtonNormalTree->Checked) {
                    normalTree = new TreeTable<int, int>();
                    FillTree(normalTree, nodeCount, maxKey);
                }
                else if (radioButtonBalancedTree->Checked) {
                    balancedTree = new TreeBalance<int, int>();
                    FillTree(balancedTree, nodeCount, maxKey);
                }

                UpdateTreeView();
                UpdateEfficiency();
            }
            catch (FormatException^) {
                MessageBox::Show("Ошибка ввода! Пожалуйста, введите целые числа во все поля.");
            }
            catch (...) {
                MessageBox::Show("Неизвестная ошибка при создании дерева!");
            }
        }

        System::Void buttonAdd_Click(System::Object^ sender, System::EventArgs^ e) {
            try {
                int key = Convert::ToInt32(textBoxKey->Text);
                if (key <= 0) {
                    MessageBox::Show("Ключ должен быть положительным числом больше нуля!");
                    return;
                }
                foundNodeKey = -1; // Сбрасываем найденный узел

                if (normalTree) {
                    if (normalTree->Insert(Record<int, int>{key, 0})) {
                        UpdateTreeView();
                        UpdateEfficiency();
                    }
                    else {
                        MessageBox::Show("Ключ уже существует в дереве!");
                    }
                }
                else if (balancedTree) {
                    try {
                        balancedTree->Insert(Record<int, int>{key, 0});
                        UpdateTreeView();
                        UpdateEfficiency();
                    }
                    catch (...) {
                        MessageBox::Show("Ключ уже существует в дереве!");
                    }
                }
                else {
                    MessageBox::Show("Сначала создайте дерево!");
                }
            }
            catch (FormatException^) {
                MessageBox::Show("Ошибка ввода! Пожалуйста, введите целые числа.");
            }
            catch (...) {
                MessageBox::Show("Неизвестная ошибка при добавлении узла!");
            }
        }

        System::Void buttonDelete_Click(System::Object^ sender, System::EventArgs^ e) {
            try {
                int key = Convert::ToInt32(textBoxKey->Text);
                if (key <= 0) {
                    MessageBox::Show("Ключ должен быть положительным числом больше нуля!");
                    return;
                }
                foundNodeKey = -1; // Сбрасываем найденный узел

                if (normalTree) {
                    try {
                        normalTree->Delete(key);
                        UpdateTreeView();
                        UpdateEfficiency();
                    }
                    catch (...) {
                        MessageBox::Show("Узел с таким ключом не найден!");
                    }
                }
                else if (balancedTree) {
                    try {
                        balancedTree->Delete(key);
                        UpdateTreeView();
                        UpdateEfficiency();
                    }
                    catch (...) {
                        MessageBox::Show("Узел с таким ключом не найден!");
                    }
                }
                else {
                    MessageBox::Show("Сначала создайте дерево!");
                }
            }
            catch (FormatException^) {
                MessageBox::Show("Ошибка ввода! Пожалуйста, введите целое число для ключа.");
            }
            catch (...) {
                MessageBox::Show("Неизвестная ошибка при удалении узла!");
            }
        }

        System::Void buttonAddRange_Click(System::Object^ sender, System::EventArgs^ e) {
            try {
                int from = Convert::ToInt32(textBoxFrom->Text);
                int to = Convert::ToInt32(textBoxTo->Text);
                int step = Convert::ToInt32(textBoxStep->Text);
                foundNodeKey = -1; // Сбрасываем найденный узел

                if (step <= 0) {
                    MessageBox::Show("Шаг должен быть положительным числом!");
                    return;
                }

                if (normalTree) {
                    for (int i = from; i <= to; i += step) {
                        try {
                            normalTree->Insert(Record<int, int>{i, 0});
                        }
                        catch (...) {
                            // Игнорировать дубликаты
                        }
                    }
                }
                else if (balancedTree) {
                    for (int i = from; i <= to; i += step) {
                        try {
                            balancedTree->Insert(Record<int, int>{i, 0});
                        }
                        catch (...) {
                            // Игнорировать дубликаты
                        }
                    }
                }
                else {
                    MessageBox::Show("Сначала создайте дерево!");
                    return;
                }

                UpdateTreeView();
                UpdateEfficiency();
            }
            catch (Exception^ e) {
                MessageBox::Show("Ошибка: " + e->Message);
            }
        }

        // НОВЫЙ ОБРАБОТЧИК ДЛЯ ПОИСКА ПО КЛЮЧУ
        System::Void buttonSearch_Click(System::Object^ sender, System::EventArgs^ e) {
            try {
                int key = Convert::ToInt32(textBoxKey->Text);
                if (key <= 0) {
                    MessageBox::Show("Ключ должен быть положительным числом больше нуля!");
                    return;
                }

                bool found = false;

                if (normalTree) {
                    found = normalTree->Find(key);
                }
                else if (balancedTree) {
                    found = balancedTree->Find(key);
                }
                else {
                    MessageBox::Show("Сначала создайте дерево!");
                    return;
                }

                if (found) {
                    foundNodeKey = key; // Запоминаем найденный ключ
                    UpdateTreeView();   // Обновляем отображение с подсветкой
                    UpdateEfficiency();
                    MessageBox::Show("Узел с ключом " + key + " найден!");
                }
                else {
                    foundNodeKey = -1; // Сбрасываем найденный узел
                    UpdateTreeView();
                    MessageBox::Show("Узел с ключом " + key + " не найден!");
                }
            }
            catch (FormatException^) {
                MessageBox::Show("Ошибка ввода! Пожалуйста, введите целое число для ключа.");
            }
            catch (...) {
                MessageBox::Show("Неизвестная ошибка при поиске узла!");
            }
        }
    };
}