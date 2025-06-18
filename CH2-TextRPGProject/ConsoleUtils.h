// ConsoleUtils.h
#pragma once
#include <string>
#include <windows.h>
#include <conio.h>   // _getch()

using namespace std;

namespace ConsoleUtils {
    // 콘솔 커서 위치 이동 (x좌표는 한글 등을 고려해 2배로 계산)
    void gotoxy(int x, int y);

    // 콘솔 커서 숨기기/보이기
    void ShowConsoleCursor(bool showFlag);

    // 화면 전체 지우기
    void clearScreen();

    // HP, MP 등 상태 바 문자열 생성
    std::wstring drawStatBar(const wstring& label, float current, float max, int barLength = 15);

	// 대화 상자 그리기
    void DrawDialogueBox(const wstring& message);

    // 사각형 테두리 그리기
    void drawBox(int x, int y, int width, int height);
}