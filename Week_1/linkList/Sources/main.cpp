#include <iostream>
#include <linkedList.h>
#include <conio.h>
#include <Windows.h>

Status CreateList(LinkedList* L);
Status CircuLinkLisk(LinkedList* L);
LNode* ReverseList_recur(LinkedList* L); /*递归反向*/

int Menu(void);
void Stop(void);
void Visit(ElemType e);
void Fresh_Buffer(void); /*刷新缓冲区*/

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
            state = CreateList(tohead);
            if (state) {
                printf("构造链表成功。\n");
            }
            else {
                printf("构造链表失败。\n");
            }
            Stop();
            break;
        case 2:                                             //插入新节点
            if (state) {
                printf("请输入你要插入到的位置的前一个结点的数据：");
                if (scanf_s("%d", &n) == 0) {
                    printf("\n*** 非法输入，请检查输入 ***\n");
                    Fresh_Buffer(); /*清空输入缓冲区*/
                }
                else {
                    p = SearchList(tohead, n);
                    if (p != NULL) {
                        printf("请输入你要插入节点的数据：");
                        if (scanf_s("%d", &n) == 0) {
                            printf("\n*** 非法输入，请检查输入 ***\n");
                            
                        }
                        else {
                            q = (LNode*)malloc(sizeof(LNode));
                            if (q != NULL) {
                                q->data = n;
                                if (InsertList(p, q))
                                    printf("插入新节点成功。\n");
                                else
                                    printf("插入新节点失败。\n");
                            }
                        }
                        Fresh_Buffer(); /*清空输入缓冲区*/
                    }
                    else
                        printf("没有找到你要插入的前节点！请检查输入！\n");
                }
            }
            else
                printf("未创建链表。\n");
            Stop();
            break;
        case 3:                                             //遍历输出
            if (state)
                TraverseList(*tohead, Visit);
            else
                printf("未创建链表。\n");
            Stop();
            break;
        case 4:                                                 //链表反向
            if (state) {
                if (IsLoopList(*tohead)) {
                    printf("链表成环，没必要。\n");
                }
                else {
                    /*非递归反向*/
                    //if (ReverseList(tohead))
                    //    printf("链表反向成功。\n");
                    //else
                    //    printf("链表反向失败。\n");

                    /*递归反向*/
                    p = *tohead;
                    if (ReverseList_recur(tohead) == p) /*判断之前的头是否等于现在的尾*/
                        printf("链表反向成功。\n");
                    else
                        printf("链表反向失败。\n");
                }
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
                if (scanf_s("%d", &n) == 0) {
                    printf("\n*** 非法输入，请检查输入 ***\n");
                    
                }
                else {
                    if (DeleteList(tohead, &n)) {
                        printf("删除成功\n");
                        if (*tohead == NULL)                //删除唯一节点
                            state = (Status)ERROR;
                    }
                    else
                        printf("未找到目标节点，删除失败\n");
                }
                Fresh_Buffer(); /*清空输入缓冲区*/
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
                if (scanf_s("%d", &n) == 0) {
                    printf("\n*** 非法输入，请检查输入 ***\n");
                    
                }
                else {
                    if (SearchList(tohead, n) != NULL) {
                        printf("该数据位于链表中。\n");
                    }
                    else {
                        printf("该数据不位于链表中。\n");
                    }
                }
                Fresh_Buffer(); /*清空输入缓冲区*/
            }
            else               
                printf("未创建链表。\n");
            Stop();
            break;
        case 10: /*构造循环链表*/
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
            if (state)
                DestroyList(tohead);
            exit(EXIT_SUCCESS);
        }
        Sleep(180);
    }
}