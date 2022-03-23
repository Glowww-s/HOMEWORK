#include <iostream>
#include <linkedList.h>
#include <conio.h>
#include <Windows.h>

void Fresh_Buffer(void); /*ˢ�»�����*/

Status InitList(LinkedList* L) {
    Status result = (Status)ERROR;
    LinkedList head;
    head = (LinkedList)malloc(sizeof(LNode));
    if (head != NULL) {
        head->data = -1;
        head->next = NULL;
        *L = head;
        result = SUCCESS;
    }
    return result;
}

void DestroyList(LinkedList* L) {                           //����
    LNode* p1, * p2, * p;
    p1 = p2 = *L;
    if (IsLoopList(*L)) {                               //�⻷
        while (p1 != NULL) {
            p = p1;
            p1 = p1->next;
            if (p2 != NULL && p2->next != NULL) {
                p2 = p2->next->next;
                if (p1 == p2) {
                    p->next = NULL;
                    break;
                }
            }
        }
    }
    p1 = p2 = *L;
    while (p1 != NULL) {                                //�ͷŵ�����
        p = p1;
        p1 = p1->next;
        free(p);
    }
}

Status InsertList(LNode* p, LNode* q) {
    Status result = (Status)ERROR;
    LNode* mark;
    mark = p->next;
    p->next = q;
    if (mark == NULL) {
        q->next = NULL;
    }
    else {
        q->next = mark;
    }
    result = SUCCESS;
    return result;
}

Status DeleteList(LinkedList* L, ElemType* e) {
    Status result = (Status)ERROR;
    LNode* p1, * p2, * p;
    p1 = p2 = p = *L;
    if (*L != NULL) {
        while (p1->next != NULL) {                                //����Ŀ��ڵ�p1
            p = p1;
            p1 = p1->next; /*ֱ��������һ�����ӵڶ�����ʼ�ж�*/
            if (p2 != NULL && p2->next != NULL) {
                p2 = p2->next->next;
                if (p1 == p2) {
                    p1 = NULL;
                    break;
                }
            }
            if (p1->data == *e)
                break;
        }
        if ((*L)->data == *e) /*����Ե�һ���ڵ���ж�*/
            p1 = *L;
    }
    if (p1 != NULL) {
        if (p1 != *L) {                             //Ŀ�겻�ǵ�һ���ڵ�
            p->next = p1->next;
        }
        else {                                      //Ŀ���ǵ�һ���ڵ�
            *L = p1->next;
            if (p->next == p1) { /*��ѭ����������*/
                if (p->next == p) /*Ψһһ���ڵ�*/
                    *L = NULL;
                p->next = *L; /*��ѭ������ȥ*/
            }
        }
        free(p1);
        result = SUCCESS;
    }
    return result;
}

void TraverseList(LinkedList L, void (*visit)(ElemType e)) {
    LNode* p1, * p2;
    p1 = p2 = L;
    while (p1 != NULL) {
        visit(p1->data);
        p1 = p1->next;
        if (p2 != NULL && p2->next != NULL) {
            p2 = p2->next->next;
            if (p1 == p2) {
                break;
            }
        }
    }
}

LNode* SearchList(LinkedList* L, ElemType n) {                  //��������Ҳ������ͷ�ļ�
    LNode* p1, * p2;                                        //��ʱ��Ҫ�õ��������ڵ��ָ�����԰ѷ���ֵ�ĳ���ָ��
    p1 = p2 = *L;
    while (p1 != NULL) {
        if (p1->data == n)
            break;
        p1 = p1->next;                                      //p1ÿ����һ���ڵ�
        if (p2 != NULL && p2->next != NULL) {
            p2 = p2->next->next;                            //p2ÿ���������ڵ㣬����NULL��ͣ��
            if (p1 == p2) {                                 //���ڽ������������жϣ�p1��p2����������
                p1 = NULL;                                  //�������Ҫ�����ĺ������������Ƶ��㷨
                break;
            }
        }
    }
    return p1;
}

Status ReverseList(LinkedList* L) {             //�ǵݹ鷴��
    Status result = (Status)ERROR;
    LNode* p1, * p2, * p;
    int cnt = 0;
    p = p1 = p2 = *L;
    while (p1 != NULL) {
        cnt += 1;
        p2 = p1->next;
        if (cnt == 1)
            p1->next = NULL;
        else
            p1->next = p;
        p = p1;                 //��¼������ͷָ��
        p1 = p2;
    }
    *L = p;                     //��¼������ͷָ��
    result = SUCCESS;
    return result;
}

