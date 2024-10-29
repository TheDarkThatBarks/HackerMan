#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <random>
#include <time.h>
#include "hacker.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int size, diff, rO;
double threshold;

vector<vector<int>> generateMaze(int s, int d, double t) {
	size = s;
	diff = d;
	threshold = t;
	rO = (((size + 1) / 2) * ((size + 1) / 2));
	srand(time(NULL));
	vector<vector<int>> maze(size, vector<int>(size, 0));
	int dir = 0, x = 0, y = size / 2, r, dx, dy;
	r = rO - 1;
	maze[x][y] = 1;
	while (r > 0) {
		dir = rand() % 4;
		if ((dir == 0) && (x - 2 >= 0)) {
			dx = -2;
			dy = 0;
		} else if ((dir == 1) && (y + 2 < size)) {
			dx = 0;
			dy = 2;
		} else if ((dir == 2) && (x + 2 < size)) {
			dx = 2;
			dy = 0;
		} else if ((dir == 3) && (y - 2 >= 0)) {
			dx = 0;
			dy = -2;
		} else {
			dx = 0;
			dy = 0;
		}
		if (maze[x + dx][y + dy] == 0) {
			maze[x + dx][y + dy] = 1;
			maze[x + (dx / 2)][y + (dy / 2)] = 1;
			r--;
		}
		x += dx;
		y += dy;
	}
	maze = generateConsoles(maze);
	return maze;
}

vector<vector<int>> generateConsoles(vector<vector<int>> maze) {
	int x = 0, y = size / 2, r = rO - 1, tempX, tempY, tempYL, tempYR, c;
	vector<bool> checks(diff, true);
	for (int i = 2; x + i < size; i += 2) {
		for (int j = 0; j <= i; j += 2) {
			tempYL = 0;
			tempYR = 0;
			if (y - (i - j) < size) {
				tempYL = y - (i - j);
				r--;
			}
			if (y + (i - j) < size) {
				tempYR = y + (i - j);
				r--;
			}
			tempX = x + j;
			tempY = tempYL;
			for (int k = 0; k < 2; k++) {
				if (k == 1)
					tempY = tempYR;
				c = 0;
				if ((tempX - 1 >= 0) && (maze[tempX - 1][tempY] == 0))
					c++;
				if ((tempY + 1 < size) && (maze[tempX][tempY + 1] == 0))
					c++;
				if ((tempX + 1 < size) && (maze[tempX + 1][tempY] == 0))
					c++;
				if ((tempY - 1 >= 0) && (maze[tempX][tempY - 1] == 0))
					c++;
				if ((c == 3) && (maze[tempX][tempY] != 0)) {
					for (int l = diff - 1; l >= 0; l--) {
						if (checks[l] && (((double) r) / rO <= threshold * ((double) (l + 1) / diff))) {
							maze[tempX][tempY] = 2;
							checks[l] = false;
						}
					}
				}
			}
		}
	}
	return maze;
}

void displayMaze(vector<vector<int>> maze) {
	SetConsoleTextAttribute(hConsole, 7);
	SetConsoleCursorPosition(hConsole, {0, 0});
	for (int i = 0; i < 50; i++)
		cout << "                                                                                                                                                                                                        " << endl;
	SetConsoleCursorPosition(hConsole, {0, 1});
	int height = size;
	int width = size;
	cout << "  ";
	for (int i = 1; i <= (width * 2) + 4; i++) {
		if ((i >= width + 2) && (i <= width + 3)) {
			SetConsoleTextAttribute(hConsole, 7);
			cout << "|";
		} else {
			SetConsoleTextAttribute(hConsole, 255);
			cout << "-";
		}
	}
	cout << endl;
	for (int i = 0; i < size; i++) {
		SetConsoleTextAttribute(hConsole, 7);
		cout << "  ";
		SetConsoleTextAttribute(hConsole, 255);
		cout << "  ";
		vector<int> m = maze[i];
		for (int i = 0; i < m.size(); i++) {
			SetConsoleTextAttribute(hConsole, 7);
			if (m[i] == 0)  {
				SetConsoleTextAttribute(hConsole, 255);
				cout << "00";
			} else if (m[i] == 1) {
				SetConsoleTextAttribute(hConsole, 0);
				cout << "11";
			} else if (m[i] == 2) {
				SetConsoleTextAttribute(hConsole, 187);
				cout << "22";
			} else if (m[i] == 3) {
				cout << "||";
			} else if (m[i] == 4) {
				cout << "--";
			} else if (m[i] == 5) {
				cout << "++";
			}
		}
		SetConsoleTextAttribute(hConsole, 255);
		cout << "  " << endl;
	}
	SetConsoleTextAttribute(hConsole, 7);
	cout << "  ";
	SetConsoleTextAttribute(hConsole, 255);
	for (int i = 1; i <= (width * 2) + 4; i++)
		cout << "-";
}

