#ifndef SCANNER_H
#define SCANNER_H
#include<iostream>
#include<stdio.h>
#include<string>
#include<iostream>
#include<windows.h>   
#include<iomanip>

static HWND  hConWnd;
void displayPicture(int);
HWND BCX_Bitmap(char*, std::string, HWND = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
HWND GetConsoleWndHandle(void);
//void displayMessage();

void startScanner()
{
	system("cls");
	std::cout << "A wild Pokemon has appeared!\n";
	std::cout << "press <Enter> to start scanning the creature...\n";
	std::cin.get();


	displayPicture(1);
	//system("cls");
	//Sleep(5000);
	displayPicture(2);

	//std::cout << "press <Enter> to return to main menu...";
	//std::cin.get();
}


void displayPicture(int pictureNumber)
{
	hConWnd = GetConsoleWndHandle();
	std::string message1 = "\n\tscan complete...\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\npress <Enter> to display pokemon information...";  // 32 new lines
	std::string message2 = "text";
	if (hConWnd)
	{
		// select a bitmap file you have or use one of the files in the Windows folder
		// filename, handle, ID, horizontal offset, vertical offset, [width, height (0,0 auto-adjusts)]

		if (pictureNumber == 1)
		{
			BCX_Bitmap("test.bmp", message1, hConWnd, 123, 25, 50, 475, 475);
		}
		else
		{
			BCX_Bitmap("pikachuFull.bmp", message2, hConWnd, 123, 25, 50, 475, 475);
		}

		//getchar();  // wait
	}
}

//void displayMessage()
//{
//	std::cout << "\n\tscan complete...";
//	std::cout << "\n\n\n\n\n\n\n\n\n\n"; // 10 new lines
//	std::cout << "\n\n\n\n\n\n\n\n\n\n"; // 10 new lines
//	std::cout << "\n\n\n\n\n\n\n\n\n\n"; // 10 new lines
//	std::cout << "\n\n\n\n\n\n";  // 6 new lines
//	std::cout << "\npress<Enter> to display pokemon information...";
//	std::cin.get();
//}


// draw the bitmap
HWND BCX_Bitmap(char* Text, std::string displayText, HWND hWnd, int id, int X, int Y, int W, int H, int Res, int Style, int Exstyle)
{
	HWND pictureFrame;
	HBITMAP hBitmap;

	// set default style
	if (!Style) Style = WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE | SS_BITMAP | WS_TABSTOP;

	// form for the image
	pictureFrame = CreateWindowEx(Exstyle, "static", NULL, Style, X, Y, 0, 0, hWnd, (HMENU)id, GetModuleHandle(0), NULL);

	// Text contains filename
	hBitmap = (HBITMAP)LoadImage(0, Text, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	// auto-adjust width and height
	if (W || H) hBitmap = (HBITMAP)CopyImage(hBitmap, IMAGE_BITMAP, W, H, LR_COPYRETURNORG);
	SendMessage(pictureFrame, (UINT)STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
	if (W || H) SetWindowPos(pictureFrame, HWND_TOP, X, Y, W, H, SWP_DRAWFRAME);

	//displayMessage();
	if (displayText == "text")
	{
		//std::cout << " " << std::setw(8) << std::left << "setw = 8";
		std::cout << "\t\t\t\t\t\t Pikachu";
		std::cout << "\npress <Enter> to return to main menu...";
		std::cin.get();
	}
	else
	{
		system("cls");
		std::cout << "scanning...";
		Sleep(1000);
		system("cls");
		Sleep(600);
		std::cout << "scanning...";
		Sleep(1000);
		system("cls");
		Sleep(600);
		std::cout << "scanning...";
		Sleep(1000);
		system("cls");
		std::cout << displayText;
		std::cin.get();
	}

	DestroyWindow(pictureFrame);
	return pictureFrame;
}

// tricking Windows just a little ...
HWND GetConsoleWndHandle(void)
{

	HWND hConWnd;
	OSVERSIONINFO os;
	char szTempTitle[64], szClassName[128], szOriginalTitle[1024];
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	GetConsoleTitle(szOriginalTitle, sizeof(szOriginalTitle));
	sprintf_s(szTempTitle, "%u - %u", GetTickCount(), GetCurrentProcessId());
	SetConsoleTitle(szTempTitle);
	Sleep(40);

	hConWnd = FindWindow(NULL, szTempTitle);
	SetConsoleTitle(szOriginalTitle);

	return hConWnd;
}


#endif