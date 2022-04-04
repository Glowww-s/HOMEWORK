#include "../Headers/sort.h"
#include "../Headers/tools.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

void HideCursor() //隐藏光标
{
    CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void ShowCursor() //显示光标
{
    CONSOLE_CURSOR_INFO cursor_info = { 1,1 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

char MenuChoose(const char(*menu)[W], int m)//选择功能,m->项数
{
    int s = (E / 2) - m / 2 * 3;//开始位置
    int e = (E / 2) + m / 2 * 3;//结束位置
    int step = ((m + 1) % 2 + 1) * 3; //步长
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
                n = (n - s) / step + 1; /*将行号转化为选择的项数*/
                system("cls");
                break;
            }
        }
        Sleep(100);
    }
    return n;
}

void HLshow(const char(*p)[W], int n)//高亮显示
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

void DataSave(int scale) /*生成并保存数据*/
{
    FILE* fp;
    if (fopen_s(&fp, "data.txt", "wb")) {
        fprintf(stderr, "*** 打开数据文件失败! ***\n");
        exit(EXIT_FAILURE);
    }
    srand((unsigned)time(NULL)); /*修改随机数种子*/
    for (int i = 0; i < scale; i++) {
        fprintf(fp, "%d ", rand()); /*生成数据写入文件*/
    }
    fclose(fp);
}

int* DataRead(void) /*读取数据*/
{
    FILE* fp;
    int* p;
    int cnt = 0;
    if (fopen_s(&fp, "data.txt", "rb")) {
        fprintf(stderr, "*** 打开数据文件失败! ***\n");
        exit(EXIT_FAILURE);
    }
    p = (int*)malloc(sizeof(int)); /*初始化*/
    if (p == NULL) {
        fprintf(stderr, "*** 申请内存空间失败！ ***");
        exit(EXIT_FAILURE);
    }
    while (fscanf_s(fp, "%d", p + cnt) != EOF) {
        cnt += 1;
        p = (int*)realloc(p, (cnt + 1) * sizeof(int));
        if (p == NULL) {
            fprintf(stderr, "*** 申请内存空间失败！ ***");
            exit(EXIT_FAILURE);
        }
    }
    fclose(fp);
    return p; /*返回数据指针*/
}

void Stop(void) /*暂停*/
{
    char c = ' ';
    printf("\n输入回车[Enter]返回菜单\n");
    do {
        c = _getch();
        Sleep(100);
    } while (c != '\r');
}

void Fresh_Buffer(void) /*刷新缓冲区*/
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF); /*清空输入缓冲区*/
}