void setPos(int newX, int newY, int oldX, int oldY, int wire) {
	SetConsoleCursorPosition(hConsole, {(newY * 2) + 4, newX + 2});
	SetConsoleTextAttribute(hConsole, 204);
	cout << "++";
	SetConsoleCursorPosition(hConsole, {(oldY * 2) + 4, oldX + 2});
	SetConsoleTextAttribute(hConsole, 7);
	if (wire == 0) {
		cout << "  ";
	} else if (wire == 1) {
		cout << "||";
	} else if (wire == 2) {
		cout << "--";
	} else if (wire == 3) {
		cout << "++";
	}
	SetConsoleCursorPosition(hConsole, {0, 0});
}

void setPos(int newX, int newY) {
	SetConsoleCursorPosition(hConsole, {(newY * 2) + 4, newX + 2});
	SetConsoleTextAttribute(hConsole, 204);
	cout << "++";
	SetConsoleTextAttribute(hConsole, 7);
	SetConsoleCursorPosition(hConsole, {0, 0});
}

void navigateMaze(vector<vector<int>> maze) {
	int kb = 0, x = 0, y = size / 2;
	SetConsoleCursorPosition(hConsole, {(y * 2) + 4, x + 1});
	SetConsoleTextAttribute(hConsole, 204);
	cout << "++";
	SetConsoleTextAttribute(hConsole, 7);
	SetConsoleCursorPosition(hConsole, {0, 0});
	while (kb != KB_DOWN) {
		if (kbhit())
			kb = getch();
	}
	SetConsoleCursorPosition(hConsole, {(y * 2) + 4, x + 1});
	cout << "||";
	SetConsoleCursorPosition(hConsole, {(y * 2) + 4, x + 2});
	SetConsoleTextAttribute(hConsole, 204);
	cout << "++";
	SetConsoleTextAttribute(hConsole, 7);
	SetConsoleCursorPosition(hConsole, {0, 0});
	navigate(maze, x, y);
}

void navigateMaze(vector<vector<int>> maze, int x, int y) {
	setPos(x, y);
	navigate(maze, x, y);
}

