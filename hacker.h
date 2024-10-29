#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <windows.h>
using namespace std;

#define KB_UP 72
#define KB_DOWN 80
#define KB_LEFT 75
#define KB_RIGHT 77
#define KB_ESCAPE 27

vector<vector<int>> generateMaze(int s, int d, double t);
vector<vector<int>> generateConsoles(vector<vector<int>> maze);
void displayMaze(vector<vector<int>> maze);
void setPos(int newX, int newY, int oldX, int oldY, int wire);
void setPos(int newX, int newY);
void navigateMaze(vector<vector<int>> maze);
void navigateMaze(vector<vector<int>> maze, int x, int y);
void navigate(vector<vector<int>> maze, int x, int y);
void consoleGame();
void displayConsoleGame(vector<vector<vector<string>>> puzzle, vector<vector<bool>> select);
