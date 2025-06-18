// ConsoleUtils.h
#pragma once
#include <string>
#include <windows.h>
#include <conio.h>   // _getch()

using namespace std;

namespace ConsoleUtils {
    // �ܼ� Ŀ�� ��ġ �̵� (x��ǥ�� �ѱ� ���� ����� 2��� ���)
    void gotoxy(int x, int y);

    // �ܼ� Ŀ�� �����/���̱�
    void ShowConsoleCursor(bool showFlag);

    // ȭ�� ��ü �����
    void clearScreen();

    // HP, MP �� ���� �� ���ڿ� ����
    std::wstring drawStatBar(const wstring& label, float current, float max, int barLength = 15);

	// ��ȭ ���� �׸���
    void DrawDialogueBox(const wstring& message);

    // �簢�� �׵θ� �׸���
    void drawBox(int x, int y, int width, int height);
}