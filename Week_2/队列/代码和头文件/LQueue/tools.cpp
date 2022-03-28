#include "../head/LQueue.h" 
#include <iostream>
#include <Windows.h>
#include <conio.h>

#define H 19
#define W 61

int Menu();
void Stop(void); /*��ͣ*/
void Fresh_Buffer(void); /*ˢ�»�����*/
Status GetData(void* data); /*��ȡ��������*/
void MoveForward(int n); /*��������ǰ��һλ*/

int Menu()
{
    int i;
    int choice;
    char menu[H][W] = {
        {"                                                            "},
        {"         --------       1.��ʼ������         --------       "},
        {"                                                            "},
        {"         --------       2.���               --------       "},
        {"                                                            "},
        {"         --------       3.����               --------       "},
        {"                                                            "},
        {"         --------       4.��������Ԫ��       --------       "},
        {"                                                            "},
        {"         --------       5.�鿴��ͷԪ��       --------       "},
        {"                                                            "},
        {"         --------       6.�ж϶����Ƿ�Ϊ��   --------       "},
        {"                                                            "},
        {"         --------       7.�����г���       --------       "},
        {"                                                            "},
        {"         --------       8.��ն���           --------       "},
        {"                                                            "},
        {"         --------       9.���ٶ���           --------       "},
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

Status GetData(void* data) /*��ȡ��������*/
{
    Status state = (Status)FALSE;
    int choice;
    printf("��ѡ�������ͣ�  1.���ͣ�  2.�����ͣ�  3.���ַ���  4.�ַ���\n\n");
    printf("��������Ҫ�����������͵���ţ�");
    if (scanf_s("%d", &choice) == 0 || choice > 4 || choice < 1) {
        printf(" *** ��Чѡ���������롣 *** \n");
    }
    else {
        switch (choice) {
        case 1:
            printf("�������������ݣ�");
            if (scanf_s("%d", (int*)data) == 0) {
                printf(" *** ����ѡ���Ͳ������������롣 *** \n");
            }
            else {
                state = (Status)TRUE;
                type = 'd'; /*��¼��������*/
            }
            break;
        case 2:
            printf("�����븡�������ݣ�");
            if (scanf_s("%lf", (double*)data) == 0) {
                printf(" *** ����ѡ���Ͳ������������롣 *** \n");
            }
            else {
                state = (Status)TRUE;
                type = 'f'; /*��¼��������*/
            }
            break;
        case 3:
            printf("�����뵥�ַ����ݣ�");
            if (scanf_s("%s", (char*)data, 50) == 0) {
                printf(" *** ����ѡ���Ͳ������������롣 *** \n");
            }
            else if (strlen((char*)data) != 1) {
                printf(" *** ����ѡ���Ͳ������������롣 *** \n");
            }
            else {
                state = (Status)TRUE;
                type = 'c'; /*��¼��������*/
            }
            break;
        case 4:
            printf("�������ַ������ݣ�");
            if (scanf_s("%s", (char*)data, 50) == 0) {
                printf(" *** ����ѡ���Ͳ������������롣 *** \n");
            }
            else {
                state = (Status)TRUE;
                type = 's'; /*��¼��������*/
            }
            break;
        }
    }
    Fresh_Buffer();
    return state;
}

void MoveForward(int n) /*��������ǰ��һλ*/
{
    int i;
    for (i = 0; i < n; i++) {
        datatype[i] = datatype[i + 1];
    }
    datatype[n] = 0; /*����ظ������һ��*/
}