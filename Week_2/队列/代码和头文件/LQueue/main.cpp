#include "../head/LQueue.h" 
#include <iostream>

int Menu();
void Stop(void); /*暂停*/
void Fresh_Buffer(void); /*刷新缓冲区*/

int main()
{
	Status state = FALSE;
	int choice;
	void* data, * e;
	LQueue* Q;
	Q = (LQueue*)malloc(sizeof(LQueue));
	system("mode con cols=60 lines=20");
	while (true) {
		choice = Menu();
		switch (choice) {
		case 1: /*初始化队列*/
			if (state) {
				printf(" *** 队列已存在，请先销毁队列。 *** \n");
			}
			else {
				Q = (LQueue*)malloc(sizeof(LQueue));
				InitLQueue(Q);
				printf("队列初始化成功！\n");
				state = TRUE;
			}
			Stop();
			break;
		case 2: /*入队*/
			if (state) {
				data = (void*)malloc(50);
				if (EnLQueue(Q, data)) {
					printf("入队成功！\n");
					datatype[Q->length - 1] = type; /*拿数组记录数据类型？？！*/
					datatype[Q->length] = 0;		/*数组头对应队列头*/
				}
				else {
					printf("入队失败！\n");
					free(data);
				}
			}
			else {
				printf(" *** 队列不存在，请先初始化队列。 *** \n");
			}
			Stop();
			break;
		case 3: /*出队*/
			if (state) {
				if (DeLQueue(Q))
					printf("出队成功！\n");
				else
					printf("出队失败！\n");
			}
			else {
				printf(" *** 队列不存在，请先初始化队列。 *** \n");
			}
			Stop();
			break;
		case 4: /*遍历队内元素*/
			if (state) {
				if (TraverseLQueue(Q, LPrint))
					printf("遍历队内元素成功！\n");
				else
					printf("遍历队内元素失败！\n");
			}
			else {
				printf(" *** 队列不存在，请先初始化队列。 *** \n");
			}
			Stop();
			break;
		case 5: /*查看队头元素*/
			if (state) {
				e = (void*)malloc(50);
				if (GetHeadLQueue(Q, e))
					printf("查看队头元素成功！\n");
				else
					printf("查看队头元素失败！\n");
				free(e);
			}
			else {
				printf(" *** 队列不存在，请先初始化队列。 *** \n");
			}
			Stop();
			break;
		case 6: /*判断是否为空*/
			if (state) {
				if (IsEmptyLQueue(Q))
					printf("队列为空。\n");
				else
					printf("队列不为空。\n");
			}
			else {
				printf(" *** 队列不存在，请先初始化队列。 *** \n");
			}
			Stop();
			break;
		case 7: /*检测长度*/
			if (state) {
				if (LengthLQueue(Q))
					printf("检测队列长度成功！\n");
				else
					printf("检测队列长度失败！\n");
			}
			else {
				printf(" *** 队列不存在，请先初始化队列。 *** \n");
			}
			Stop();
			break;
		case 8: /*清空队列*/
			if (state) {
				ClearLQueue(Q);
				printf("清空队列成功！\n");
			}
			else {
				printf(" *** 队列不存在，请先初始化队列。 *** \n");
			}
			Stop();
			break;
		case 9: /*销毁队列*/
			if (state) {
				DestoryLQueue(Q);
				state = FALSE;
				printf("销毁队列成功！\n");
			}
			else {
				printf(" *** 队列不存在，请先初始化队列。 *** \n");
			}
			Stop();
			break;
		}
	}
	return 0;
}