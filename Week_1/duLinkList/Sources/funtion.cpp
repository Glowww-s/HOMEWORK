#include <duLinkedList.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>

Status InitList_DuL(DuLinkedList* L) { /*初始化链表*/
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

void DestroyList_DuL(DuLinkedList* L) { /*销毁链表*/
    DuLNode* p1, * p2;
    p1 = p2 = *L;
    while (p1 != NULL) {
        p2 = p1;
        p1 = p1->next;
        free(p2);
    }
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
            while (p->next != NULL) {
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

void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e)) { /*遍历链表节点并访问*/
    if (L != NULL) {
        while (L->prior != NULL) { /*获取链表的头指针*/
            L = L->prior;
        }
        while (L != NULL) {  /*遍历输出*/
            visit(L->data);
            L = L->next;
        }
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
