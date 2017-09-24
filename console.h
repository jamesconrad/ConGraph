#pragma once

#include <Windows.h>
#include "math.h"


//Colour specifier, to use multiple seperate each with a '|'
//Example	: Colour c = FG_CYAN | FG_INTENSITY | BG_RED
//			This will create a bright cyan text, with a dark red background
enum Colour
{
	FG_BLUE = 0x0001,
	FG_GREEN = 0x0002,
	FG_RED = 0x0004,
	FG_WHITE = 0x0001 | 0x0002 | 0x0004,
	FG_PURPLE = 0x0001 | 0x0004,
	FG_CYAN = 0x0001 | 0x0002,
	FG_YELLOW = 0x0002 | 0x0004,
	FG_INTENSITY = 0x0008,
	BG_BLUE = 0x0010,
	BG_GREEN = 0x0020,
	BG_RED = 0x0040,
	BG_WHITE = 0x0010 | 0x0020 | 0x0040,
	BG_PURPLE = 0x0010 | 0x0040,
	BG_CYAN = 0x0010 | 0x0020,
	BG_YELLOW = 0x0020 | 0x0040,
	BG_INTENSITY = 0x0080,
	UNDERSCORE = 0x8000
};

class Console
{
public:
	HANDLE hConsole;
	HANDLE hConsoleBack;

	//Empty constructor.
	Console();

	//Initialize, must be called after construction before class use
	//Screen is the size of the console in characters, Title will be the name of the window
	int Initialize(vec2 screen, const char* title);

	//Convers the char* text into a CHAR_INFO* result
	//Recomended for use on unchanging or constant ASCII "models" to save on execution time
	void ConvertString(const char * text, CHAR_INFO * result, int hexAttribute);

	//Prints a char string of text in the specificed location
	void Print(const char* text, vec2 position, vec2 artsize, int hexColour);
	
	//Prints a preformated CHAR_INFO string of text at the specified location
	void Print(CHAR_INFO* text, vec2 position, vec2 artsize);

	//Prints a char string of text centered on the position provided
	void PrintCenter(const char* text, vec2 position, vec2 artsize, int hexColour);

	//Prints a CHAR_INFO string of text resulted from ConvertString centered on the position provided
	void PrintCenter(CHAR_INFO* text, vec2 position, vec2 artsize);

	//Draws the render buffer to the console itself, must be done at the end of the Print commands
	void Draw();

	//Clears the back buffer, must be done before any Print commands each frame
	void Clear();
private:
	SMALL_RECT screenSize;
	CHAR_INFO* convString;
	wchar_t* wconverted;
};