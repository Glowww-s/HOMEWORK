#include <iostream>
#include "../head/LinkStack.h" 
//��ջ

//��ʼ��ջ
Status initLStack(LinkStack *s){
	Status state = ERROR;
	if (s == NULL) {
		fprintf(stderr, "error!\n");
		exit(EXIT_FAILURE);
	}
	else {
		s->top = NULL;
		s->count = 0;
	}
	state = SUCCESS;
	return state;
}

//�ж�ջ�Ƿ�Ϊ��
Status isEmptyLStack(LinkStack *s){
	Status state = ERROR;
	if (s->count == 0 && s->top == NULL)
		state = SUCCESS;
	return state;
}

//�õ�ջ��Ԫ��
Status getTopLStack(LinkStack *s,ElemType *e){
	Status state = ERROR;
	*e = s->top->data;
	state = SUCCESS;
	return state;
}

//���ջ
Status clearLStack(LinkStack *s){
	Status state = ERROR;
	StackNode* p;
	int i;
	int n = s->count; /*��¼�ʼ�Ľڵ���*/
	for (i = 0; i < n; i++) {
		p = s->top;
		s->top = s->top->next;
		free(p);
		s->count -= 1;
	}
	state = SUCCESS;
	return state;
}

//����ջ
Status destroyLStack(LinkStack *s){
	Status state = ERROR;
	if (clearLStack(s)) {
		free(s);
		state = SUCCESS;
	}
	return state;
}

//���ջ����
Status LStackLength(LinkStack *s,int *length){
	Status state = ERROR;
	StackNode* p;
	int cnt = 0;
	p = s->top;
	while (p != NULL) {
		p = p->next;
		cnt += 1;
	}
	*length = cnt;
	state = SUCCESS;
	return state;
}

//��ջ
Status pushLStack(LinkStack *s,ElemType data){
	Status state = ERROR;
	StackNode* p;
	p = (StackNode*)malloc(sizeof(StackNode));
	if (p == NULL) {
		fprintf(stderr, "ERROR�������½ڵ�ʧ�ܣ�\n");
		exit(EXIT_FAILURE);
	}
	p->data = data;
	p->next = s->top;
	s->top = p;
	s->count += 1;
	state = SUCCESS;
	return state;
}

//��ջ
Status popLStack(LinkStack *s,ElemType *data){
	Status state = ERROR;
	StackNode* p = s->top;
	if (p != NULL) {
		s->top = s->top->next;
		s->count -= 1;
		*data = p->data;
		free(p);
		state = SUCCESS;
	}
	return state;
}