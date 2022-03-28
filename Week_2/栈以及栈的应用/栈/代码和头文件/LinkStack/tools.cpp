#include <iostream>
#include <Windows.h>
#include <conio.h>

#define H 17
#define W 61

int Menu();
void Stop(void); /*暂停*/
void Fresh_Buffer(void); /*刷新缓冲区*/

int Menu()
{
    int i;
    int choice;
    char menu[H][W] = {
        {"                                                            "},
        {"         --------       1.初始化链栈         --------       "},
        {"                                                            "},
        {"         --------       2.入栈               --------       "},
        {"                                                            "},
        {"         --------       3.出栈               --------       "},
        {"                                                            "},
        {"         --------       4.得到栈顶元素       --------       "},
        {"                                                            "},
        {"         --------       5.判断栈是否为空     --------       "},
        {"                                                            "},
        {"         --------       6.检测栈长度         --------       "},
        {"                                                            "},
        {"         --------       7.清空栈             --------       "},
        {"                                                            "},
        {"         --------       8.销毁栈             --------       "},
        {"                                                            "},
    };
    system("cls");
    for (i = 0; i < H; i++) {
        printf("%s\n", menu[i]);
    }
    printf("  请输入所选功能的序号：");
    if (scanf_s("%d", &choice) == 0) { /*非法输入*/
        choice = -1;
    }
    else
        system("cls");
    Fresh_Buffer(); /*清空输入缓冲区*/
    return choice;
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