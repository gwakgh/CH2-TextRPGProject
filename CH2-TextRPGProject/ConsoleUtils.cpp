// ConsoleUtils.cpp
#include "ConsoleUtils.h"
#include <iostream>

using namespace std;

namespace ConsoleUtils {
    void gotoxy(int x, int y) {
        COORD pos = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }

    void ShowConsoleCursor(bool showFlag) {
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = showFlag;
        SetConsoleCursorInfo(out, &cursorInfo);
    }

    void clearScreen() {
        system("cls");
    }

    wstring drawStatBar(const wstring& label, float current, float max, int barLength) {
        if (current < 0) current = 0;
        float ratio = (max > 0) ? (current / max) : 0;
        int filledLength = static_cast<int>(ratio * barLength);

        wstring bar = label + L" [";
        for (int i = 0; i < barLength; ++i) {
            if (i < filledLength) bar += L"■";
            else bar += L" ";
        }
        bar += L"]";
        return bar;
    }

    void drawBox(int x, int y, int width, int height) {
        gotoxy(x, y); wcout << L"┌";
        for (int i = 0; i < width - 2; ++i) wcout << L"─";
        wcout << L"┐";

        for (int i = 1; i < height - 1; ++i) {
            gotoxy(x, y + i); wcout << L"│";
            gotoxy(x + width - 1, y + i); wcout << L"│";
        }

        gotoxy(x, y + height - 1); wcout << L"└";
        for (int i = 0; i < width - 2; ++i) wcout << L"─";
        wcout << L"┘";
    }
    void DrawDialogueBox(const std::wstring& message)
    {
        int width = 40;
        int height = 5;
        int startX = 2;
        int startY = 15; // 필드 하단에 표시

        drawBox(startX, startY, width, height);

        // 이전 메시지를 지우기 위해 박스 내부를 공백으로 채움
        gotoxy(startX + 1, startY + 2);
        std::wcout << std::wstring(width * 2 - 4, L' ');

        gotoxy(startX + 2, startY + 2);
        std::wcout << message;

        // 아무 키나 누를 때까지 대기
        _getch();
    }
}