void navigate(vector<vector<int>> maze, int x, int y) {
	int kb = 0, tempX, tempY, wire = 0;
	bool done;
	while (kb != -1) {
		if (diff == 0) {
			Sleep(500);
			while ((x != 0) || (y != size / 2)) {
				tempX = x;
				tempY = y;
				if ((x - 1 >= 0) && ((maze[x - 1][y] == 3) || (maze[x - 1][y] == 4) || (maze[x - 1][y] == 5))) {
					tempX = x - 1;
					tempY = y;
				} else if ((y + 1 < size) && ((maze[x][y + 1] == 3) || (maze[x][y + 1] == 4) || (maze[x][y + 1] == 5))) {
					tempX = x;
					tempY = y + 1;
				} else if ((x + 1 < size) && ((maze[x + 1][y] == 3) || (maze[x + 1][y] == 4) || (maze[x + 1][y] == 5))) {
					tempX = x + 1;
					tempY = y;
				} else if ((y - 1 >= 0) && ((maze[x][y - 1] == 3) || (maze[x][y - 1] == 4) || (maze[x][y - 1] == 5))) {
					tempX = x;
					tempY = y - 1;
				}
				setPos(tempX, tempY, x, y, 0);
				maze[x][y] = 1;
				x = tempX;
				y = tempY;
				Sleep(65);
			}
			SetConsoleCursorPosition(hConsole, {(y * 2) + 4, x + 1});
			SetConsoleTextAttribute(hConsole, 204);
			cout << "++";
			SetConsoleTextAttribute(hConsole, 7);
			SetConsoleCursorPosition(hConsole, {(y * 2) + 4, x + 2});
			cout << "  ";
			SetConsoleCursorPosition(hConsole, {0, 0});
			Sleep(250);
			SetConsoleCursorPosition(hConsole, {(y * 2) + 4, x + 1});
			cout << "  ";
			SetConsoleCursorPosition(hConsole, {0, 0});
			kb = -1;
		}
		if (kbhit()) {
			kb = getch();
			tempX = x;
			tempY = y;
			wire = 0;
			done = false;
			if ((kb == KB_UP) && (x - 1 >= 0) && (maze[x - 1][y] != 0)) {
				tempX = x - 1;
				tempY = y;
				if (maze[tempX][tempY] != 3)
					wire = 1;
				done = true;
			} else if ((kb == KB_RIGHT) && (y + 1 < size) && (maze[x][y + 1] != 0)) {
				tempX = x;
				tempY = y + 1;
				if (maze[tempX][tempY] != 4)
					wire = 2;
				done = true;
			} else if ((kb == KB_DOWN) && (x + 1 < size) && (maze[x + 1][y] != 0)) {
				tempX = x + 1;
				tempY = y;
				if (maze[tempX][tempY] != 3)
					wire = 1;
				done = true;
			} else if ((kb == KB_LEFT) && (y - 1 >= 0) && (maze[x][y - 1] != 0)) {
				tempX = x;
				tempY = y - 1;
				if (maze[tempX][tempY] != 4)
					wire = 2;
				done = true;
			}
			if (wire != 0) {
				if (maze[x][y] == 1) {
					maze[x][y] = wire + 2;
				} else if (maze[x][y] != wire + 2) {
					maze[x][y] = 5;
					wire = 3;
				}
			} else {
				maze[x][y] = 1;
			}
			if (done)
				setPos(tempX, tempY, x, y, wire);
			if (maze[tempX][tempY] == 2) {
				maze[tempX][tempY] = 1;
				Sleep(250);
				consoleGame();
				diff--;
				displayMaze(maze);
				navigateMaze(maze, tempX, tempY);
				kb = -1;
			}
			x = tempX;
			y = tempY;
		}
	}
	Sleep(250);
}

