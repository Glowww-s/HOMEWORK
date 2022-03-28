#include "../head/LQueue.h" 
#include <iostream>
#include <Windows.h>
#include <conio.h>

#define H 19
#define W 61

int Menu();
void Stop(void); /*暂停*/
void Fresh_Buffer(void); /*刷新缓冲区*/
Status GetData(void* data); /*获取泛型数据*/
void MoveForward(int n); /*整个数组前移一位*/

int Menu()
{
    int i;
    int choice;
    char menu[H][W] = {
        {"                                                            "},
        {"         --------       1.初始化队列         --------       "},
        {"                                                            "},
        {"         --------       2.入队               --------       "},
        {"                                                            "},
        {"         --------       3.出队               --------       "},
        {"                                                            "},
        {"         --------       4.遍历队内元素       --------       "},
        {"                                                            "},
        {"         --------       5.查看队头元素       --------       "},
        {"                                                            "},
        {"         --------       6.判断队列是否为空   --------       "},
        {"                                                            "},
        {"         --------       7.检测队列长度       --------       "},
        {"                                                            "},
        {"         --------       8.清空队列           --------       "},
        {"                                                            "},
        {"         --------       9.销毁队列           --------       "},
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

Status GetData(void* data) /*获取泛型数据*/
{
    Status state = (Status)FALSE;
    int choice;
    printf("可选数据类型：  1.整型，  2.浮点型，  3.单字符，  4.字符串\n\n");
    printf("请输入您要输入数据类型的序号：");
    if (scanf_s("%d", &choice) == 0 || choice > 4 || choice < 1) {
        printf(" *** 无效选择，请检查输入。 *** \n");
    }
    else {
        switch (choice) {
        case 1:
            printf("请输入整型数据：");
            if (scanf_s("%d", (int*)data) == 0) {
                printf(" *** 与所选类型不符，请检查输入。 *** \n");
            }
            else {
                state = (Status)TRUE;
                type = 'd'; /*记录数据类型*/
            }
            break;
        case 2:
            printf("请输入浮点型数据：");
            if (scanf_s("%lf", (double*)data) == 0) {
                printf(" *** 与所选类型不符，请检查输入。 *** \n");
            }
            else {
                state = (Status)TRUE;
                type = 'f'; /*记录数据类型*/
            }
            break;
        case 3:
            printf("请输入单字符数据：");
            if (scanf_s("%s", (char*)data, 50) == 0) {
                printf(" *** 与所选类型不符，请检查输入。 *** \n");
            }
            else if (strlen((char*)data) != 1) {
                printf(" *** 与所选类型不符，请检查输入。 *** \n");
            }
            else {
                state = (Status)TRUE;
                type = 'c'; /*记录数据类型*/
            }
            break;
        case 4:
            printf("请输入字符串数据：");
            if (scanf_s("%s", (char*)data, 50) == 0) {
                printf(" *** 与所选类型不符，请检查输入。 *** \n");
            }
            else {
                state = (Status)TRUE;
                type = 's'; /*记录数据类型*/
            }
            break;
        }
    }
    Fresh_Buffer();
    return state;
}

void MoveForward(int n) /*整个数组前移一位*/
{
    int i;
    for (i = 0; i < n; i++) {
        datatype[i] = datatype[i + 1];
    }
    datatype[n] = 0; /*清除重复的最后一项*/
}