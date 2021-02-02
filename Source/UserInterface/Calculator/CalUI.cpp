#include "CalUI.h"

int main()
{
	System::Windows::Forms::Application::Run(gcnew Calculator::CalUI());
	return 0;
}

using namespace Calculator;

System::Void CalUI::CalUI_Load(System::Object^  sender, System::EventArgs^  e)
{
	bntDEC->BackColor = Color::Gray;
	updateButtonAvailability();
}
System::Void CalUI::bnt_FloatMode_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (floatMode)
	{
		floatMode = false;
		bntFloatMode->BackColor = Color::LightGray;
		displayHEX->Visible = true;
	}
	else
	{
		floatMode = true;
		bntFloatMode->BackColor = Color::Gray;
		displayHEX->Visible = false;
	}

	clickC(sender, e);
	updateButtonAvailability();
}

BinaryNumber CalUI::convertToBinary(String^ s)
{
	std::string st = cliStringToString(s);
	return BinaryNumber::fromStringtoBin(st, mode, floatMode);
}
String^ CalUI::getHistory()
{
	String^ tempHistory = lableHistory->Text;
	if (tempHistory == "")
		return "0";
	if (tempHistory->Length > 1)
	{
		tempHistory = tempHistory->Substring(0, tempHistory->IndexOf(' '));
	}
	return tempHistory;
}

String^ CalUI::convertBinaryToCLIString(BinaryNumber a)
{
	std::string temp = a.binaryToString(mode);
	return stringToCliString(temp);
}
std::string CalUI::cliStringToString(String^ s)
{
	return msclr::interop::marshal_as<std::string>(s);
}
String^ CalUI::stringToCliString(std::string s)
{
	return msclr::interop::marshal_as<String^>(s);
}

void CalUI::updateDataType()
{
	*_currNum = BinaryNumber::fromStringtoBin(cliStringToString(display->Text), mode, floatMode);
	displayDEC->Text = stringToCliString(_currNum->binaryToString(DEC_MODE));
	if (floatMode == false)
		displayHEX->Text = stringToCliString(_currNum->binaryToString(HEX_MODE));
	displayBIN->Text = stringToCliString(_currNum->binaryToString(BIN_MODE));
}
void CalUI::updateDisplayNumber()
{
	String^ disp;
	String^ historyDisp;

	disp = stringToCliString(_currNum->binaryToString(mode));
	historyDisp = stringToCliString(_hisNum->binaryToString(mode));

	display->Text = disp;
	lableHistory->Text = historyDisp + " " + oper;
}
void CalUI::turnButtons(cli::array<Button^>^ a, bool onOff)
{
	for each (Button^ bnt in a)
	{
		bnt->Enabled = onOff;
		if (onOff == true)
		{
			bnt->BackColor = Color::LightGray;
		}
		else
		{
			bnt->BackColor = Color::FromName("ControlLight");
		}
	}
}
void CalUI::updateButtonAvailability()
{
	cli::array<Button^>^ characterButtons = gcnew cli::array<Button^>{bntA, bntB, bntC_, bntD, bntE, bntF};
	cli::array<Button^>^ nonBinaryNumberbuttons = gcnew cli::array<Button^>{bnt2, bnt3, bnt4, bnt5, bnt6, bnt7, bnt8, bnt9};
	cli::array<Button^>^ nonStandardOperators = gcnew cli::array<Button^>{bntRol, bntRor, bntMod, bntAnd, bntXor, bntOr, bntNot, bntRsh, bntLsh};

	turnButtons(nonBinaryNumberbuttons, TURN_ON);
	turnButtons(characterButtons, TURN_ON);
	turnButtons(nonStandardOperators, TURN_ON);
	bntDot->Enabled = true;
	bntHEX->Enabled = true;

	if (mode == DEC_MODE)
	{
		turnButtons(characterButtons, TURN_OFF);
	}
	else if (mode == BIN_MODE)
	{
		turnButtons(characterButtons, TURN_OFF);
		turnButtons(nonBinaryNumberbuttons, TURN_OFF);
	}
	else if (mode == HEX_MODE)
	{

	}

	if (floatMode)
	{
		bntHEX->Enabled = false;
		turnButtons(nonStandardOperators, TURN_OFF);
		turnButtons(characterButtons, TURN_OFF);
	}
	else
	{
		bntDot->Enabled = false;
	}
}

