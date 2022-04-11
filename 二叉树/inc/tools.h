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
    NodePtr node;                   //������ָ��
    struct node* next;            //ָ��ǰ������һ���
} LNode;

typedef struct Lqueue
{
    LNode* front;                   //��ͷ
    LNode* rear;                    //��β
    size_t length;            //���г���
} LQueue;



int Menu_Main(); /*���˵�*/
int Menu_ior(); /*�ݹ�ѡ�������˵�*/
int Menu_ThreeOrder(BinarySortTreePtr); /*�����˵�*/

void HideCursor(); //���ع��
void ShowCursor(); //��ʾ���
char MenuChoose(const char(*menu)[W], int m); //ѡ����,m->����
void HLshow(const char(*p)[W], int n); //������ʾ
void Stop(void); /*��ͣ*/
void Fresh_Buffer(void); /*ˢ�»�����*/
void Visit(NodePtr p);

#endif // QUEUE_H_INCLUDED
