#include <duLinkedList.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>

#define H 13

int Menu(void);
void Stop(void);
DuLNode* Search(DuLinkedList* L, ElemType n);
void visit(ElemType e);
void insert(DuLinkedList* tohead, Status (*mode)(DuLNode* p, DuLNode* q));
void reset(DuLinkedList* L);

int main()
{
    Status state = (Status)ERROR;                                   //初始化链表状态用于判断
    DuLinkedList* tohead;                                           //指向头指针的二重指针
    int choice;
    ElemType *e;
    e = (ElemType*)malloc(sizeof(ElemType));                        //初始化参数的指针
    tohead = (DuLinkedList*)malloc(sizeof(DuLinkedList));           //初始化二重指针
    system("mode con cols=50 lines=14");
    while (true) {
        choice = Menu();
        switch (choice) {                                           //功能选择
        case 1:                                         //初始化链表
            if (state == SUCCESS) {                                             //先销毁之前的链表
                DestroyList_DuL(tohead);
                tohead = (DuLinkedList*)malloc(sizeof(DuLinkedList));           //重新初始化二重指针
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
        case 2:                                         //销毁链表
            if (state == SUCCESS) {
                DestroyList_DuL(tohead);
                tohead = (DuLinkedList*)malloc(sizeof(DuLinkedList));           //重新初始化二重指针
                state = (Status)ERROR;
            }
            break;
        case 3:                                         //搜索节点并插入（前）
            if (state == SUCCESS)
                insert(tohead, InsertBeforeList_DuL);
            else 
                printf("未初始化链表\n");
            Stop();
            break;
        case 4:
            if (state == SUCCESS)
                insert(tohead, InsertAfterList_DuL);        //搜索节点并插入（后）
            else
                printf("未初始化链表\n");
            Stop();
            break;
        case 5:                                         //删除指定节点
            if (state == SUCCESS) {
                printf("输入需要删除的节点数据：");
                scanf_s("%d", e);
                if (DeleteList_DuL(tohead, e)) {
                    printf("删除成功\n");
                    if (*tohead == NULL)                        //删了唯一一个节点的情况
                        state = (Status)ERROR;
                }
                else
                    printf("删除失败\n");
            }
            else
                printf("未初始化链表\n");
            Stop();
            break;
        case 6:                                         //遍历链表并输出
            if (state==SUCCESS)
                TraverseList_DuL(*tohead, visit);
            else
                printf("未初始化链表！\n");
            Stop();
            break;
        }
        if (state)
            reset(tohead);                              //每次操作过后都重新定位头指针（方便查找和遍历）
        Sleep(180);
    }
}

void Stop(void) {               //暂停
    char c = ' ';
    printf("输入回车[Enter]返回菜单\n");
    do {
        c = _getch();
        Sleep(100);
    } while (c != '\r');
}

int Menu(void) {                //交互菜单
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

Status InitList_DuL(DuLinkedList* L) {              //初始化链表
    //初始化结果为error
    Status result = (Status)ERROR;
    DuLinkedList head;
    head = (DuLinkedList)malloc(sizeof(DuLNode));
    if (head != NULL) {
        head->data = -1;
        head->next = NULL;
        head->prior = NULL;
        *L = head;
        result = SUCCESS;
    }
    return result;
}

void DestroyList_DuL(DuLinkedList* L) {             //销毁链表
    DuLNode* p1, * p2;
    p1 = p2 = *L;
    while (p1 != NULL) {
        p2 = p1;
        p1 = p1->next;
        free(p2);
    }
}

DuLNode* Search(DuLinkedList* L, ElemType n) {
    DuLinkedList p = *L;
    while (p != NULL) {
        if (p->data == n) {
            break;
        }
        p = p->next;
    }
    return p;
}

void insert(DuLinkedList* tohead, Status(*mode)(DuLNode* p, DuLNode* q)) {          //分前后模式插入节点
    int n, m;
    DuLNode* p, * q;
    printf("输入目标结点的data：");
    scanf_s("%d", &n);
    p = Search(tohead, n);
    if (p == NULL && *mode == InsertBeforeList_DuL) {                   //找不到目标节点，before插到最前面
        p = *tohead;
    }
    else if (p == NULL && *mode == InsertAfterList_DuL) {               //找不到目标节点，after插到最后面
        p = *tohead;
        if (p != NULL) {
            while (p->next!=NULL) {
                p = p->next;
            }
        }
    }
    q = (DuLNode*)malloc(sizeof(DuLNode));
    if (q != NULL) {
        printf("输入新节点的data：");
        scanf_s("%d", &m);
        q->data = m;
    }
    if (mode(p, q))
        printf("新增节点成功。\n");
    else
        printf("新增节点失败。\nError:链表未初始化/未找到目标节点/新节点创建失败\n");
}

Status InsertBeforeList_DuL(DuLNode* p, DuLNode* q) {
    DuLNode* mark;
    Status result = (Status)ERROR;
    if (p != NULL && q != NULL) {
        mark = p->prior;                    //记录目标的前一个节点
        p->prior = q;
        q->next = p;
        if (mark == NULL) {                 //p是head的情况
            q->prior = NULL;
        }
        else {                              //p不是head的情况
            mark->next = q;
            q->prior = mark;
        }
        result = SUCCESS;
    }
    return result;
}

Status InsertAfterList_DuL(DuLNode* p, DuLNode* q) {
    Status result = (Status)ERROR;
    DuLNode* mark;
    if (p != NULL && q != NULL) {
        mark = p->next;             //记录目标的下一个节点
        p->next = q;
        q->prior = p;
        if (mark == NULL) {         //p是head的情况
            q->next = NULL;
        }
        else {                      //p不是head的情况
            q->next = mark;
            mark->prior = q;
        }
        result = SUCCESS;
    }
    return result;
}

Status DeleteList_DuL(DuLinkedList* L, ElemType* e) {            //这里的头文件改了个形参
    Status result = (Status)ERROR;
    DuLNode* p, * before, * after;
    p = Search(L, *e);
    if (p != NULL) {
        before = p->prior;
        after = p->next;
        if (before == NULL && after != NULL) {              //要删除第一个节点
            *L = after;
            after->prior = NULL;
        }
        else if (after == NULL && before != NULL) {         //要删除最后一个节点
            before->next = NULL;
        }
        else if (before != NULL && after != NULL) {         //删除非头尾节点
            before->next = after;
            after->prior = before;
        }
        else {                                              //删除唯一的节点
            *L = NULL;
        }
        free(p);
        result = SUCCESS;
    }
    return result;
}

void visit(ElemType e) {                        //访问节点数据
    printf("节点data：%d\n", int(e));
}

void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e)) {      //遍历链表节点并访问
    if (L != NULL) {
        while (L->prior != NULL) {                  //获取链表的头指针
            L = L->prior;
        }
        while (L != NULL) {                         //遍历输出
            visit(L->data);
            L = L->next;
        }
    }
}

void reset(DuLinkedList* L) {                       //找到链表头指针的函数
    DuLNode* p = *L;
    if (p != NULL) {
        while (p->prior != NULL) {                  //获取链表的头指针
            p = p->prior;
        }
        *L = p;
    }
}