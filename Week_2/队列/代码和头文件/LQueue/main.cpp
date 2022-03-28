#include "../head/LQueue.h" 
#include <iostream>

int Menu();
void Stop(void); /*��ͣ*/
void Fresh_Buffer(void); /*ˢ�»�����*/

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
		case 1: /*��ʼ������*/
			if (state) {
				printf(" *** �����Ѵ��ڣ��������ٶ��С� *** \n");
			}
			else {
				Q = (LQueue*)malloc(sizeof(LQueue));
				InitLQueue(Q);
				printf("���г�ʼ���ɹ���\n");
				state = TRUE;
			}
			Stop();
			break;
		case 2: /*���*/
			if (state) {
				data = (void*)malloc(50);
				if (EnLQueue(Q, data)) {
					printf("��ӳɹ���\n");
					datatype[Q->length - 1] = type; /*�������¼�������ͣ�����*/
					datatype[Q->length] = 0;		/*����ͷ��Ӧ����ͷ*/
				}
				else {
					printf("���ʧ�ܣ�\n");
					free(data);
				}
			}
			else {
				printf(" *** ���в����ڣ����ȳ�ʼ�����С� *** \n");
			}
			Stop();
			break;
		case 3: /*����*/
			if (state) {
				if (DeLQueue(Q))
					printf("���ӳɹ���\n");
				else
					printf("����ʧ�ܣ�\n");
			}
			else {
				printf(" *** ���в����ڣ����ȳ�ʼ�����С� *** \n");
			}
			Stop();
			break;
		case 4: /*��������Ԫ��*/
			if (state) {
				if (TraverseLQueue(Q, LPrint))
					printf("��������Ԫ�سɹ���\n");
				else
					printf("��������Ԫ��ʧ�ܣ�\n");
			}
			else {
				printf(" *** ���в����ڣ����ȳ�ʼ�����С� *** \n");
			}
			Stop();
			break;
		case 5: /*�鿴��ͷԪ��*/
			if (state) {
				e = (void*)malloc(50);
				if (GetHeadLQueue(Q, e))
					printf("�鿴��ͷԪ�سɹ���\n");
				else
					printf("�鿴��ͷԪ��ʧ�ܣ�\n");
				free(e);
			}
			else {
				printf(" *** ���в����ڣ����ȳ�ʼ�����С� *** \n");
			}
			Stop();
			break;
		case 6: /*�ж��Ƿ�Ϊ��*/
			if (state) {
				if (IsEmptyLQueue(Q))
					printf("����Ϊ�ա�\n");
				else
					printf("���в�Ϊ�ա�\n");
			}
			else {
				printf(" *** ���в����ڣ����ȳ�ʼ�����С� *** \n");
			}
			Stop();
			break;
		case 7: /*��ⳤ��*/
			if (state) {
				if (LengthLQueue(Q))
					printf("�����г��ȳɹ���\n");
				else
					printf("�����г���ʧ�ܣ�\n");
			}
			else {
				printf(" *** ���в����ڣ����ȳ�ʼ�����С� *** \n");
			}
			Stop();
			break;
		case 8: /*��ն���*/
			if (state) {
				ClearLQueue(Q);
				printf("��ն��гɹ���\n");
			}
			else {
				printf(" *** ���в����ڣ����ȳ�ʼ�����С� *** \n");
			}
			Stop();
			break;
		case 9: /*���ٶ���*/
			if (state) {
				DestoryLQueue(Q);
				state = FALSE;
				printf("���ٶ��гɹ���\n");
			}
			else {
				printf(" *** ���в����ڣ����ȳ�ʼ�����С� *** \n");
			}
			Stop();
			break;
		}
	}
	return 0;
}