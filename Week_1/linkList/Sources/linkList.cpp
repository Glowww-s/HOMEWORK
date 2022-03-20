#include <iostream>
#include <linkedList.h>
#include <conio.h>
#include <Windows.h>

#define H 23

Status CreateList(LinkedList* L);               //创建列表函数
int Menu(void);                          //交互菜单
void Stop(void);                         //暂停
void visit(ElemType e);                        //访问节点数据
Status CircuLinkLisk(LinkedList* L);          //构造循环链表

int main()
{
    Status state = (Status)ERROR;
    LinkedList* tohead;
    int choice;
    int n;
    LNode* p, * q, * mid;
    tohead = (LinkedList*)malloc(sizeof(LinkedList));                //初始化二重指针
    system("mode con cols=70 lines=24");
    while (true) {
        choice = Menu();
        switch (choice) {
        case 1:                                             //创建链表
            if (state)
                DestroyList(tohead);                        //先把之前的销毁再创建新链表
            if (CreateList(tohead)) {
                printf("构造链表成功。\n");
                state = SUCCESS;
            }
            else
                printf("构造链表失败。\n");
            Stop();
            break;
        case 2:                                             //插入新节点
            if (state) {
                printf("请输入你要插入到的位置的前一个结点的数据：");
                scanf_s("%d", &n);
                p = SearchList(tohead, n);
                if (p != NULL) {
                    printf("请输入你要插入节点的数据：");
                    scanf_s("%d", &n);
                    q = (LNode*)malloc(sizeof(LNode));
                    if (q != NULL) {
                        q->data = n;
                        if (InsertList(p, q))
                            printf("插入新节点成功。\n");
                        else
                            printf("插入新节点失败。\n");
                    }
                }
                else
                    printf("没有找到你要插入的前节点！请检查输入！\n");
            }
            else
                printf("未创建链表。\n");
            Stop();
            break;
        case 3:                                             //遍历输出
            if (state)
                TraverseList(*tohead, visit);
            else
                printf("未创建链表。\n");
            Stop();
            break;
        case 4:                                                 //链表反向
            if (state) {
                if (ReverseList(tohead))
                    printf("链表反向成功。\n");
                else
                    printf("链表反向失败。\n");
            }
            else
                printf("未创建链表。\n");
            Stop();
            break;
        case 5:                                             //单链表中点
            if (state) {
                mid = FindMidNode(tohead);
                if (mid != NULL) {
                    printf("单链表中点值为%d\n", mid->data);
                }
                else {
                    printf("链表成环，无法操作。\n");
                }
            }
            else
                printf("未创建链表。\n");
            Stop();
            break;
        case 6:                                             //判断是否成环
            if (state) {
                if (IsLoopList(*tohead))
                    printf("链表成环！！\n");
                else
                    printf("链表未成环！！\n");
            }
            else
                printf("未创建链表。\n");
            Stop();
            break;
        case 7:                                             //删除节点取值
            if (state) {
                printf("请输入需要删除的节点数据：");
                scanf_s("%d", &n);
                if (DeleteList(tohead, &n)) {
                    printf("删除成功\n");
                    if (*tohead == NULL)                //删除唯一节点
                        state = (Status)ERROR;
                }
                else
                    printf("未找到目标节点，删除失败\n");
            }
            else
                printf("未创建链表。\n");
            Stop();
            break;
        case 8:                                         //奇偶反转
            if (state) {
                if (IsLoopList(*tohead)) {
                    printf("链表成环，没必要。\n");
                }
                else {
                    *tohead = ReverseEvenList(tohead);
                    printf("奇偶项已反转。\n");
                }
            }
            else
                printf("未创建链表。\n");
            Stop();
            break;
        case 9:                                             //查询数据
            if (state) {
                printf("请输入想要查询的数据：");
                scanf_s("%d", &n);
                if (SearchList(tohead, n)!=NULL) {
                    printf("该数据位于链表中。\n");
                }
                else {
                    printf("该数据不位于链表中。\n");
                }
            }
            else               
                printf("未创建链表。\n");
            Stop();
            break;
        case 10:                                        //构造循环链表
            if (state) {
                if (CircuLinkLisk(tohead))
                    printf("构造循环链表成功！\n");
                else
                    printf("构造循环链表失败！\n");
            }
            else
                printf("未创建链表。\n");
            Stop();
            break;
        case 0:
            DestroyList(tohead);
            exit(EXIT_SUCCESS);
        }
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
    char menu[H][70] = {
        {"                                                                     "},
        {"      -------------       1.创建新链表           -------------       "},
        {"                                                                     "},
        {"      -------------       2.插入新节点           -------------       "},
        {"                                                                     "},
        {"      -------------       3.输出链表             -------------       "},
        {"                                                                     "},
        {"      -------------       4.链表反向             -------------       "},
        {"                                                                     "},
        {"      -------------       5.找到单链表中点       -------------       "},
        {"                                                                     "},
        {"      -------------       6.判断是否成环         -------------       "},
        {"                                                                     "},
        {"      -------------       7.删除节点取值         -------------       "},
        {"                                                                     "},
        {"      -------------       8.奇偶反转             -------------       "},
        {"                                                                     "},
        {"      -------------       9.查询数据是否位于链表 -------------       "},
        {"                                                                     "},
        {"      -------------       10.构造循环链表        -------------       "},
        {"                                                                     "},
        {"      -------------       0.销毁列表并退出       -------------       "},
        {"                                                                     "},
    };
    system("cls");
    for (i = 0; i < H; i++) {
        printf("%s\n", menu[i]);
    }
    printf("  请输入所选功能的序号：");
    scanf_s("%d", &choice);
    system("cls");
    return choice;
}

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

Status CreateList(LinkedList* L) {
    Status result = (Status)ERROR;
    int n = 0;
    int data;
    LNode* p1, * p2;
    int cnt;
    if (InitList(L)) {
        printf("初始化链表成功\n");
        printf("请输入你要构建的节点数：");
        scanf_s("%d", &n);
        p1 = p2 = *L;
        for (cnt = 0; cnt < n; cnt++) {
            printf("请输入第%d个节点的数据：", cnt + 1);
            scanf_s("%d", &data);
            p1->data = data;                                    //往节点填充数据
            p2 = p1;
            p1 = (LNode*)malloc(sizeof(LNode));                 //申请新节点
            if (p1 == NULL) {
                fprintf(stderr, "申请空间失败。\n");
                exit(EXIT_FAILURE);
            }
            else {
                p2->next = p1;                                  //连接下一节点
            }
        }
        p2->next = NULL;                                        //收尾
        result = SUCCESS;
    }
    else {
        printf("初始化链表失败\n");
    }
    return result;
}

void visit(ElemType e) {                        //访问节点数据
    printf("节点data：%d\n", int(e));
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
        if (p2 != NULL && p2->next != NULL) {
            p2 = p2->next->next;
            if (p1 == p2) {
                break;
            }
        }
        free(p);
    }
}

