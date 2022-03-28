#include "../head/LQueue.h" 
#include <iostream>

Status GetData(void* data); /*��ȡ��������*/
void MoveForward(int n); /*��������ǰ��һλ*/

/**
 *  @name        : void InitLQueue(LQueue *Q)
 *    @description : ��ʼ������
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void InitLQueue(LQueue *Q){
	Q->front = NULL;
	Q->rear = NULL;
	Q->length = 0;
}

/**
 *  @name        : void DestoryLQueue(LQueue *Q)
 *    @description : ���ٶ���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void DestoryLQueue(LQueue *Q){
	ClearLQueue(Q);
	free(Q);
}

/**
 *  @name        : Status IsEmptyLQueue(const LQueue *Q)
 *    @description : �������Ƿ�Ϊ��
 *    @param         Q ����ָ��Q
 *    @return         : ��-TRUE; δ��-FALSE
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue *Q){
	Status state = FALSE;
	if (Q->front == NULL && Q->rear == NULL)
		state = TRUE;
	return state;
}

/**
 *  @name        : Status GetHeadLQueue(LQueue *Q, void *e)
 *    @description : �鿴��ͷԪ��
 *    @param         Q e ����ָ��Q,��������ָ��e
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ��
 */
Status GetHeadLQueue(LQueue *Q, void *e){
	Status state = FALSE;
	Node* p;
	if (IsEmptyLQueue(Q)) {
		printf(" *** ����Ϊ�գ��޷������� *** \n");
	}
	else {
		p = Q->front;
		e = p->data;
		type = datatype[0]; /*��ȡ��ͷ�ڵ���������*/
		LPrint(e);
		state = TRUE;
	}
	return state;
}

/**
 *  @name        : int LengthLQueue(LQueue *Q)
 *    @description : ȷ�����г���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
int LengthLQueue(LQueue *Q){
	Status state = FALSE;
	int cnt = 0;
	Node* p = Q->front;
	while (p != NULL) { /*�������в�����*/
		p = p->next;
		cnt += 1;
	}
	if (cnt == Q->length) { /*��֤�����Ƿ���ȷ*/
		printf("���г���Ϊ��%d\n", Q->length);
		state = TRUE;
	}
	return state;
}

/**
 *  @name        : Status EnLQueue(LQueue *Q, void *data)
 *    @description : ��Ӳ���
 *    @param         Q ����ָ��Q,�������ָ��data
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ�Ϊ��
 */
Status EnLQueue(LQueue *Q, void *data){
	Status state = FALSE;
	Node* p;
	p = (Node*)malloc(sizeof(Node));
	if (p == NULL) {
		fprintf(stderr, " *** �����½ڵ�ʧ�ܣ� *** \n");
		exit(EXIT_FAILURE);
	}
	p->next = NULL; /*Ϊ�½ڵ��������*/
	if (GetData(data)) {
		p->data = data;
		if (Q->length == 0) {
			Q->front = p;
			Q->rear = p;
		}
		else {
			Q->rear->next = p;
			Q->rear = p;
		}
		Q->length += 1;
		state = TRUE;
	}
	else {
		free(p); /*��ȡ����ʧ�ܣ��ͷ��ڴ�ռ�*/
	}
	return state;
}

/**
 *  @name        : Status DeLQueue(LQueue *Q)
 *    @description : ���Ӳ���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
Status DeLQueue(LQueue *Q){
	Status state = FALSE;
	Node* p;
	if (IsEmptyLQueue(Q)) {
		printf(" *** ����Ϊ�գ��޷������� *** \n");
	}
	else {
		p = Q->front;
		Q->front = Q->front->next;
		Q->length -= 1;
		if (Q->length == 0 && Q->front == NULL) /*��������Ψһ�ڵ�����*/
			Q->rear = NULL;
		type = datatype[0];
		MoveForward(Q->length);
		LPrint(p->data);
		free(p);
		state = TRUE;
	}
	return state;
}

/**
 *  @name        : void ClearLQueue(AQueue *Q)
 *    @description : ��ն���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void ClearLQueue(LQueue *Q){
	Node* p;
	while (Q->front != NULL) {
		p = Q->front; /*��¼Ҫ�ͷŵĽڵ�*/
		Q->front = Q->front->next;
		Q->length -= 1;
		free(p);
	}
	Q->rear = NULL; /*��������ո�β*/
}

/**
 *  @name        : Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
 *    @description : ������������
 *    @param         Q ����ָ��Q����������ָ��foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q)){
	Status state = FALSE;
	int cnt = 0;
	Node* p;
	if(IsEmptyLQueue(Q)){
		printf(" *** ����Ϊ�գ��޷������� *** \n");
	}
	else {
		printf("����Ԫ�ش�ͷ��β�����ǣ�\n");
		for (p = Q->front; p != NULL; p = p->next) { /*�����ڵ�*/
			type = datatype[cnt]; /*��ȡ��Ӧ����������*/
			LPrint(p->data);
			cnt += 1;
		}
		state = TRUE;
	}
	return state;
}

/**
 *  @name        : void LPrint(void *q)
 *    @description : ��������
 *    @param         q ָ��q
 
 *  @notice      : None
 */
void LPrint(void *q){
	switch (type) { /*�����ı��ǿ��ת��ָ���������*/
	case 'd':
		printf("%d\n", *((int*)q));
		break;
	case 'f':
		printf("%lf\n", *((double*)q));
		break;
	case 'c':
		printf("%c\n", *((char*)q));
		break;
	case 's':
		printf("%s\n", (char*)q);
	}
}

/**************************************************************
 *    End-Multi-Include-Prevent Section
 **************************************************************/
 // LQUEUE_H_INCLUDED
