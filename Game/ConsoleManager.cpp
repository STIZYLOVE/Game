#include "consoleManager.h"
#include <fstream>
#include <chrono>
#include <thread>
#include <windows.h>
#include <conio.h>
#include <stdio.h>

using namespace std;

HANDLE hConsole;

double defaultCharsPerSecond = 30;

void Pause(bool needText)
{
    if (needText)
        cout << "Enter чтобы продолжить...";
    cin.get();
    cout << endl;
}

void printSlowly(const string& text, bool needPause)
{
    if (defaultCharsPerSecond <= 0) {
        cout << text;
        if (needPause) Pause(false);
        return;
    }

    auto delay = chrono::duration<double>(1.0 / defaultCharsPerSecond);

    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(delay);
    }

    if (needPause) {
        Pause(false);
    }
}

void printSlowly(const string& text, double charsPerSecond, bool needPause)
{
    if (charsPerSecond <= 0 || defaultCharsPerSecond == 0) {
        cout << text;
        if (needPause) Pause(false);
        return;
    }

    auto delay = chrono::duration<double>(1.0 / charsPerSecond);

    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(delay);
    }

    if (needPause) {
        Pause(false);
    }
}

void printSlowly(const string& text, double charsPerSecond, bool needPause, int color)
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, color);

    if (charsPerSecond <= 0 || defaultCharsPerSecond == 0) {
        cout << text;
        if (needPause) Pause(false);
        SetConsoleTextAttribute(hConsole, 7);
        return;
    }

    auto delay = chrono::duration<double>(1.0 / charsPerSecond);

    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(delay);
    }

    SetConsoleTextAttribute(hConsole, 7);

    if (needPause) {
        Pause(false);
    }
}

void ShowName(string name)
{
    cout << "[" << name << "]" << endl;
}

void ClearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void ChangeDefaulSpeed(double speed)
{
    defaultCharsPerSecond = speed;
}