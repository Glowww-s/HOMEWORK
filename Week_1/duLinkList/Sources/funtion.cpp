#include <duLinkedList.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>

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

void insert(DuLinkedList* tohead, Status(*mode)(DuLNode* p, DuLNode* q)) {          //��ǰ��ģʽ����ڵ�
    int n, m;
    DuLNode* p, * q;
    printf("����Ŀ�����data��");
    scanf_s("%d", &n);
    p = Search(tohead, n);
    if (p == NULL && *mode == InsertBeforeList_DuL) {                   //�Ҳ���Ŀ��ڵ㣬before�嵽��ǰ��
        p = *tohead;
    }
    else if (p == NULL && *mode == InsertAfterList_DuL) {               //�Ҳ���Ŀ��ڵ㣬after�嵽�����
        p = *tohead;
        if (p != NULL) {
            while (p->next != NULL) {
                p = p->next;
            }
        }
    }
    q = (DuLNode*)malloc(sizeof(DuLNode));
    if (q != NULL) {
        printf("�����½ڵ��data��");
        scanf_s("%d", &m);
        q->data = m;
    }
    if (mode(p, q))
        printf("�����ڵ�ɹ���\n");
    else
        printf("�����ڵ�ʧ�ܡ�\nError:����δ��ʼ��/δ�ҵ�Ŀ��ڵ�/�½ڵ㴴��ʧ��\n");
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
