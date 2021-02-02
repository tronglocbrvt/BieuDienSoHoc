#pragma once

#include "BinaryNumber.h"
#include <msclr\marshal_cppstd.h>
#include "CoreCalculator.h"
#include <vector>

#define DEC_MODE 10
#define HEX_MODE 16
#define BIN_MODE 2
#define FLOAT_MODE 3
#define TURN_OFF 0
#define TURN_ON 1

namespace Calculator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for CalUI
	/// </summary>
	public ref class CalUI : public System::Windows::Forms::Form
	{
	private: System::Windows::Forms::Button^  bntRol;



	private: System::Windows::Forms::Button^  bntRor;

	private: System::Windows::Forms::Button^  bntOr;

	private: System::Windows::Forms::Button^  bntXor;

	private: System::Windows::Forms::Button^  bntNot;

	private: System::Windows::Forms::Button^  bntAnd;

	private: System::Windows::Forms::Label^  lableHistory;
	private: System::Windows::Forms::Button^  bntRsh;
	private: System::Windows::Forms::Label^  display;


	private: System::Windows::Forms::Button^  bntLsh;


	public:
		CalUI(void)
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
		~CalUI()
		{
			if (components)
			{
				delete components;
			}
			delete _hisNum;
			delete _currNum;
		}
	private: System::Windows::Forms::Button^  bntDEC;
	protected:

	private: System::Windows::Forms::Button^  bntHEX;
	private: System::Windows::Forms::Button^  bntBIN;
	private: System::Windows::Forms::Button^  bntC;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  bntDivison;
	private: System::Windows::Forms::Button^  bntA;
	private: System::Windows::Forms::Button^  bntB;
	private: System::Windows::Forms::Button^  bnt7;
	private: System::Windows::Forms::Button^  bnt8;
	private: System::Windows::Forms::Button^  bnt9;
	private: System::Windows::Forms::Button^  bntMultiply;
	private: System::Windows::Forms::Button^  bntC_;
	private: System::Windows::Forms::Button^  bntD;
	private: System::Windows::Forms::Button^  bnt4;
	private: System::Windows::Forms::Button^  bnt5;
	private: System::Windows::Forms::Button^  bnt6;
	private: System::Windows::Forms::Button^  bntMinus;
	private: System::Windows::Forms::Button^  bntE;
	private: System::Windows::Forms::Button^  bntF;
	private: System::Windows::Forms::Button^  bnt1;
	private: System::Windows::Forms::Button^  bnt2;
	private: System::Windows::Forms::Button^  bnt3;
	private: System::Windows::Forms::Button^  bntPlus;
	private: System::Windows::Forms::Button^  bntFloatMode;
	private: System::Windows::Forms::Button^  bntMod;
	private: System::Windows::Forms::Button^  bnt0;
	private: System::Windows::Forms::Button^  bntDot;
	private: System::Windows::Forms::Button^  bntEqual;

	private: System::Windows::Forms::Label^  displayDEC;
	private: System::Windows::Forms::Label^  displayHEX;
	private: System::Windows::Forms::Label^  displayBIN;
	private: System::Windows::Forms::Button^  button31;
	private: System::Windows::Forms::Button^  bntChangeSign;

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
			this->bntDEC = (gcnew System::Windows::Forms::Button());
			this->bntHEX = (gcnew System::Windows::Forms::Button());
			this->bntBIN = (gcnew System::Windows::Forms::Button());
			this->bntC = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->bntDivison = (gcnew System::Windows::Forms::Button());
			this->bntA = (gcnew System::Windows::Forms::Button());
			this->bntB = (gcnew System::Windows::Forms::Button());
			this->bnt7 = (gcnew System::Windows::Forms::Button());
			this->bnt8 = (gcnew System::Windows::Forms::Button());
			this->bnt9 = (gcnew System::Windows::Forms::Button());
			this->bntMultiply = (gcnew System::Windows::Forms::Button());
			this->bntC_ = (gcnew System::Windows::Forms::Button());
			this->bntD = (gcnew System::Windows::Forms::Button());
			this->bnt4 = (gcnew System::Windows::Forms::Button());
			this->bnt5 = (gcnew System::Windows::Forms::Button());
			this->bnt6 = (gcnew System::Windows::Forms::Button());
			this->bntMinus = (gcnew System::Windows::Forms::Button());
			this->bntE = (gcnew System::Windows::Forms::Button());
			this->bntF = (gcnew System::Windows::Forms::Button());
			this->bnt1 = (gcnew System::Windows::Forms::Button());
			this->bnt2 = (gcnew System::Windows::Forms::Button());
			this->bnt3 = (gcnew System::Windows::Forms::Button());
			this->bntPlus = (gcnew System::Windows::Forms::Button());
			this->bntFloatMode = (gcnew System::Windows::Forms::Button());
			this->bntMod = (gcnew System::Windows::Forms::Button());
			this->bnt0 = (gcnew System::Windows::Forms::Button());
			this->bntDot = (gcnew System::Windows::Forms::Button());
			this->bntEqual = (gcnew System::Windows::Forms::Button());
			this->displayDEC = (gcnew System::Windows::Forms::Label());
			this->displayHEX = (gcnew System::Windows::Forms::Label());
			this->displayBIN = (gcnew System::Windows::Forms::Label());
			this->button31 = (gcnew System::Windows::Forms::Button());
			this->bntChangeSign = (gcnew System::Windows::Forms::Button());
			this->bntRol = (gcnew System::Windows::Forms::Button());
			this->bntRor = (gcnew System::Windows::Forms::Button());
			this->bntOr = (gcnew System::Windows::Forms::Button());
			this->bntXor = (gcnew System::Windows::Forms::Button());
			this->bntNot = (gcnew System::Windows::Forms::Button());
			this->bntAnd = (gcnew System::Windows::Forms::Button());
			this->bntLsh = (gcnew System::Windows::Forms::Button());
			this->lableHistory = (gcnew System::Windows::Forms::Label());
			this->bntRsh = (gcnew System::Windows::Forms::Button());
			this->display = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// bntDEC
			// 
			this->bntDEC->BackColor = System::Drawing::Color::LightGray;
			this->bntDEC->FlatAppearance->BorderSize = 0;
			this->bntDEC->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntDEC->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold));
			this->bntDEC->Location = System::Drawing::Point(3, 130);
			this->bntDEC->Name = L"bntDEC";
			this->bntDEC->Size = System::Drawing::Size(49, 22);
			this->bntDEC->TabIndex = 0;
			this->bntDEC->Text = L"DEC";
			this->bntDEC->UseVisualStyleBackColor = false;
			this->bntDEC->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &CalUI::bntClickDataType);
			// 
			// bntHEX
			// 
			this->bntHEX->BackColor = System::Drawing::Color::LightGray;
			this->bntHEX->FlatAppearance->BorderSize = 0;
			this->bntHEX->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntHEX->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold));
			this->bntHEX->Location = System::Drawing::Point(3, 158);
			this->bntHEX->Name = L"bntHEX";
			this->bntHEX->Size = System::Drawing::Size(49, 23);
			this->bntHEX->TabIndex = 1;
			this->bntHEX->Text = L"HEX";
			this->bntHEX->UseVisualStyleBackColor = false;
			this->bntHEX->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &CalUI::bntClickDataType);
			// 
			// bntBIN
			// 
			this->bntBIN->BackColor = System::Drawing::Color::LightGray;
			this->bntBIN->Cursor = System::Windows::Forms::Cursors::Default;
			this->bntBIN->FlatAppearance->BorderSize = 0;
			this->bntBIN->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntBIN->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold));
			this->bntBIN->Location = System::Drawing::Point(3, 187);
			this->bntBIN->Name = L"bntBIN";
			this->bntBIN->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->bntBIN->Size = System::Drawing::Size(49, 23);
			this->bntBIN->TabIndex = 2;
			this->bntBIN->Text = L"BIN";
			this->bntBIN->UseVisualStyleBackColor = false;
			this->bntBIN->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &CalUI::bntClickDataType);
			// 
			// bntC
			// 
			this->bntC->BackColor = System::Drawing::Color::LightGray;
			this->bntC->FlatAppearance->BorderSize = 0;
			this->bntC->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntC->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntC->Location = System::Drawing::Point(214, 327);
			this->bntC->Name = L"bntC";
			this->bntC->Size = System::Drawing::Size(64, 44);
			this->bntC->TabIndex = 3;
			this->bntC->Text = L"C";
			this->bntC->UseVisualStyleBackColor = false;
			this->bntC->Click += gcnew System::EventHandler(this, &CalUI::clickC);
			// 
			// button5
			// 
			this->button5->BackColor = System::Drawing::Color::LightGray;
			this->button5->FlatAppearance->BorderSize = 0;
			this->button5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button5->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->button5->Location = System::Drawing::Point(284, 327);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(64, 44);
			this->button5->TabIndex = 4;
			this->button5->Text = L"DEL";
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &CalUI::clickBackSlash);
			// 
			// bntDivison
			// 
			this->bntDivison->BackColor = System::Drawing::Color::LightGray;
			this->bntDivison->FlatAppearance->BorderSize = 0;
			this->bntDivison->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntDivison->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntDivison->Location = System::Drawing::Point(354, 327);
			this->bntDivison->Name = L"bntDivison";
			this->bntDivison->Size = System::Drawing::Size(64, 44);
			this->bntDivison->TabIndex = 5;
			this->bntDivison->Text = L"/";
			this->bntDivison->UseVisualStyleBackColor = false;
			this->bntDivison->Click += gcnew System::EventHandler(this, &CalUI::clickBinaryOperators);
			// 
			// bntA
			// 
			this->bntA->BackColor = System::Drawing::Color::LightGray;
			this->bntA->FlatAppearance->BorderSize = 0;
			this->bntA->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntA->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntA->Location = System::Drawing::Point(3, 377);
			this->bntA->Name = L"bntA";
			this->bntA->Size = System::Drawing::Size(64, 44);
			this->bntA->TabIndex = 0;
			this->bntA->Text = L"A";
			this->bntA->UseVisualStyleBackColor = false;
			this->bntA->Click += gcnew System::EventHandler(this, &CalUI::clickNum);
			// 
			// bntB
			// 
			this->bntB->BackColor = System::Drawing::Color::LightGray;
			this->bntB->FlatAppearance->BorderSize = 0;
			this->bntB->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntB->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntB->Location = System::Drawing::Point(73, 377);
			this->bntB->Name = L"bntB";
			this->bntB->Size = System::Drawing::Size(64, 44);
			this->bntB->TabIndex = 1;
			this->bntB->Text = L"B";
			this->bntB->UseVisualStyleBackColor = false;
			this->bntB->Click += gcnew System::EventHandler(this, &CalUI::clickNum);
			// 
			// bnt7
			// 
			this->bnt7->BackColor = System::Drawing::Color::LightGray;
			this->bnt7->FlatAppearance->BorderSize = 0;
			this->bnt7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bnt7->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bnt7->Location = System::Drawing::Point(143, 377);
			this->bnt7->Name = L"bnt7";
			this->bnt7->Size = System::Drawing::Size(64, 44);
			this->bnt7->TabIndex = 2;
			this->bnt7->Text = L"7";
			this->bnt7->UseVisualStyleBackColor = false;
			this->bnt7->Click += gcnew System::EventHandler(this, &CalUI::clickNum);
			// 
			// bnt8
			// 
			this->bnt8->BackColor = System::Drawing::Color::LightGray;
			this->bnt8->FlatAppearance->BorderSize = 0;
			this->bnt8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bnt8->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bnt8->Location = System::Drawing::Point(213, 377);
			this->bnt8->Name = L"bnt8";
			this->bnt8->Size = System::Drawing::Size(64, 44);
			this->bnt8->TabIndex = 3;
			this->bnt8->Text = L"8";
			this->bnt8->UseVisualStyleBackColor = false;
			this->bnt8->Click += gcnew System::EventHandler(this, &CalUI::clickNum);
			// 
			// bnt9
			// 
			this->bnt9->BackColor = System::Drawing::Color::LightGray;
			this->bnt9->FlatAppearance->BorderSize = 0;
			this->bnt9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bnt9->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bnt9->Location = System::Drawing::Point(284, 377);
			this->bnt9->Name = L"bnt9";
			this->bnt9->Size = System::Drawing::Size(64, 44);
			this->bnt9->TabIndex = 4;
			this->bnt9->Text = L"9";
			this->bnt9->UseVisualStyleBackColor = false;
			this->bnt9->Click += gcnew System::EventHandler(this, &CalUI::clickNum);
			// 
			// bntMultiply
			// 
			this->bntMultiply->BackColor = System::Drawing::Color::LightGray;
			this->bntMultiply->FlatAppearance->BorderSize = 0;
			this->bntMultiply->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntMultiply->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntMultiply->Location = System::Drawing::Point(354, 377);
			this->bntMultiply->Name = L"bntMultiply";
			this->bntMultiply->Size = System::Drawing::Size(64, 44);
			this->bntMultiply->TabIndex = 5;
			this->bntMultiply->Text = L"x";
			this->bntMultiply->UseVisualStyleBackColor = false;
			this->bntMultiply->Click += gcnew System::EventHandler(this, &CalUI::clickBinaryOperators);
			// 
			// bntC_
			// 
			this->bntC_->BackColor = System::Drawing::Color::LightGray;
			this->bntC_->FlatAppearance->BorderSize = 0;
			this->bntC_->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntC_->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntC_->Location = System::Drawing::Point(3, 427);
			this->bntC_->Name = L"bntC_";
			this->bntC_->Size = System::Drawing::Size(64, 44);
			this->bntC_->TabIndex = 0;
			this->bntC_->Text = L"C";
			this->bntC_->UseVisualStyleBackColor = false;
			this->bntC_->Click += gcnew System::EventHandler(this, &CalUI::clickNum);
			// 
			// bntD
			// 
			this->bntD->BackColor = System::Drawing::Color::LightGray;
			this->bntD->FlatAppearance->BorderSize = 0;
			this->bntD->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntD->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntD->Location = System::Drawing::Point(73, 427);
			this->bntD->Name = L"bntD";
			this->bntD->Size = System::Drawing::Size(64, 44);
			this->bntD->TabIndex = 1;
			this->bntD->Text = L"D";
			this->bntD->UseVisualStyleBackColor = false;
			this->bntD->Click += gcnew System::EventHandler(this, &CalUI::clickNum);
			// 
			// bnt4
			// 
			this->bnt4->BackColor = System::Drawing::Color::LightGray;
			this->bnt4->FlatAppearance->BorderSize = 0;
			this->bnt4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bnt4->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bnt4->Location = System::Drawing::Point(143, 427);
			this->bnt4->Name = L"bnt4";
			this->bnt4->Size = System::Drawing::Size(64, 44);
			this->bnt4->TabIndex = 2;
			this->bnt4->Text = L"4";
			this->bnt4->UseVisualStyleBackColor = false;
			this->bnt4->Click += gcnew System::EventHandler(this, &CalUI::clickNum);
			// 
			// bnt5
			// 
			this->bnt5->BackColor = System::Drawing::Color::LightGray;
			this->bnt5->FlatAppearance->BorderSize = 0;
			this->bnt5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bnt5->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bnt5->Location = System::Drawing::Point(213, 427);
			this->bnt5->Name = L"bnt5";
			this->bnt5->Size = System::Drawing::Size(64, 44);
			this->bnt5->TabIndex = 3;
			this->bnt5->Text = L"5";
			this->bnt5->UseVisualStyleBackColor = false;
			this->bnt5->Click += gcnew System::EventHandler(this, &CalUI::clickNum);
			// 
			// bnt6
			// 
			this->bnt6->BackColor = System::Drawing::Color::LightGray;
			this->bnt6->FlatAppearance->BorderSize = 0;
			this->bnt6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bnt6->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bnt6->Location = System::Drawing::Point(284, 427);
			this->bnt6->Name = L"bnt6";
			this->bnt6->Size = System::Drawing::Size(64, 44);
			this->bnt6->TabIndex = 4;
			this->bnt6->Text = L"6";
			this->bnt6->UseVisualStyleBackColor = false;
			this->bnt6->Click += gcnew System::EventHandler(this, &CalUI::clickNum);
			// 
			// bntMinus
			// 
			this->bntMinus->BackColor = System::Drawing::Color::LightGray;
			this->bntMinus->FlatAppearance->BorderSize = 0;
			this->bntMinus->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntMinus->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntMinus->Location = System::Drawing::Point(354, 427);
			this->bntMinus->Name = L"bntMinus";
			this->bntMinus->Size = System::Drawing::Size(64, 44);
			this->bntMinus->TabIndex = 5;
			this->bntMinus->Text = L"-";
			this->bntMinus->UseVisualStyleBackColor = false;
			this->bntMinus->Click += gcnew System::EventHandler(this, &CalUI::clickBinaryOperators);
			// 
			// bntE
			// 
			this->bntE->BackColor = System::Drawing::Color::LightGray;
			this->bntE->FlatAppearance->BorderSize = 0;
			this->bntE->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntE->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntE->Location = System::Drawing::Point(3, 477);
			this->bntE->Name = L"bntE";
			this->bntE->Size = System::Drawing::Size(64, 44);
			this->bntE->TabIndex = 0;
			this->bntE->Text = L"E";
			this->bntE->UseVisualStyleBackColor = false;
			this->bntE->Click += gcnew System::EventHandler(this, &CalUI::clickNum);
			// 
			// bntF
			// 
			this->bntF->BackColor = System::Drawing::Color::LightGray;
			this->bntF->FlatAppearance->BorderSize = 0;
			this->bntF->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntF->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntF->Location = System::Drawing::Point(73, 477);
			this->bntF->Name = L"bntF";
			this->bntF->Size = System::Drawing::Size(64, 44);
			this->bntF->TabIndex = 1;
			this->bntF->Text = L"F";
			this->bntF->UseVisualStyleBackColor = false;
			this->bntF->Click += gcnew System::EventHandler(this, &CalUI::clickNum);
			// 
			// bnt1
			// 
			this->bnt1->BackColor = System::Drawing::Color::LightGray;
			this->bnt1->FlatAppearance->BorderSize = 0;
			this->bnt1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bnt1->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bnt1->Location = System::Drawing::Point(143, 477);
			this->bnt1->Name = L"bnt1";
			this->bnt1->Size = System::Drawing::Size(64, 44);
			this->bnt1->TabIndex = 2;
			this->bnt1->Text = L"1";
			this->bnt1->UseVisualStyleBackColor = false;
			this->bnt1->Click += gcnew System::EventHandler(this, &CalUI::clickNum);
			// 
			// bnt2
			// 
			this->bnt2->BackColor = System::Drawing::Color::LightGray;
			this->bnt2->FlatAppearance->BorderSize = 0;
			this->bnt2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bnt2->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bnt2->Location = System::Drawing::Point(213, 477);
			this->bnt2->Name = L"bnt2";
			this->bnt2->Size = System::Drawing::Size(64, 44);
			this->bnt2->TabIndex = 3;
			this->bnt2->Text = L"2";
			this->bnt2->UseVisualStyleBackColor = false;
			this->bnt2->Click += gcnew System::EventHandler(this, &CalUI::clickNum);
			// 
			// bnt3
			// 
			this->bnt3->BackColor = System::Drawing::Color::LightGray;
			this->bnt3->FlatAppearance->BorderSize = 0;
			this->bnt3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bnt3->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bnt3->Location = System::Drawing::Point(284, 477);
			this->bnt3->Name = L"bnt3";
			this->bnt3->Size = System::Drawing::Size(64, 44);
			this->bnt3->TabIndex = 4;
			this->bnt3->Text = L"3";
			this->bnt3->UseVisualStyleBackColor = false;
			this->bnt3->Click += gcnew System::EventHandler(this, &CalUI::clickNum);
			// 
			// bntPlus
			// 
			this->bntPlus->BackColor = System::Drawing::Color::LightGray;
			this->bntPlus->FlatAppearance->BorderSize = 0;
			this->bntPlus->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntPlus->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntPlus->Location = System::Drawing::Point(354, 477);
			this->bntPlus->Name = L"bntPlus";
			this->bntPlus->Size = System::Drawing::Size(64, 44);
			this->bntPlus->TabIndex = 5;
			this->bntPlus->Text = L"+";
			this->bntPlus->UseVisualStyleBackColor = false;
			this->bntPlus->Click += gcnew System::EventHandler(this, &CalUI::clickBinaryOperators);
			// 
			// bntFloatMode
			// 
			this->bntFloatMode->BackColor = System::Drawing::Color::LightGray;
			this->bntFloatMode->FlatAppearance->BorderSize = 0;
			this->bntFloatMode->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntFloatMode->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntFloatMode->Location = System::Drawing::Point(3, 527);
			this->bntFloatMode->Name = L"bntFloatMode";
			this->bntFloatMode->Size = System::Drawing::Size(134, 44);
			this->bntFloatMode->TabIndex = 0;
			this->bntFloatMode->Text = L"Floating Point Mode";
			this->bntFloatMode->UseVisualStyleBackColor = false;
			this->bntFloatMode->Click += gcnew System::EventHandler(this, &CalUI::bnt_FloatMode_Click);
			// 
			// bntMod
			// 
			this->bntMod->BackColor = System::Drawing::Color::LightGray;
			this->bntMod->FlatAppearance->BorderSize = 0;
			this->bntMod->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntMod->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntMod->Location = System::Drawing::Point(73, 327);
			this->bntMod->Name = L"bntMod";
			this->bntMod->Size = System::Drawing::Size(64, 44);
			this->bntMod->TabIndex = 2;
			this->bntMod->Text = L"MOD";
			this->bntMod->UseVisualStyleBackColor = false;
			this->bntMod->Click += gcnew System::EventHandler(this, &CalUI::clickBinaryOperators);
			// 
			// bnt0
			// 
			this->bnt0->BackColor = System::Drawing::Color::LightGray;
			this->bnt0->FlatAppearance->BorderSize = 0;
			this->bnt0->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bnt0->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bnt0->Location = System::Drawing::Point(213, 527);
			this->bnt0->Name = L"bnt0";
			this->bnt0->Size = System::Drawing::Size(64, 44);
			this->bnt0->TabIndex = 3;
			this->bnt0->Text = L"0";
			this->bnt0->UseVisualStyleBackColor = false;
			this->bnt0->Click += gcnew System::EventHandler(this, &CalUI::clickNum);
			// 
			// bntDot
			// 
			this->bntDot->BackColor = System::Drawing::Color::LightGray;
			this->bntDot->FlatAppearance->BorderSize = 0;
			this->bntDot->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntDot->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntDot->Location = System::Drawing::Point(284, 527);
			this->bntDot->Name = L"bntDot";
			this->bntDot->Size = System::Drawing::Size(64, 44);
			this->bntDot->TabIndex = 4;
			this->bntDot->Text = L".";
			this->bntDot->UseVisualStyleBackColor = false;
			this->bntDot->Click += gcnew System::EventHandler(this, &CalUI::clickNum);
			// 
			// bntEqual
			// 
			this->bntEqual->BackColor = System::Drawing::Color::LightGray;
			this->bntEqual->FlatAppearance->BorderSize = 0;
			this->bntEqual->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntEqual->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntEqual->Location = System::Drawing::Point(354, 527);
			this->bntEqual->Name = L"bntEqual";
			this->bntEqual->Size = System::Drawing::Size(64, 44);
			this->bntEqual->TabIndex = 5;
			this->bntEqual->Text = L"=";
			this->bntEqual->UseVisualStyleBackColor = false;
			this->bntEqual->Click += gcnew System::EventHandler(this, &CalUI::bntEqual_Click);
			// 
			// displayDEC
			// 
			this->displayDEC->Font = (gcnew System::Drawing::Font(L"Arial", 14.2F, System::Drawing::FontStyle::Bold));
			this->displayDEC->Location = System::Drawing::Point(55, 130);
			this->displayDEC->Name = L"displayDEC";
			this->displayDEC->Size = System::Drawing::Size(362, 22);
			this->displayDEC->TabIndex = 7;
			this->displayDEC->Text = L"0";
			// 
			// displayHEX
			// 
			this->displayHEX->Font = (gcnew System::Drawing::Font(L"Arial", 14.2F, System::Drawing::FontStyle::Bold));
			this->displayHEX->Location = System::Drawing::Point(55, 159);
			this->displayHEX->Name = L"displayHEX";
			this->displayHEX->Size = System::Drawing::Size(362, 22);
			this->displayHEX->TabIndex = 7;
			this->displayHEX->Text = L"0";
			// 
			// displayBIN
			// 
			this->displayBIN->Font = (gcnew System::Drawing::Font(L"Arial", 14.2F, System::Drawing::FontStyle::Bold));
			this->displayBIN->Location = System::Drawing::Point(55, 191);
			this->displayBIN->Name = L"displayBIN";
			this->displayBIN->Size = System::Drawing::Size(362, 83);
			this->displayBIN->TabIndex = 7;
			this->displayBIN->Text = L"0";
			// 
			// button31
			// 
			this->button31->BackColor = System::Drawing::Color::LightGray;
			this->button31->FlatAppearance->BorderSize = 0;
			this->button31->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button31->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->button31->Location = System::Drawing::Point(143, 327);
			this->button31->Name = L"button31";
			this->button31->Size = System::Drawing::Size(64, 44);
			this->button31->TabIndex = 3;
			this->button31->Text = L"CE";
			this->button31->UseVisualStyleBackColor = false;
			this->button31->Click += gcnew System::EventHandler(this, &CalUI::clickCE);
			// 
			// bntChangeSign
			// 
			this->bntChangeSign->BackColor = System::Drawing::Color::LightGray;
			this->bntChangeSign->FlatAppearance->BorderSize = 0;
			this->bntChangeSign->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntChangeSign->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntChangeSign->Location = System::Drawing::Point(143, 527);
			this->bntChangeSign->Name = L"bntChangeSign";
			this->bntChangeSign->Size = System::Drawing::Size(64, 44);
			this->bntChangeSign->TabIndex = 2;
			this->bntChangeSign->Text = L"+/-";
			this->bntChangeSign->UseVisualStyleBackColor = false;
			this->bntChangeSign->Click += gcnew System::EventHandler(this, &CalUI::clickUnaryOperation);
			// 
			// bntRol
			// 
			this->bntRol->BackColor = System::Drawing::Color::LightGray;
			this->bntRol->FlatAppearance->BorderSize = 0;
			this->bntRol->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntRol->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntRol->Location = System::Drawing::Point(3, 277);
			this->bntRol->Name = L"bntRol";
			this->bntRol->Size = System::Drawing::Size(64, 44);
			this->bntRol->TabIndex = 0;
			this->bntRol->Text = L"RoL";
			this->bntRol->UseVisualStyleBackColor = false;
			this->bntRol->Click += gcnew System::EventHandler(this, &CalUI::clickBinaryOperators);
			// 
			// bntRor
			// 
			this->bntRor->BackColor = System::Drawing::Color::LightGray;
			this->bntRor->FlatAppearance->BorderSize = 0;
			this->bntRor->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntRor->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntRor->Location = System::Drawing::Point(73, 277);
			this->bntRor->Name = L"bntRor";
			this->bntRor->Size = System::Drawing::Size(64, 44);
			this->bntRor->TabIndex = 1;
			this->bntRor->Text = L"RoR";
			this->bntRor->UseVisualStyleBackColor = false;
			this->bntRor->Click += gcnew System::EventHandler(this, &CalUI::clickBinaryOperators);
			// 
			// bntOr
			// 
			this->bntOr->BackColor = System::Drawing::Color::LightGray;
			this->bntOr->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->bntOr->FlatAppearance->BorderSize = 0;
			this->bntOr->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->bntOr->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntOr->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntOr->Location = System::Drawing::Point(143, 277);
			this->bntOr->Name = L"bntOr";
			this->bntOr->Size = System::Drawing::Size(64, 44);
			this->bntOr->TabIndex = 2;
			this->bntOr->Text = L"Or";
			this->bntOr->UseVisualStyleBackColor = false;
			this->bntOr->Click += gcnew System::EventHandler(this, &CalUI::clickBinaryOperators);
			// 
			// bntXor
			// 
			this->bntXor->BackColor = System::Drawing::Color::LightGray;
			this->bntXor->FlatAppearance->BorderSize = 0;
			this->bntXor->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntXor->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntXor->Location = System::Drawing::Point(214, 277);
			this->bntXor->Name = L"bntXor";
			this->bntXor->Size = System::Drawing::Size(64, 44);
			this->bntXor->TabIndex = 3;
			this->bntXor->Text = L"Xor";
			this->bntXor->UseVisualStyleBackColor = false;
			this->bntXor->Click += gcnew System::EventHandler(this, &CalUI::clickBinaryOperators);
			// 
			// bntNot
			// 
			this->bntNot->BackColor = System::Drawing::Color::LightGray;
			this->bntNot->FlatAppearance->BorderSize = 0;
			this->bntNot->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntNot->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntNot->Location = System::Drawing::Point(284, 277);
			this->bntNot->Name = L"bntNot";
			this->bntNot->Size = System::Drawing::Size(64, 44);
			this->bntNot->TabIndex = 4;
			this->bntNot->Text = L"Not";
			this->bntNot->UseVisualStyleBackColor = false;
			this->bntNot->Click += gcnew System::EventHandler(this, &CalUI::clickUnaryOperation);
			// 
			// bntAnd
			// 
			this->bntAnd->BackColor = System::Drawing::Color::LightGray;
			this->bntAnd->FlatAppearance->BorderSize = 0;
			this->bntAnd->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntAnd->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntAnd->Location = System::Drawing::Point(354, 277);
			this->bntAnd->Name = L"bntAnd";
			this->bntAnd->Size = System::Drawing::Size(64, 44);
			this->bntAnd->TabIndex = 5;
			this->bntAnd->Text = L"And";
			this->bntAnd->UseVisualStyleBackColor = false;
			this->bntAnd->Click += gcnew System::EventHandler(this, &CalUI::clickBinaryOperators);
			// 
			// bntLsh
			// 
			this->bntLsh->BackColor = System::Drawing::Color::LightGray;
			this->bntLsh->FlatAppearance->BorderSize = 0;
			this->bntLsh->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntLsh->Font = (gcnew System::Drawing::Font(L"Arial", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntLsh->Location = System::Drawing::Point(3, 327);
			this->bntLsh->Name = L"bntLsh";
			this->bntLsh->Size = System::Drawing::Size(31, 44);
			this->bntLsh->TabIndex = 0;
			this->bntLsh->Text = L"Lsh";
			this->bntLsh->UseVisualStyleBackColor = false;
			this->bntLsh->Click += gcnew System::EventHandler(this, &CalUI::clickBinaryOperators);
			// 
			// lableHistory
			// 
			this->lableHistory->AutoSize = true;
			this->lableHistory->Location = System::Drawing::Point(12, 10);
			this->lableHistory->Name = L"lableHistory";
			this->lableHistory->Size = System::Drawing::Size(0, 13);
			this->lableHistory->TabIndex = 10;
			// 
			// bntRsh
			// 
			this->bntRsh->BackColor = System::Drawing::Color::LightGray;
			this->bntRsh->FlatAppearance->BorderSize = 0;
			this->bntRsh->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bntRsh->Font = (gcnew System::Drawing::Font(L"Arial", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->bntRsh->Location = System::Drawing::Point(35, 327);
			this->bntRsh->Name = L"bntRsh";
			this->bntRsh->Size = System::Drawing::Size(31, 44);
			this->bntRsh->TabIndex = 0;
			this->bntRsh->Text = L"Rsh";
			this->bntRsh->UseVisualStyleBackColor = false;
			this->bntRsh->Click += gcnew System::EventHandler(this, &CalUI::clickBinaryOperators);
			// 
			// display
			// 
			this->display->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->display->Location = System::Drawing::Point(3, 24);
			this->display->Name = L"display";
			this->display->Size = System::Drawing::Size(414, 103);
			this->display->TabIndex = 6;
			this->display->Text = L"0";
			this->display->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// CalUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(421, 583);
			this->Controls->Add(this->lableHistory);
			this->Controls->Add(this->displayBIN);
			this->Controls->Add(this->displayHEX);
			this->Controls->Add(this->displayDEC);
			this->Controls->Add(this->display);
			this->Controls->Add(this->bntEqual);
			this->Controls->Add(this->bntDot);
			this->Controls->Add(this->bntPlus);
			this->Controls->Add(this->bnt3);
			this->Controls->Add(this->bntMinus);
			this->Controls->Add(this->bnt6);
			this->Controls->Add(this->bnt0);
			this->Controls->Add(this->bntAnd);
			this->Controls->Add(this->bntMultiply);
			this->Controls->Add(this->bntNot);
			this->Controls->Add(this->bnt2);
			this->Controls->Add(this->bnt9);
			this->Controls->Add(this->bnt5);
			this->Controls->Add(this->bntChangeSign);
			this->Controls->Add(this->bntMod);
			this->Controls->Add(this->bntDivison);
			this->Controls->Add(this->bntXor);
			this->Controls->Add(this->bnt1);
			this->Controls->Add(this->bnt8);
			this->Controls->Add(this->bnt4);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->bntOr);
			this->Controls->Add(this->bntF);
			this->Controls->Add(this->bnt7);
			this->Controls->Add(this->bntD);
			this->Controls->Add(this->bntFloatMode);
			this->Controls->Add(this->button31);
			this->Controls->Add(this->bntC);
			this->Controls->Add(this->bntRor);
			this->Controls->Add(this->bntE);
			this->Controls->Add(this->bntB);
			this->Controls->Add(this->bntC_);
			this->Controls->Add(this->bntRsh);
			this->Controls->Add(this->bntLsh);
			this->Controls->Add(this->bntRol);
			this->Controls->Add(this->bntBIN);
			this->Controls->Add(this->bntA);
			this->Controls->Add(this->bntHEX);
			this->Controls->Add(this->bntDEC);
			this->Name = L"CalUI";
			this->Text = L"CalUI";
			this->Load += gcnew System::EventHandler(this, &CalUI::CalUI_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private:
	bool floatMode = false;
	String^ oper = "";
	bool isEnd = false; // Sau khi nhấn dấu bằng thì phép tính sẽ kết thúc
	int mode = DEC_MODE;
	BinaryNumber *_hisNum = new BinaryNumber();
	BinaryNumber *_currNum = new BinaryNumber();

private:
	System::Void CalUI_Load(System::Object^  sender, System::EventArgs^  e);

	System::Void bnt_FloatMode_Click(System::Object^  sender, System::EventArgs^  e);

	//Nhóm hàm chuyển đổi từ só nhị phân sang chuổi String^
	BinaryNumber convertToBinary(String^ s);
	String^ convertBinaryToCLIString(BinaryNumber a);
	std::string cliStringToString(String^ s);
	static String^ stringToCliString(std::string s);

	String^ getHistory(); // Lấy số đã tính toán ở góc trái màn hình
	void updateDataType(); //Tính toán lại các kiểu số
	void updateDisplayNumber();//Cập nhật số ở màn hình chính và số đã lưu
	void turnButtons(cli::array<Button^>^ a, bool onOff); // Bật/tắt các nút
	void updateButtonAvailability();//Update cho phép chỉ được nhấn một số nút nhất định ở mỗi chế độ

	System::Void clickNum(System::Object^  sender, System::EventArgs^  e); // Nhấn số nhập (0-9, A-F)

	System::Void bntClickDataType(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e); //Nhấn nút kiểu dữ liệu DEC, BIN, HEX

	// Nhấn các nút tính toán 2 ngôi và 1 ngôi
	System::Void clickBinaryOperators(System::Object^  sender, System::EventArgs^  e);
	System::Void clickUnaryOperation(System::Object^  sender, System::EventArgs^  e);

	//Nút bằng
	System::Void bntEqual_Click(System::Object^  sender, System::EventArgs^  e);

	//Các nút xóa
	System::Void clickC(System::Object^  sender, System::EventArgs^  e);
	System::Void clickBackSlash(System::Object^  sender, System::EventArgs^  e);
	System::Void clickCE(System::Object^  sender, System::EventArgs^  e);
};
}
