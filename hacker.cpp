#include "hacker.h"

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
HWND window = GetConsoleWindow();
RECT r;

vector<string> options = {"Start Game", "Difficulty", "Quit"};
vector<string> diffs = {"Easy", "Medium", "Hard"};
int indexO = 0, indexD, sizeD = 17, diffD = 2;

void displayOptions() {
	SetConsoleCursorPosition(console, {0, 8});
	for (int i = 0; i < options.size(); i++)
		cout << "                                                                                                    ";
	SetConsoleCursorPosition(console, {0, 8});
	for (int i = 0; i < options.size(); i++) {
		cout << "   >> ";
		if (i == indexO) {
			SetConsoleTextAttribute(console, 240);
			cout << options[i];
			SetConsoleTextAttribute(console, 7);
		} else {
			cout << options[i];
		}
		cout << endl;
	}
	SetConsoleCursorPosition(console, {0, 0});
}

void displayDiffs() {
	SetConsoleCursorPosition(console, {0, 8});
	for (int i = 0; i < diffs.size(); i++)
		cout << "                                                                                                    ";
	SetConsoleCursorPosition(console, {0, 8});
	for (int i = 0; i < diffs.size(); i++) {
		cout << "   >> ";
		if (i == indexD) {
			SetConsoleTextAttribute(console, 240);
			cout << diffs[i];
			SetConsoleTextAttribute(console, 7);
		} else {
			cout << diffs[i];
		}
		cout << endl;
	}
	SetConsoleCursorPosition(console, {0, 0});
}

int main() {
	GetWindowRect(window, &r);
	MoveWindow(window, r.left, r.top, 1000, 800, TRUE);
	SetConsoleTitle("HackerMan");
	cout << endl << endl;
	cout << "   " << "|    |  " << "        " <<   "       " <<  "|     " <<  "        " <<  "        " <<  "|\\    /|  " << "        " <<   "      "  << endl;
	cout << "   " << "|    |  " << " __     " <<   " ____  " <<  "|  /  " <<  " ____   " <<  " ____   " <<  "| \\  / |  " << " __     " <<   " ____ "  << endl;
	cout << "   " << "|----|  " << "/  \\    " <<  "/      " <<  "|_/   " <<  "/____\\  " << "/    \\  " << "|  \\/  |  " << "/  \\    " <<  "|    \\" << endl;
	cout << "   " << "|    |  " << "|  |\\   " <<  "|      " <<  "| \\   " << "|       " <<  "|       " <<  "|      |  " <<  "|  |\\   " <<  "|    |"  << endl;
	cout << "   " << "|    |  " << "\\__/ \\  " << "\\____  " << "|  \\  " << "\\____   " << "|       " <<  "|      |  " <<  "\\__/ \\  " << "|    |"  << endl;
	cout << endl;
	cout << "   >> Press ENTER to begin . . .";
	cin.get();
	int kb = 0;
	displayOptions();
	while (true) {
		if (kbhit()) {
			kb = getch();
			if ((kb == KB_UP) && (indexO - 1 >= 0)) {
				indexO--;
			} else if ((kb == KB_DOWN) && (indexO + 1 < options.size())) {
				indexO++;
			} else if (kb == VK_SPACE) {
				Sleep(250);
				if (indexO == 0) {
					vector<vector<int>> maze = generateMaze(sizeD, diffD, 0.6);
					displayMaze(maze);
					navigateMaze(maze);
					SetConsoleTextAttribute(console, 7);
					SetConsoleCursorPosition(console, {0, 0});
					for (int i = 0; i < 50; i++)
						cout << "                                                                                                                                                                                                        " << endl;
					SetConsoleCursorPosition(console, {0, 0});
					main();
					//exit(0);
				} else if (indexO == 1) {
					indexD = 0;
					displayDiffs();
					while (true) {
						if (kbhit()) {
							kb = getch();
							if ((kb == KB_UP) && (indexD - 1 >= 0)) {
								indexD--;
							} else if ((kb == KB_DOWN) && (indexD + 1 < diffs.size())) {
								indexD++;
							} else if (kb == VK_SPACE) {
								Sleep(250);
								sizeD = 17 + (8 * indexD);
								diffD = 2 + indexD;
								break;
							}
							displayDiffs();
						}
					}
				} else if (indexO == 2) {
					exit(0);
				}
			}
			displayOptions();
		}
	}
}
