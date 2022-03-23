#include <iostream>
#include <linkedList.h>
#include <conio.h>
#include <Windows.h>

void Fresh_Buffer(void); /*刷新缓冲区*/

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

void DestroyList(LinkedList* L) {                           //销毁
    LNode* p1, * p2, * p;
    p1 = p2 = *L;
    if (IsLoopList(*L)) {                               //解环
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
    while (p1 != NULL) {                                //释放单链表
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
        while (p1->next != NULL) {                                //搜索目标节点p1
            p = p1;
            p1 = p1->next; /*直接跳过第一个，从第二个开始判断*/
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
        if ((*L)->data == *e) /*补充对第一个节点的判断*/
            p1 = *L;
    }
    if (p1 != NULL) {
        if (p1 != *L) {                             //目标不是第一个节点
            p->next = p1->next;
        }
        else {                                      //目标是第一个节点
            *L = p1->next;
            if (p->next == p1) { /*是循环链表的情况*/
                if (p->next == p) /*唯一一个节点*/
                    *L = NULL;
                p->next = *L; /*把循环连回去*/
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

LNode* SearchList(LinkedList* L, ElemType n) {                  //搜索函数也改了下头文件
    LNode* p1, * p2;                                        //有时需要用到搜索到节点的指针所以把返回值改成了指针
    p1 = p2 = *L;
    while (p1 != NULL) {
        if (p1->data == n)
            break;
        p1 = p1->next;                                      //p1每次走一个节点
        if (p2 != NULL && p2->next != NULL) {
            p2 = p2->next->next;                            //p2每次走两个节点，遇到NULL就停下
            if (p1 == p2) {                                 //用于解决环形链表的判断（p1，p2相遇结束）
                p1 = NULL;                                  //大多数需要遍历的函数都用了类似的算法
                break;
            }
        }
    }
    return p1;
}

Status ReverseList(LinkedList* L) {             //非递归反向
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
        p = p1;                 //记录新链的头指针
        p1 = p2;
    }
    *L = p;                     //记录反向后的头指针
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

LNode* ReverseEvenList(LinkedList* L) {             //这个函数其实可以不用返回头指针的吧
    LNode* p1, * p2, * after, * before, * head;                   //感觉直接用二重指针改还好点
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
        p = NULL; /*链表成环返回空指针*/
    }
    else {
        while (p2 != NULL && p2->next != NULL) {            //以步长为2的p2作为判断条件
            p2 = p2->next->next;                           //p2停止时，p1即为中点
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
        printf("初始化链表成功\n");
        printf("请输入你要构建的节点数：");
        if (scanf_s("%d", &n) == 0) { /*非法输入*/
            DestroyList(L);
            printf("\n*** 非法输入，请检查输入 ***\n");
            goto End_CreateList;
        }
        p1 = p2 = *L;
        for (cnt = 0; cnt < n; cnt++) {
            printf("请输入第%d个节点的数据：", cnt + 1);
            if (scanf_s("%d", &data) == 0) { /*非法输入*/
                p2->next = NULL; /*收尾*/
                DestroyList(L);
                printf("\n*** 非法输入，请检查输入 ***\n");
                goto End_CreateList;
            }
            p1->data = data; /*往节点填充数据*/
            p2 = p1;
            p1 = (LNode*)malloc(sizeof(LNode)); /*申请新节点*/
            if (p1 == NULL) {
                fprintf(stderr, "申请空间失败。\n");
                exit(EXIT_FAILURE);
            }
            else {
                p2->next = p1; /*连接下一节点*/
            }
        }
        p2->next = NULL; /*收尾*/
        result = SUCCESS;
    }
    else {
        printf("初始化链表失败\n");
    }
End_CreateList:;
    Fresh_Buffer(); /*清空输入缓冲区*/
    return result;
}

Status CircuLinkLisk(LinkedList* L) {
    Status result = (Status)ERROR;
    LNode* p1, * p2, * p;
    p1 = p2 = *L;
    if (p1 != NULL && p1->next != NULL) {
        while (p1->next != NULL) {
            p = p1; /*用一个指针记录p1的上一个节点*/
            p1 = p1->next;
            if (p2 != NULL && p2->next != NULL) {
                p2 = p2->next->next;
                if (p1 == p2) {
                    p1 = p; /*已经成环让p1回到上一个节点*/
                    break;
                }
            }
        }
        p1->next = *L; /*头尾相连*/
        result = SUCCESS;
    }
    return result;
}

LNode* ReverseList_recur(LinkedList* L) { /*递归反向*/
    LNode* p, * q;
    if ((*L)->next == NULL) { /*边界条件：原链表尾部，直接返回*/
        p = *L;
    }
    else {
        q = *L; /*q指针记录原链表尾部*/
        *L = (*L)->next;
        p = ReverseList_recur(L);
        p->next = q;
        q->next = NULL; /*原链表的尾指向NULL*/
        p = q;
    }
    return p; /*返回新链表的尾部*/
}