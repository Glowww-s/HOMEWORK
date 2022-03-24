#include <iostream>
#include <linkedList.h>
#include <conio.h>
#include <Windows.h>

#define H 23

void Fresh_Buffer(void); /*刷新缓冲区*/

int Menu(void) { /*交互菜单*/
    int i;
    int choice = 0;
    char menu[H][70] = {
        {"                                                                     "},
        {"      -------------       1.创建新链表           -------------       "},
        {"                                                                     "},
        {"      -------------       2.插入新节点           -------------       "},
        {"                                                                     "},
        {"      -------------       3.输出链表             -------------       "},
        {"                                                                     "},
        {"      -------------       4.链表反向             -------------       "},
        {"                                                                     "},
        {"      -------------       5.找到单链表中点       -------------       "},
        {"                                                                     "},
        {"      -------------       6.判断是否成环         -------------       "},
        {"                                                                     "},
        {"      -------------       7.删除节点取值         -------------       "},
        {"                                                                     "},
        {"      -------------       8.奇偶反转             -------------       "},
        {"                                                                     "},
        {"      -------------       9.查询数据是否位于链表 -------------       "},
        {"                                                                     "},
        {"      -------------       10.构造循环链表        -------------       "},
        {"                                                                     "},
        {"      -------------       0.销毁列表并退出       -------------       "},
        {"                                                                     "},
    };
    system("cls");
    for (i = 0; i < H; i++) {
        printf("%s\n", menu[i]);
    }
    printf("  请输入所选功能的序号：");
    if (scanf_s("%d", &choice) == 0) { /*非法输入*/
        choice = OVERFLOW;
    }
    else
        system("cls");
    Fresh_Buffer(); /*清空输入缓冲区*/
    return choice;
}

void Stop(void) { /*暂停*/
    char c = ' ';
    printf("输入回车[Enter]返回菜单\n");
    do {
        c = _getch();
        Sleep(100);
    } while (c != '\r');
}

void Visit(ElemType e) { /*访问节点数据*/
    printf("节点data：%d\n", int(e));
}

void Fresh_Buffer(void) { /*刷新缓冲区*/
    char c;
    while ((c = getchar()) != '\n' && c != EOF); /*清空输入缓冲区*/
}