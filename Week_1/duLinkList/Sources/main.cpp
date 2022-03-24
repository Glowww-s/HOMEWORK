#include <iostream>
#include <duLinkedList.h>
#include <conio.h>
#include <Windows.h>

int Menu(void);
void Stop(void);
void Visit(ElemType e);
void Reset(DuLinkedList* L);
void Fresh_Buffer(void);

void Insert(DuLinkedList* tohead, Status(*mode)(DuLNode* p, DuLNode* q));
Status CreateList(DuLinkedList* L);

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
        case 1: /*创建链表*/
            if (state == SUCCESS) { /*先销毁之前的链表*/
                DestroyList_DuL(tohead);
                tohead = (DuLinkedList*)malloc(sizeof(DuLinkedList)); /*重新初始化二重指针*/
                state = (Status)ERROR;
            }
            state = CreateList(tohead);
            if (state) {
                printf("创建链表成功！！！\n");
            }
            else {
                printf("创建链表失败！！！\n");
            }
            Stop();
            break;
        case 2: /*遍历链表并输出*/
            if (state == SUCCESS)
                TraverseList_DuL(*tohead, Visit);
            else
                printf("未初始化链表！\n");
            Stop();
            break;
        case 3: /*搜索节点并插入（前）*/
            if (state == SUCCESS)
                Insert(tohead, InsertBeforeList_DuL);
            else 
                printf("未初始化链表\n");
            Stop();
            break;
        case 4: /*搜索节点并插入（后）*/
            if (state == SUCCESS)
                Insert(tohead, InsertAfterList_DuL); 
            else
                printf("未初始化链表\n");
            Stop();
            break;
        case 5: /*删除指定节点*/
            if (state == SUCCESS) {
                printf("输入需要删除的节点数据：");
                if (scanf_s("%d", e) == 0) {
                    printf("\n*** 非法输入，请检查输入 ***\n");
                }
                else {
                    if (DeleteList_DuL(tohead, e)) {
                        printf("删除成功\n");
                        if (*tohead == NULL) /*删了唯一一个节点的情况*/
                            state = (Status)ERROR;
                    }
                    else
                        printf("删除失败\n");
                }
                Fresh_Buffer();
            }
            else
                printf("未初始化链表\n");
            Stop();
            break;
        case 6: /*销毁链表并退出*/
            if (state == SUCCESS) {
                DestroyList_DuL(tohead);
                tohead = (DuLinkedList*)malloc(sizeof(DuLinkedList)); /*重新初始化二重指针*/
                state = (Status)ERROR;
            }
            exit(EXIT_SUCCESS);
        }
        if (state)
            Reset(tohead);  /*每次操作过后都重新定位头指针（方便查找和遍历）*/
        Sleep(180);
    }
}