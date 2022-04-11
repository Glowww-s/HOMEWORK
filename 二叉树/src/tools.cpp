#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "../inc/binary_sort_tree.h"
#include "../inc/tools.h"


void HideCursor() //���ع��
{
    CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void ShowCursor() //��ʾ���
{
    CONSOLE_CURSOR_INFO cursor_info = { 1,1 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

char MenuChoose(const char(*menu)[W], int m)//ѡ����,m->����
{
    int s = (E / 2) - m / 2 * 3;//��ʼλ��
    int e = (E / 2) + m / 2 * 3;//����λ��
    int step = ((m + 1) % 2 + 1) * 3; //����
    int n = s;
    char c = ' ';
    HLshow(menu, s);
    while (1) {
        if (_kbhit()) {
            c = _getch();
            if (GetAsyncKeyState(VK_UP)) {
                n -= step;
                if (n < s)
                    n = e;
                system("cls");
                HLshow(menu, n);
            }
            if (GetAsyncKeyState(VK_DOWN)) {
                n += step;
                if (n > e)
                    n = s;
                system("cls");
                HLshow(menu, n);
            }
            if (GetAsyncKeyState(VK_ESCAPE)) {
                n = -1;
                system("cls");
                break;
            }
            if (c == '\r') {
                n = (n - s) / step + 1; /*���к�ת��Ϊѡ�������*/
                system("cls");
                break;
            }
        }
        Sleep(100);
    }
    return n;
}

void HLshow(const char(*p)[W], int n)//������ʾ
{
    int i;
    for (i = 0; i < E - 1; i++) {
        if (i == n)
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x70);
        else
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        printf("%s\n", *(p + i));
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    printf("%s", *(p + i));
}

void Stop(void) /*��ͣ*/
{
    char c = ' ';
    printf("\n����س�[Enter]���ز˵�\n");
    do {
        c = _getch();
        Sleep(100);
    } while (c != '\r');
}

void Fresh_Buffer(void) /*ˢ�»�����*/
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF); /*������뻺����*/
}

void Visit(NodePtr p)
{
    printf("%d��", p->value);
}
