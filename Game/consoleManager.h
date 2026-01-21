#include <iostream>
#include <string>

using namespace std;

void Pause(bool needText);
void printSlowly(const string& text, bool needPause);
void printSlowly(const string& text, double charsPerSecond, bool needPause);
void printSlowly(const string& text, double charsPerSecond, bool needPause, int color);
void ShowName(std::string name);
void ClearScreen();
void ChangeDefaulSpeed(double speed);
