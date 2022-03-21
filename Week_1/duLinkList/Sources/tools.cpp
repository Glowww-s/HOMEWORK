#include <duLinkedList.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>

#define H 13

int Menu(void) { /*交互菜单*/
    int i;
    int choice = 0;
    char menu[H][50] = {
        {"                                                 "},
        {"    ----------    1.链表初始化     ----------    "},
        {"                                                 "},
        {"    ----------    2.销毁链表       ----------    "},
        {"                                                 "},
        {"    ----------    3.插入节点（前） ----------    "},
        {"                                                 "},
        {"    ----------    4.插入节点（后） ----------    "},
        {"                                                 "},
        {"    ----------    5.删除节点       ----------    "},
        {"                                                 "},
        {"    ----------    6.遍历链表       ----------    "},
        {"                                                 "},
    };
    system("cls");
    for (i = 0; i < H; i++) {
        printf("%s\n", menu[i]);
    }
    printf("请输入所选功能的序号：");
    scanf_s("%d", &choice);
    system("cls");
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

void visit(ElemType e) { /*访问节点数据*/
    printf("节点data：%d\n", int(e));
}

void reset(DuLinkedList* L) { /*找到链表头指针的函数*/
    DuLNode* p = *L;
    if (p != NULL) {
        while (p->prior != NULL) { /*获取链表的头指针*/
            p = p->prior;
        }
        *L = p;
    }
}