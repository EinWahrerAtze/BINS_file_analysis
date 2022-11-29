//
//  main.cpp
//  BINS_file_analysis_3.0
//
//  Created by Den Fedorov on 25.11.2022.
//

#if defined(_WIN32)
#include <Windows.h>
#endif
#include "interaction.h"

int main(int argc, const char * argv[])
{
#if defined(_WIN32)
	//HWND console {GetConsoleWindow()};
	//RECT r {};
	//GetWindowRect(console, &r);
	//MoveWindow(console, r.left, r.top, 1000, 500, TRUE);
	SetConsoleTitleA("BINS_file_analysis 3.0");
	SetConsoleCP(1251);
	SetConsoleOutputCP(65001);
#endif
	FL::Interaction interaction;
	interaction.run();
	return 0;
}