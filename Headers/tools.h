#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#define E 21
#define W 61

void HideCursor(); //���ع��
void ShowCursor(); //��ʾ���
char MenuChoose(const char(*menu)[W], int m); //ѡ����,m->����
void HLshow(const char(*p)[W], int n); //������ʾ
int Menu_Main(); /*���˵�*/
int Menu_LargeData(); /*�����������β��Զ����˵�*/
int Menu_SmallData(); /*С��������β��Զ����˵�*/
int Menu_Apply(); /*Ӧ��������˵�*/
int Menu_Sort(int scale, int n); /*�����˵�����ѡ�������㷨*/

void DataSave(int scale); /*���ɲ���������*/
int* DataRead(void); /*��ȡ����*/

void Stop(void); /*��ͣ*/
void Fresh_Buffer(void); /*ˢ�»�����*/

#endif // QUEUE_H_INCLUDED