Status DeleteList(LinkedList* L, ElemType* e) {
    Status result = (Status)ERROR;
    LNode* p1, * p2, * p;
    p1 = p2 = p = *L;
    while (p1 != NULL) {                                //搜索目标节点
        if (p1->data == *e)                             //算法与搜索函数类似
            break;
        p = p1;
        p1 = p1->next;
        if (p2 != NULL && p2->next != NULL) {
            p2 = p2->next->next;
            if (p1 == p2) {
                p1 = NULL;
                break;
            }
        }
    }
    if (p1 != NULL) {
        if (p1 != *L) {                             //目标不是第一个节点
            p->next = p1->next;
        }
        else {                                      //目标是第一个节点
            *L = p1->next;
        }
        free(p1);
        result = SUCCESS;
    }
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

Status CircuLinkLisk(LinkedList* L) {
    Status result = (Status)ERROR;
    LNode* p1, * p2, * p;
    p1 = p2 = *L;
    if (p1 != NULL && p1->next != NULL) {
        while (p1->next != NULL) {
            p = p1;                                         //用一个指针记录p1的上一个节点
            p1 = p1->next;
            if (p2 != NULL && p2->next != NULL) {
                p2 = p2->next->next;
                if (p1 == p2) {
                    p1 = p;                                 //已经成环让p1回到上一个节点
                    break;
                }
            }
        }
        p1->next = *L;                                      //头尾相连
        result = SUCCESS;
    }
    return result;
}

LNode* FindMidNode(LinkedList* L) {
    LNode* p1, * p2, *p;
    p1 = p2 = *L;
    if (IsLoopList(*L)) {
        p = NULL;                                           //链表成环返回空指针
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

Status ReverseList(LinkedList* L) {             //非递归反向
    Status result = (Status)ERROR;
    LNode* p1, * p2, * p;
    int cnt = 0;
    p = p1 = p2 = *L;
    if(IsLoopList(*L)){
        printf("链表成环，没必要。\n");
    }
    else{
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