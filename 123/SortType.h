#pragma once

public ref class SortTypeDialog : public System::Windows::Forms::Form
{
public:
	enum class SortType { Merge, Selection, Quick, None };

	SortType selectedSortType;

	SortTypeDialog()
	{
		selectedSortType = SortType::None;
		InitializeComponent();
	}

private:
	System::Windows::Forms::Button^ buttonMerge;
	System::Windows::Forms::Button^ buttonSelection;
	System::Windows::Forms::Button^ buttonQuick;

	void InitializeComponent()
	{
		this->buttonMerge = (gcnew System::Windows::Forms::Button());
		this->buttonSelection = (gcnew System::Windows::Forms::Button());
		this->buttonQuick = (gcnew System::Windows::Forms::Button());

		// 
		// buttonMerge
		// 
		this->buttonMerge->Location = System::Drawing::Point(20, 20);
		this->buttonMerge->Size = System::Drawing::Size(100, 50);
		this->buttonMerge->Text = L"Merge";
		this->buttonMerge->Click += gcnew System::EventHandler(this, &SortTypeDialog::buttonMerge_Click);
		// 
		// buttonSelection
		// 
		this->buttonSelection->Location = System::Drawing::Point(130, 20);
		this->buttonSelection->Size = System::Drawing::Size(100, 50);
		this->buttonSelection->Text = L"Selection";
		this->buttonSelection->Click += gcnew System::EventHandler(this, &SortTypeDialog::buttonSelection_Click);
		// 
		// buttonQuick
		// 
		this->buttonQuick->Location = System::Drawing::Point(240, 20);
		this->buttonQuick->Size = System::Drawing::Size(100, 50);
		this->buttonQuick->Text = L"Quick";
		this->buttonQuick->Click += gcnew System::EventHandler(this, &SortTypeDialog::buttonQuick_Click);

		// 
		// Form settings
		// 
		this->ClientSize = System::Drawing::Size(370, 100);
		this->Controls->Add(this->buttonMerge);
		this->Controls->Add(this->buttonSelection);
		this->Controls->Add(this->buttonQuick);
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->MaximizeBox = false;
		this->MinimizeBox = false;
		this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
		this->Text = L"Выберите тип сортировки";

	}

	void buttonMerge_Click(System::Object^ sender, System::EventArgs^ e)
	{
		selectedSortType = SortType::Merge;
		this->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->Close();
	}
	void buttonSelection_Click(System::Object^ sender, System::EventArgs^ e)
	{
		selectedSortType = SortType::Selection;
		this->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->Close();
	}
	void buttonQuick_Click(System::Object^ sender, System::EventArgs^ e)
	{
		selectedSortType = SortType::Quick;
		this->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->Close();
	}
};