Status IsLoopList(LinkedList L) {
    Status result = (Status)ERROR;
    LNode* p1, * p2;
    p1 = p2 = L;
    while (p1 != NULL) {
        p1 = p1->next;
        if (p2 != NULL && p2->next != NULL) {
            p2 = p2->next->next;
            if (p1 == p2) {
                result = SUCCESS;
                break;
            }
        }
        else
            break;
    }
    return result;
}

LNode* ReverseEvenList(LinkedList* L) {             //���������ʵ���Բ��÷���ͷָ��İ�
    LNode* p1, * p2, * after, * before, * head;                   //�о�ֱ���ö���ָ��Ļ��õ�
    int cnt = 0;
    p1 = head = before = *L;
    while (p1 != NULL && p1->next != NULL) {
        cnt += 1;
        p2 = p1->next;
        if (cnt == 1) {
            head = p2;
        }
        else {
            before->next = p2;
        }
        after = p2->next;
        p2->next = p1;
        p1->next = after;
        before = p1;
        p1 = after;
    }
    return head;
}

LNode* FindMidNode(LinkedList* L) {
    LNode* p1, * p2, * p;
    p1 = p2 = *L;
    if (IsLoopList(*L)) {
        p = NULL; /*����ɻ����ؿ�ָ��*/
    }
    else {
        while (p2 != NULL && p2->next != NULL) {            //�Բ���Ϊ2��p2��Ϊ�ж�����
            p2 = p2->next->next;                           //p2ֹͣʱ��p1��Ϊ�е�
            p1 = p1->next;
        }
        p = p1;
    }
    return p;
}

Status CreateList(LinkedList* L) {
    Status result = (Status)ERROR;
    int n = 0;
    int data;
    int cnt;
    LNode* p1, * p2;
    if (InitList(L)) {
        printf("��ʼ������ɹ�\n");
        printf("��������Ҫ�����Ľڵ�����");
        if (scanf_s("%d", &n) == 0) { /*�Ƿ�����*/
            DestroyList(L);
            printf("\n*** �Ƿ����룬�������� ***\n");
            goto End_CreateList;
        }
        p1 = p2 = *L;
        for (cnt = 0; cnt < n; cnt++) {
            printf("�������%d���ڵ�����ݣ�", cnt + 1);
            if (scanf_s("%d", &data) == 0) { /*�Ƿ�����*/
                p2->next = NULL; /*��β*/
                DestroyList(L);
                printf("\n*** �Ƿ����룬�������� ***\n");
                goto End_CreateList;
            }
            p1->data = data; /*���ڵ��������*/
            p2 = p1;
            p1 = (LNode*)malloc(sizeof(LNode)); /*�����½ڵ�*/
            if (p1 == NULL) {
                fprintf(stderr, "����ռ�ʧ�ܡ�\n");
                exit(EXIT_FAILURE);
            }
            else {
                p2->next = p1; /*������һ�ڵ�*/
            }
        }
        p2->next = NULL; /*��β*/
        result = SUCCESS;
    }
    else {
        printf("��ʼ������ʧ��\n");
    }
End_CreateList:;
    Fresh_Buffer(); /*������뻺����*/
    return result;
}

Status CircuLinkLisk(LinkedList* L) {
    Status result = (Status)ERROR;
    LNode* p1, * p2, * p;
    p1 = p2 = *L;
    if (p1 != NULL && p1->next != NULL) {
        while (p1->next != NULL) {
            p = p1; /*��һ��ָ���¼p1����һ���ڵ�*/
            p1 = p1->next;
            if (p2 != NULL && p2->next != NULL) {
                p2 = p2->next->next;
                if (p1 == p2) {
                    p1 = p; /*�Ѿ��ɻ���p1�ص���һ���ڵ�*/
                    break;
                }
            }
        }
        p1->next = *L; /*ͷβ����*/
        result = SUCCESS;
    }
    return result;
}

LNode* ReverseList_recur(LinkedList* L) { /*�ݹ鷴��*/
    LNode* p, * q;
    if ((*L)->next == NULL) { /*�߽�������ԭ����β����ֱ�ӷ���*/
        p = *L;
    }
    else {
        q = *L; /*qָ���¼ԭ����β��*/
        *L = (*L)->next;
        p = ReverseList_recur(L);
        p->next = q;
        q->next = NULL; /*ԭ�����βָ��NULL*/
        p = q;
    }
    return p; /*�����������β��*/
}