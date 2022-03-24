#include <duLinkedList.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>

void Fresh_Buffer(void);
DuLNode* Search(DuLinkedList* L, ElemType n);

Status InitList_DuL(DuLinkedList* L) { /*��ʼ������*/
    //��ʼ�����Ϊerror
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

void DestroyList_DuL(DuLinkedList* L) { /*��������*/
    DuLNode* p1, * p2;
    p1 = p2 = *L;
    while (p1 != NULL) {
        p2 = p1;
        p1 = p1->next;
        free(p2);
    }
}

void Insert(DuLinkedList* tohead, Status(*mode)(DuLNode* p, DuLNode* q)) { /*��ǰ��ģʽ����ڵ�*/
    int n, m;
    DuLNode* p, * q;
    printf("����Ŀ�����data��");
    if (scanf_s("%d", &n) == 0) {
        printf("\n*** �Ƿ����룬�������� ***\n");
        goto End_Insert;
    }
    p = Search(tohead, n);
    if (p == NULL) {
        printf("δ�ҵ�Ŀ��ڵ㡣\n");
    }
    else {
        q = (DuLNode*)malloc(sizeof(DuLNode));
        if (q != NULL) {
            printf("�����½ڵ��data��");
            if (scanf_s("%d", &m) == 0) {
                free(q);
                printf("\n*** �Ƿ����룬�������� ***\n");
                goto End_Insert;
            }
            q->data = m;
        }
        if (mode(p, q))
            printf("�����ڵ�ɹ���\n");
        else
            printf("�����ڵ�ʧ�ܡ�\n");
    }
End_Insert:;
    Fresh_Buffer();
}

Status InsertBeforeList_DuL(DuLNode* p, DuLNode* q) {
    DuLNode* mark;
    Status result = (Status)ERROR;
    if (p != NULL && q != NULL) {
        mark = p->prior;                    //��¼Ŀ���ǰһ���ڵ�
        p->prior = q;
        q->next = p;
        if (mark == NULL) {                 //p��head�����
            q->prior = NULL;
        }
        else {                              //p����head�����
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
        mark = p->next;             //��¼Ŀ�����һ���ڵ�
        p->next = q;
        q->prior = p;
        if (mark == NULL) {         //p��head�����
            q->next = NULL;
        }
        else {                      //p����head�����
            q->next = mark;
            mark->prior = q;
        }
        result = SUCCESS;
    }
    return result;
}

Status DeleteList_DuL(DuLinkedList* L, ElemType* e) {            //�����ͷ�ļ����˸��β�
    Status result = (Status)ERROR;
    DuLNode* p, * before, * after;
    p = Search(L, *e);
    if (p != NULL) {
        before = p->prior;
        after = p->next;
        if (before == NULL && after != NULL) {              //Ҫɾ����һ���ڵ�
            *L = after;
            after->prior = NULL;
        }
        else if (after == NULL && before != NULL) {         //Ҫɾ�����һ���ڵ�
            before->next = NULL;
        }
        else if (before != NULL && after != NULL) {         //ɾ����ͷβ�ڵ�
            before->next = after;
            after->prior = before;
        }
        else {                                              //ɾ��Ψһ�Ľڵ�
            *L = NULL;
        }
        free(p);
        result = SUCCESS;
    }
    return result;
}

void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e)) { /*��������ڵ㲢����*/
    if (L != NULL) {
        while (L->prior != NULL) { /*��ȡ�����ͷָ��*/
            L = L->prior;
        }
        while (L != NULL) {  /*�������*/
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
        printf("��ʼ������ɹ���\n��������Ҫ�����Ľڵ�����");
        if (scanf_s("%d", &n) == 0) {
            DestroyList_DuL(L);
            printf("\n*** �Ƿ����룬�������� ***\n");
            Fresh_Buffer();
            goto End_Create;
        }
        for (cnt = 0; cnt < n; cnt++) {
            printf("�������%d���ڵ�����ݣ�", cnt + 1);
            if (scanf_s("%d", &data) == 0) {
                q->next = NULL; /*��β*/
                DestroyList_DuL(L);
                printf("\n*** �Ƿ����룬�������� ***\n");
                Fresh_Buffer();
                goto End_Create;
            }
            p->data = data;
            q = p;
            p = (DuLNode*)malloc(sizeof(DuLNode));
            if (p == NULL) {
                fprintf(stderr, "����ռ�ʧ��.\n");
                exit(EXIT_FAILURE);
            }
            q->next = p;
            p->prior = q;
        }
        q->next = NULL; /*��β*/
        result = SUCCESS;
    }
    else {
        printf("�����ʼ��ʧ�ܡ�\n");
    }
End_Create:; /*�Ƿ���������ʧ������*/
    return result;
}