System::Void CalUI::clickNum(System::Object^  sender, System::EventArgs^  e) {
	if (isEnd)
	{
		clickC(sender, e); // Nếu sau khi bấm nút bằng rồi thì số cũ sẽ được xóa đi
		isEnd = false;
	}

	Button ^ num = safe_cast<Button^>(sender);

	if (isStringZero(cliStringToString(display->Text)) && num->Text != ".")
	{
		display->Text = num->Text;
	}
	else
	{
		if (num->Text == "." && display->Text->Contains("."))
			return;
		display->Text = display->Text + num->Text;
	}

	updateDataType();
}
System::Void CalUI::clickCE(System::Object^  sender, System::EventArgs^  e) {
	if (isEnd)
	{
		clickC(sender, e);
	}
	else
	{
		display->Text = "0";
		updateDataType();
	}
}
System::Void CalUI::bntClickDataType(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	Button^ bnt = safe_cast < Button^>(sender);

	bntDEC->BackColor = Color::LightGray;
	bntHEX->BackColor = Color::LightGray;
	bntBIN->BackColor = Color::LightGray;
	bnt->BackColor = Color::Gray;

	String^ type = bnt->Text;

	if (type == bntDEC->Text)
	{
		mode = DEC_MODE;
	}
	else if (type == bntHEX->Text)
	{
		mode = HEX_MODE;
	}
	else if (type == bntBIN->Text)
	{
		mode = BIN_MODE;
	}

	updateDisplayNumber();
	updateButtonAvailability();
}
System::Void CalUI::clickBinaryOperators(System::Object^  sender, System::EventArgs^  e) {
	if (isEnd)
		isEnd = false;

	display->Text = "0";
	try{
		*_hisNum = CoreCalculator::binaryCalculate(cliStringToString(oper), *_hisNum, *_currNum);
	}
	catch (const std::invalid_argument& e)
	{
		display->Text = "Math ERROR!";
		isEnd = true;
	}

	Button^ bnt = safe_cast < Button^>(sender);
	oper = bnt->Text;


	lableHistory->Text = convertBinaryToCLIString(*_hisNum) + " " + oper;
}



System::Void CalUI::bntEqual_Click(System::Object^  sender, System::EventArgs^  e) {
	display->TextAlign = ContentAlignment::TopRight;
	try{
		*_currNum = CoreCalculator::binaryCalculate(cliStringToString(oper), *_hisNum, *_currNum);
		display->Text = convertBinaryToCLIString(*_currNum);
		lableHistory->Text = "";
		*_hisNum = BinaryNumber();
		oper = "";
		updateDataType();
	}
	catch (const std::invalid_argument& e)
	{
		display->Text = "Math ERROR!";
		isEnd = true;
	}

	isEnd = true;
}
System::Void CalUI::clickC(System::Object^  sender, System::EventArgs^  e)
{
	*_hisNum = BinaryNumber();
	oper = "";
	lableHistory->Text = "";
	display->Text = "0";
	updateDataType();
}
System::Void CalUI::clickUnaryOperation(System::Object^  sender, System::EventArgs^  e) {
	Button^ bnt = safe_cast < Button^>(sender);
	String^ o = bnt->Text;

	*_currNum = CoreCalculator::unaryCalculate(cliStringToString(o), *_currNum);
	display->Text = convertBinaryToCLIString(*_currNum);
	updateDataType();
}
System::Void CalUI::clickBackSlash(System::Object^  sender, System::EventArgs^  e) {
	int n = display->Text->Length;
	if (n > 1)
	{
		display->Text = display->Text->Remove(n - 1);
	}
	else
		display->Text = "0";
	updateDataType();
}