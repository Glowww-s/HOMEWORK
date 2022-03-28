#include "../head/LQueue.h" 
#include <iostream>

Status GetData(void* data); /*获取泛型数据*/
void MoveForward(int n); /*整个数组前移一位*/

/**
 *  @name        : void InitLQueue(LQueue *Q)
 *    @description : 初始化队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void InitLQueue(LQueue *Q){
	Q->front = NULL;
	Q->rear = NULL;
	Q->length = 0;
}

/**
 *  @name        : void DestoryLQueue(LQueue *Q)
 *    @description : 销毁队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void DestoryLQueue(LQueue *Q){
	ClearLQueue(Q);
	free(Q);
}

/**
 *  @name        : Status IsEmptyLQueue(const LQueue *Q)
 *    @description : 检查队列是否为空
 *    @param         Q 队列指针Q
 *    @return         : 空-TRUE; 未空-FALSE
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
 *    @description : 查看队头元素
 *    @param         Q e 队列指针Q,返回数据指针e
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否空
 */
Status GetHeadLQueue(LQueue *Q, void *e){
	Status state = FALSE;
	Node* p;
	if (IsEmptyLQueue(Q)) {
		printf(" *** 队列为空，无法操作。 *** \n");
	}
	else {
		p = Q->front;
		e = p->data;
		type = datatype[0]; /*获取队头节点数据类型*/
		LPrint(e);
		state = TRUE;
	}
	return state;
}

/**
 *  @name        : int LengthLQueue(LQueue *Q)
 *    @description : 确定队列长度
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
int LengthLQueue(LQueue *Q){
	Status state = FALSE;
	int cnt = 0;
	Node* p = Q->front;
	while (p != NULL) { /*遍历队列并计数*/
		p = p->next;
		cnt += 1;
	}
	if (cnt == Q->length) { /*验证长度是否正确*/
		printf("队列长度为：%d\n", Q->length);
		state = TRUE;
	}
	return state;
}

/**
 *  @name        : Status EnLQueue(LQueue *Q, void *data)
 *    @description : 入队操作
 *    @param         Q 队列指针Q,入队数据指针data
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否为空
 */
Status EnLQueue(LQueue *Q, void *data){
	Status state = FALSE;
	Node* p;
	p = (Node*)malloc(sizeof(Node));
	if (p == NULL) {
		fprintf(stderr, " *** 申请新节点失败！ *** \n");
		exit(EXIT_FAILURE);
	}
	p->next = NULL; /*为新节点填充数据*/
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
		free(p); /*获取数据失败，释放内存空间*/
	}
	return state;
}

/**
 *  @name        : Status DeLQueue(LQueue *Q)
 *    @description : 出队操作
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
Status DeLQueue(LQueue *Q){
	Status state = FALSE;
	Node* p;
	if (IsEmptyLQueue(Q)) {
		printf(" *** 队列为空，无法操作。 *** \n");
	}
	else {
		p = Q->front;
		Q->front = Q->front->next;
		Q->length -= 1;
		if (Q->length == 0 && Q->front == NULL) /*出掉队列唯一节点的情况*/
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
 *    @description : 清空队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void ClearLQueue(LQueue *Q){
	Node* p;
	while (Q->front != NULL) {
		p = Q->front; /*记录要释放的节点*/
		Q->front = Q->front->next;
		Q->length -= 1;
		free(p);
	}
	Q->rear = NULL; /*清除结束收个尾*/
}

/**
 *  @name        : Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
 *    @description : 遍历函数操作
 *    @param         Q 队列指针Q，操作函数指针foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q)){
	Status state = FALSE;
	int cnt = 0;
	Node* p;
	if(IsEmptyLQueue(Q)){
		printf(" *** 队列为空，无法操作。 *** \n");
	}
	else {
		printf("队列元素从头到尾依次是：\n");
		for (p = Q->front; p != NULL; p = p->next) { /*遍历节点*/
			type = datatype[cnt]; /*获取对应的数据类型*/
			LPrint(p->data);
			cnt += 1;
		}
		state = TRUE;
	}
	return state;
}

/**
 *  @name        : void LPrint(void *q)
 *    @description : 操作函数
 *    @param         q 指针q
 
 *  @notice      : None
 */
void LPrint(void *q){
	switch (type) { /*按定的标记强制转换指针类型输出*/
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
