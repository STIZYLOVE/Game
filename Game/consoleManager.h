#include <iostream>
#include <string>

using namespace std;

void Pause(bool needText);
void printSlowly(const string& text, bool needPause);
void printSlowly(const string& text, double charsPerSecond, bool needPause);
void printSlowly(const string& text, double charsPerSecond, bool needPause, int color);
void ShowName(string name);
void ClearScreen();
void ChangeDefaultSpeed(double speed);
