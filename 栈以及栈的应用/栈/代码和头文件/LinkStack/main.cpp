#include "../head/LinkStack.h" 
#include <iostream>

int Menu();
void Stop(void); /*��ͣ*/
void Fresh_Buffer(void); /*ˢ�»�����*/

int main()
{
    Status state = ERROR;
	int choice;
    int data, length = -1;
    LinkStack* s;
    s = (LinkStack*)malloc(sizeof(LinkStack));
    system("mode con cols=60 lines=18");
	while (true) {
		choice = Menu();
		switch (choice) {
        case 1: /*��ʼ����ջ*/
            if (state) {
                printf("��ջ�Ѵ��ڣ���������ջ��\n");
            }
            else {
                s = (LinkStack*)malloc(sizeof(LinkStack));
                if (initLStack(s)) {
                    printf("��ջ��ʼ���ɹ���\n");
                    state = SUCCESS;
                }
                else
                    printf("��ջ��ʼ��ʧ�ܣ�\n");
            }
            Stop();
            break;
        case 2: /*��ջ*/
            if (state) {
                printf("��������ջ���ݣ�");
                if (scanf_s("%d", &data) == 0) {
                    printf("\n*** �Ƿ����룬�������� ***\n");
                    Fresh_Buffer();
                }
                else {
                    if (pushLStack(s, data))
                        printf("������ջ�ɹ���\n");
                    else
                        printf("������ջʧ�ܡ�\n");
                }
            }
            else {
                printf("��ջ�����ڣ����ȳ�ʼ����ջ��\n");
            }
            Stop();
            break;
        case 3: /*��ջ*/
            if (state) {
                if (isEmptyLStack(s)) {
                    printf("��ջΪ�գ��޷�������\n");
                }
                else {
                    if (popLStack(s, &data))
                        printf("����%d��ջ�ɹ���\n", data);
                    else
                        printf("���ݳ�ջʧ�ܡ�\n");
                }
            }
            else {
                printf("��ջ�����ڣ����ȳ�ʼ����ջ��\n");
            }
            Stop();
            break;
        case 4: /*�õ�ջ��Ԫ��*/
            if (state) {
                if (isEmptyLStack(s)) {
                    printf("��ջΪ�գ��޷�������\n");
                }
                else {
                    if (getTopLStack(s, &data))
                        printf("ջ��Ԫ������Ϊ%d��\n", data);
                    else
                        printf("��ȡջ��Ԫ��ʧ�ܡ�\n");
                }
            }
            else {
                printf("��ջ�����ڣ����ȳ�ʼ����ջ��\n");
            }
            Stop();
            break;
        case 5: /* �ж���ջ�Ƿ�Ϊ��*/
            if (state) {
                if (isEmptyLStack(s)) {
                    printf("��ջΪ�ա�\n");
                }
                else {
                    printf("��ջ��Ϊ�ա�\n");
                }
            }
            else {
                printf("��ջ�����ڣ����ȳ�ʼ����ջ��\n");
            }
            Stop();
            break;
        case 6: /*���ջ����*/
            if (state) {
                if (LStackLength(s, &length) && length == s->count)
                    printf("���ɹ�������Ϊ%d��\n", length);
                else
                    printf("���ʧ�ܡ�\n");
            }
            else {
                printf("��ջ�����ڣ����ȳ�ʼ����ջ��\n");
            }
            Stop();
            break;
        case 7: /*���ջ*/
            if (state) {
                if (clearLStack(s))
                    printf("���ջ�ɹ���\n");
                else
                    printf("���ջʧ�ܡ�\n");
            }
            else {
                printf("��ջ�����ڣ����ȳ�ʼ����ջ��\n");
            }
            Stop();
            break;
        case 8: /*����ջ*/
            if (state) {
                if (destroyLStack(s)) {
                    printf("����ջ�ɹ���\n");
                    state = ERROR;
                }
                else
                    printf("����ջʧ�ܡ�\n");
            }
            else {
                printf("��ջ�����ڣ����ȳ�ʼ����ջ��\n");
            }
            Stop();
            break;
		}
	}
	return 0;
}