#include <iostream>
#include <Windows.h>
#include <conio.h>

#define H 17
#define W 61

int Menu();
void Stop(void); /*��ͣ*/
void Fresh_Buffer(void); /*ˢ�»�����*/

int Menu()
{
    int i;
    int choice;
    char menu[H][W] = {
        {"                                                            "},
        {"         --------       1.��ʼ����ջ         --------       "},
        {"                                                            "},
        {"         --------       2.��ջ               --------       "},
        {"                                                            "},
        {"         --------       3.��ջ               --------       "},
        {"                                                            "},
        {"         --------       4.�õ�ջ��Ԫ��       --------       "},
        {"                                                            "},
        {"         --------       5.�ж�ջ�Ƿ�Ϊ��     --------       "},
        {"                                                            "},
        {"         --------       6.���ջ����         --------       "},
        {"                                                            "},
        {"         --------       7.���ջ             --------       "},
        {"                                                            "},
        {"         --------       8.����ջ             --------       "},
        {"                                                            "},
    };
    system("cls");
    for (i = 0; i < H; i++) {
        printf("%s\n", menu[i]);
    }
    printf("  ��������ѡ���ܵ���ţ�");
    if (scanf_s("%d", &choice) == 0) { /*�Ƿ�����*/
        choice = -1;
    }
    else
        system("cls");
    Fresh_Buffer(); /*������뻺����*/
    return choice;
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