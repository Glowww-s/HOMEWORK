#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#define E 21
#define W 61

typedef  struct StackNode
{
	NodePtr node;
    int n;
	struct StackNode* next;
}StackNode, * LinkStackPtr;

typedef  struct  LinkStack
{
	LinkStackPtr top;
	int	count;
}LinkStack;

typedef struct node
{
    NodePtr node;                   //数据域指针
    struct node* next;            //指向当前结点的下一结点
} LNode;

typedef struct Lqueue
{
    LNode* front;                   //队头
    LNode* rear;                    //队尾
    size_t length;            //队列长度
} LQueue;



int Menu_Main(); /*主菜单*/
int Menu_ior(); /*递归选择三级菜单*/
int Menu_ThreeOrder(BinarySortTreePtr); /*二级菜单*/

void HideCursor(); //隐藏光标
void ShowCursor(); //显示光标
char MenuChoose(const char(*menu)[W], int m); //选择功能,m->项数
void HLshow(const char(*p)[W], int n); //高亮显示
void Stop(void); /*暂停*/
void Fresh_Buffer(void); /*刷新缓冲区*/
void Visit(NodePtr p);

#endif // QUEUE_H_INCLUDED
