#include <duLinkedList.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>

void Fresh_Buffer(void);
DuLNode* Search(DuLinkedList* L, ElemType n);

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

void Insert(DuLinkedList* tohead, Status(*mode)(DuLNode* p, DuLNode* q)) { /*分前后模式插入节点*/
    int n, m;
    DuLNode* p, * q;
    printf("输入目标结点的data：");
    if (scanf_s("%d", &n) == 0) {
        printf("\n*** 非法输入，请检查输入 ***\n");
        goto End_Insert;
    }
    p = Search(tohead, n);
    if (p == NULL) {
        printf("未找到目标节点。\n");
    }
    else {
        q = (DuLNode*)malloc(sizeof(DuLNode));
        if (q != NULL) {
            printf("输入新节点的data：");
            if (scanf_s("%d", &m) == 0) {
                free(q);
                printf("\n*** 非法输入，请检查输入 ***\n");
                goto End_Insert;
            }
            q->data = m;
        }
        if (mode(p, q))
            printf("新增节点成功。\n");
        else
            printf("新增节点失败。\n");
    }
End_Insert:;
    Fresh_Buffer();
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

Status CreateList(DuLinkedList* L) {
    Status result = (Status)ERROR;
    int n, data;
    int cnt;
    DuLNode* p, * q;
    if (InitList_DuL(L)) {
        p = q = *L;
        printf("初始化链表成功！\n请输入需要构建的节点数：");
        if (scanf_s("%d", &n) == 0) {
            DestroyList_DuL(L);
            printf("\n*** 非法输入，请检查输入 ***\n");
            Fresh_Buffer();
            goto End_Create;
        }
        for (cnt = 0; cnt < n; cnt++) {
            printf("请输入第%d个节点的数据：", cnt + 1);
            if (scanf_s("%d", &data) == 0) {
                q->next = NULL; /*收尾*/
                DestroyList_DuL(L);
                printf("\n*** 非法输入，请检查输入 ***\n");
                Fresh_Buffer();
                goto End_Create;
            }
            p->data = data;
            q = p;
            p = (DuLNode*)malloc(sizeof(DuLNode));
            if (p == NULL) {
                fprintf(stderr, "申请空间失败.\n");
                exit(EXIT_FAILURE);
            }
            q->next = p;
            p->prior = q;
        }
        q->next = NULL; /*收尾*/
        result = SUCCESS;
    }
    else {
        printf("链表初始化失败。\n");
    }
End_Create:; /*非法输入销毁失败链表*/
    return result;
}