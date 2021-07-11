#include <iostream>
#include <iomanip> //std::setw
#include <fstream>
#include <string>
#include <windows.h>

#include "Tamagotchi.h"

using std::string;
using std::cout;
using std::endl;

void PrintMenu()
{
	cout << "\n\
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ \n\
@                              @ \n\
@ Hello! So, now I am your pet.@ \n\
@ Try to take good care of me. @ \n\
@   Then we will have fun !    @ \n\
@ Choose what we will do       @ \n\
@       and enter the number : @ \n\
@           1. Feed            @ \n\
@           2. Put to bed      @ \n\
@           3. Play            @ \n\
@ If you want to complete      @ \n\
@       the game, enter 'q'.   @ \n\
@                              @ \n\
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ \n";
}

void ClearScreen()
{
	//from https://stackoverflow.com/questions/10615042/how-to-update-refresh-console-screen

	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void PrintHeader(string pic)
{
	/*-------------------------------------------------------Header start*/
	string title = "< MY TAMAGOTCHI GAME >"; // Заголовок игры

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 32; j++)
			cout << '@';
		cout << std::endl;
	}

	cout << "@";
	for (int i = 0; i < 32 - 2; i++)
		cout << ' ';
	cout << "@\n";

	size_t offset_left = (32 - title.size()) / 2; // Для печати заголовка по центру
	/*Title Start*/
	cout << '@';
	for (int i = 0; i < offset_left - 1; i++)
		cout << ' ';
	cout << title;
	for (int i = 0; i < offset_left - 1; i++)
		cout << ' ';
	cout << "@\n";
	/*Title End*/

	cout << "@";
	for (int i = 0; i < 32 - 2; i++)
		cout << ' ';
	cout << "@\n";

	cout << pic;
	for (int i = 0; i < 32; i++)
		cout << "@";
	/*-------------------------------------------------------Header End*/

}

void PrintIndicators(int health, int hungry, int tiredness)
{
	cout << "\n";
	for (int i = 0; i < 32; i++)
		cout << "@";
	cout << "\n@ HEALTH |" << "  HUNGRY |" << " TIREDNESS @" << "\n";
	for (int i = 0; i < 32; i++)
		cout << '-';
	cout << "\n@   " << std::setw(2) << health << "   |   " << std::setw(2)
		<< hungry << "    |     " << std::setw(2) << tiredness << "    @\n";

	for (int i = 0; i < 32; i++)
		cout << "@";
}

string ReadPicture()
{
	std::ifstream pet("ascii-art.txt");
	string pic, line;

	while (getline(pet, line))
	{
		pic = pic + line + "\n";
	}
	return pic;
}

int main()
{
	Tamagotchi pet;
	string picture = ReadPicture();
	string message; // от питомца
	string entered; // от пользователя

	while (pet.IsAlive())
	{
		PrintHeader(picture);
		PrintMenu();
		PrintIndicators(pet.GetHealth(), pet.GetHungry(), pet.GetTiredness());
		
		message = pet.GetMsg();
		if (message.size() > 0) cout << "\n\n@ PET SAYS: \n" << message << endl;

		cout << "\n\n@ YOUR ACTION: ";
		std::cin >> entered;
		if (entered == "1")
			pet.Feed();
		else if (entered == "2")
			pet.Sleep();
		else if (entered == "3")
			pet.Play();
		else if (entered == "q")
			break;

		ClearScreen();
	}

	ClearScreen();
	PrintHeader(picture);
	PrintIndicators(pet.GetHealth(), pet.GetHungry(), pet.GetTiredness());
	message = pet.GetMsg();
	if(message.size() > 0)	cout << "\n\n@ " << message << "\n\n\n";
	else cout << "\n\n@ The game was stopped. Goodbye!\n\n\n";

	cout << "@ Enter any key to exit..."; std::cin >> entered;

	return 0;
}