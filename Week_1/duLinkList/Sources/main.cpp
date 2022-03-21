#include <duLinkedList.h>
#include <iostream>
#include <Windows.h>

int main()
{
    Status state = (Status)ERROR; /*初始化链表状态用于判断*/
    DuLinkedList* tohead; /*指向头指针的二重指针*/
    int choice;
    ElemType *e;
    e = (ElemType*)malloc(sizeof(ElemType)); /*初始化参数的指针*/
    tohead = (DuLinkedList*)malloc(sizeof(DuLinkedList)); /*初始化二重指针*/
    system("mode con cols=50 lines=14");
    while (true) {
        choice = Menu();
        switch (choice) { /*功能选择*/
        case 1: /*初始化链表*/
            if (state == SUCCESS) { /*先销毁之前的链表*/
                DestroyList_DuL(tohead);
                tohead = (DuLinkedList*)malloc(sizeof(DuLinkedList)); /*重新初始化二重指针*/
                state = (Status)ERROR;
            }
            state = InitList_DuL(tohead);
            if (state) {
                printf("链表初始化成功！！！\n");
            }
            else {
                printf("链表初始化失败！！！\n");
            }
            Stop();
            break;
        case 2: /*销毁链表*/
            if (state == SUCCESS) {
                DestroyList_DuL(tohead);
                tohead = (DuLinkedList*)malloc(sizeof(DuLinkedList)); /*重新初始化二重指针*/
                state = (Status)ERROR;
            }
            break;
        case 3: /*搜索节点并插入（前）*/
            if (state == SUCCESS)
                insert(tohead, InsertBeforeList_DuL);
            else 
                printf("未初始化链表\n");
            Stop();
            break;
        case 4:
            if (state == SUCCESS)
                insert(tohead, InsertAfterList_DuL); /*搜索节点并插入（后）*/
            else
                printf("未初始化链表\n");
            Stop();
            break;
        case 5: /*删除指定节点*/
            if (state == SUCCESS) {
                printf("输入需要删除的节点数据：");
                scanf_s("%d", e);
                if (DeleteList_DuL(tohead, e)) {
                    printf("删除成功\n");
                    if (*tohead == NULL) /*删了唯一一个节点的情况*/
                        state = (Status)ERROR;
                }
                else
                    printf("删除失败\n");
            }
            else
                printf("未初始化链表\n");
            Stop();
            break;
        case 6: /*遍历链表并输出*/
            if (state==SUCCESS)
                TraverseList_DuL(*tohead, visit);
            else
                printf("未初始化链表！\n");
            Stop();
            break;
        }
        if (state)
            reset(tohead);  /*每次操作过后都重新定位头指针（方便查找和遍历）*/
        Sleep(180);
    }
}