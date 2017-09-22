#include "console.h"

Console::Console()
{
}

//Used to easily fill CHAR_INFO arrays
void Console::ConvertString(const char * text, CHAR_INFO * result, int hexAttribute)
{
	wchar_t* converted = new wchar_t[strlen(text)];
	MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text, strlen(text) * sizeof(char), converted, strlen(text));
	for (int i = 0; i < strlen(text); i++)
	{
		result[i].Char.UnicodeChar = text[i];
		result[i].Attributes = hexAttribute;
	}
	delete[]converted;
}

int Console::Initialize(vec2 screen, const char* title)
{
	//Get Handle
	hConsole = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle(title);

	screenSize.Left = 0;
	screenSize.Right = screen.x - 1;
	screenSize.Top = 0;
	screenSize.Bottom = screen.y - 1;

	//Resize screen buffer
	SetConsoleWindowInfo(hConsole, true, &screenSize);
	SetConsoleScreenBufferSize(hConsole, screen.coord());

	hConsoleBack = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleWindowInfo(hConsoleBack, true, &screenSize);
	SetConsoleScreenBufferSize(hConsoleBack, screen.coord());

	return 0;
}

void Console::Print(const char* text, vec2 position, vec2 artsize, int hexColour)
{
	convString = new CHAR_INFO[strlen(text)];
	ConvertString(text, convString, hexColour);
	SMALL_RECT frame = screenSize;
	frame.Right = position.x + artsize.x;
	frame.Left = position.x;
	frame.Bottom = position.y + artsize.y;
	frame.Top = position.y;
	WriteConsoleOutput(hConsoleBack, convString, artsize.coord(), { 0,0 }, &frame);
	delete[] convString;
}

void Console::Print(CHAR_INFO* text, vec2 position, vec2 artsize)
{
	SMALL_RECT frame = screenSize;
	frame.Right = position.x + artsize.x;
	frame.Left = position.x;
	frame.Bottom = position.y + artsize.y;
	frame.Top = position.y;
	WriteConsoleOutput(hConsoleBack, text, artsize.coord(), { 0,0 }, &frame);
}

void Console::PrintCenter(const char* text, vec2 position, vec2 artsize, int hexColour)
{
	int left = position.x + artsize.x / 2;
	int top = position.y + artsize.y / 2;

	vec2 np(left, top);

	Print(text, np, artsize, hexColour);
}

void Console::PrintCenter(CHAR_INFO* text, vec2 position, vec2 artsize)
{
	int left = position.x + artsize.x / 2;
	int top = position.y + artsize.y / 2;

	vec2 np(left, top);

	Print(text, np, artsize);
}

void Console::Clear()
{
	COORD coordScreen = { 0, 0 };    // home for the cursor
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	// Get the number of character cells in the current buffer. 

	GetConsoleScreenBufferInfo(hConsoleBack, &csbi);

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// Fill the entire screen with blanks.

	FillConsoleOutputCharacter(hConsoleBack, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten);
	FillConsoleOutputAttribute(hConsoleBack, 0, dwConSize, coordScreen, &cCharsWritten);
}

void Console::Draw()
{
	SetConsoleActiveScreenBuffer(hConsoleBack);
	HANDLE temp = hConsoleBack;
	hConsoleBack = hConsole;
	hConsole = temp;
	Clear();
}