void consoleGame() {
	SetConsoleTextAttribute(hConsole, 7);
	for (int i = 0; i < 50; i++) {
		SetConsoleCursorPosition(hConsole, {0, i});
		cout << "                                                                                                                                                                                                        " << endl;
	}
	SetConsoleCursorPosition(hConsole, {0, 6});
	vector<vector<vector<string>>> puzzleO(3, vector<vector<string>>(3, vector<string>(10, "")));
	int numPuzzles = 2;
	ifstream puzzleFile("puzzle" + to_string(rand() % numPuzzles + 1) + ".txt");
	string line;
	int i = 0, k = 0;
	if (puzzleFile.is_open()) {
		while (getline(puzzleFile, line)) {
			if (k == 9) {
				k = 0;
				i++;
				continue;
			}
			puzzleO[i][0][k] = line.substr(0, 20);
			puzzleO[i][1][k] = line.substr(22, 20);
			puzzleO[i][2][k] = line.substr(44, 20);
			k++;
		}
	}
	puzzleFile.close();
	srand(time(NULL));
	random_device rd;
	vector<vector<vector<string>>> puzzle = puzzleO;
	default_random_engine dre(rand() % rand());
	array<int, 3> arr = {0, 1, 2};
	array<int, 3> arr2 = {0, 1, 2};
	shuffle(arr.begin(), arr.end(), dre);
	vector<vector< vector<string>>> puzzleTemp = puzzle;
	puzzleTemp[arr[0]] = puzzle[0];
	puzzleTemp[arr[1]] = puzzle[1];
	puzzleTemp[arr[2]] = puzzle[2];
	for (int i = 0; i < 3; i++) {
		shuffle(arr2.begin(), arr2.end(), dre);
		for (int j = 0; j < 3; j++)
			puzzleTemp[arr[i]][arr2[j]] = puzzle[i][j];
		if ((puzzle[i] == puzzleTemp[0]) || (puzzle[i] == puzzleTemp[1]) || (puzzle[i] == puzzleTemp[2]))
			i--;
	}
	puzzle = puzzleTemp;
	int kb = 0, x = 1, y = 1, x1 = -1, y1 = -1, tempX, tempY;
	bool done;
	vector<vector<bool>> select(3, vector<bool>(3, false));
	select[1][1] = true;
	while (puzzle != puzzleO) {
		displayConsoleGame(puzzle, select);
		done = false;
		while (!done) {
			if (kbhit()) {
				kb = getch();
				tempX = x;
				tempY = y;
				if ((kb == KB_UP) && (x - 1 >= 0)) {
					tempX = x - 1;
					tempY = y;
				} else if ((kb == KB_RIGHT) && (y + 1 < 3)) {
					tempX = x;
					tempY = y + 1;
				} else if ((kb == KB_DOWN) && (x + 1 < 3)) {
					tempX = x + 1;
					tempY = y;
				} else if ((kb == KB_LEFT) && (y - 1 >= 0)) {
					tempX = x;
					tempY = y - 1;
				} else if (kb == VK_SPACE) {
					if (x1 == -1) {
						x1 = x;
						y1 = y;
						select[x][y] = true;
					} else {
						vector<string> temp = puzzle[x][y];
						puzzle[x][y] = puzzle[x1][y1];
						puzzle[x1][y1] = temp;
						select[x1][y1] = false;
						x1 = -1;
						y1 = -1;
					}
				}
				if ((x != x1) || (y != y1))
					select[x][y] = false;
				select[tempX][tempY] = true;
				x = tempX;
				y = tempY;
				done = true;
			}
		}
	}
	select[x][y] = false;
	displayConsoleGame(puzzle, select);
	Sleep(500);
}

void displayConsoleGame(vector<vector<vector<string>>> puzzle, vector<vector<bool>> select) {
	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 10; k++) {
			cout << "  ";
			if (select[i][0]) {
				SetConsoleTextAttribute(hConsole, 255);
				if ((k == 0) || (k == 9)) {
					cout << "XXXXXXXXXXXXXXXXXXXX";
				} else {
					cout << "X";
					SetConsoleTextAttribute(hConsole, 7);
					cout << puzzle[i][0][k].substr(1, puzzle[i][0][k].length() - 2);
					SetConsoleTextAttribute(hConsole, 255);
					cout << "X";
				}
				SetConsoleTextAttribute(hConsole, 7);
			} else {
				if (k == 9) {
					cout << "                    ";
				} else {
					cout << puzzle[i][0][k];
				}
			}
			cout << "  ";
			if (select[i][1]) {
				SetConsoleTextAttribute(hConsole, 255);
				if ((k == 0) || (k == 9)) {
					cout << "XXXXXXXXXXXXXXXXXXXX";
				} else {
					cout << "X";
					SetConsoleTextAttribute(hConsole, 7);
					cout << puzzle[i][1][k].substr(1, puzzle[i][1][k].length() - 2);
					SetConsoleTextAttribute(hConsole, 255);
					cout << "X";
				}
				SetConsoleTextAttribute(hConsole, 7);
			} else {
				if (k == 9) {
					cout << "                    ";
				} else {
					cout << puzzle[i][1][k];
				}
			}
			cout << "  ";
			if (select[i][2]) {
				SetConsoleTextAttribute(hConsole, 255);
				if ((k == 0) || (k == 9)) {
					cout << "XXXXXXXXXXXXXXXXXXXX";
				} else {
					cout << "X";
					SetConsoleTextAttribute(hConsole, 7);
					cout << puzzle[i][2][k].substr(1, puzzle[i][2][k].length() - 2);
					SetConsoleTextAttribute(hConsole, 255);
					cout << "X";
				}
				SetConsoleTextAttribute(hConsole, 7);
			} else {
				if (k == 9) {
					cout << "                    ";
				} else {
					cout << puzzle[i][2][k];
				}
			}
			cout << endl;
		}
	}
	SetConsoleCursorPosition(hConsole, {0, 6});
}
