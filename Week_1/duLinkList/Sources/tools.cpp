#include <duLinkedList.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>

#define H 13

int Menu(void) { /*�����˵�*/
    int i;
    int choice = 0;
    char menu[H][50] = {
        {"                                                 "},
        {"    ----------    1.�����ʼ��     ----------    "},
        {"                                                 "},
        {"    ----------    2.��������       ----------    "},
        {"                                                 "},
        {"    ----------    3.����ڵ㣨ǰ�� ----------    "},
        {"                                                 "},
        {"    ----------    4.����ڵ㣨�� ----------    "},
        {"                                                 "},
        {"    ----------    5.ɾ���ڵ�       ----------    "},
        {"                                                 "},
        {"    ----------    6.��������       ----------    "},
        {"                                                 "},
    };
    system("cls");
    for (i = 0; i < H; i++) {
        printf("%s\n", menu[i]);
    }
    printf("��������ѡ���ܵ���ţ�");
    scanf_s("%d", &choice);
    system("cls");
    return choice;
}

void Stop(void) { /*��ͣ*/
    char c = ' ';
    printf("����س�[Enter]���ز˵�\n");
    do {
        c = _getch();
        Sleep(100);
    } while (c != '\r');
}

void visit(ElemType e) { /*���ʽڵ�����*/
    printf("�ڵ�data��%d\n", int(e));
}

void reset(DuLinkedList* L) { /*�ҵ�����ͷָ��ĺ���*/
    DuLNode* p = *L;
    if (p != NULL) {
        while (p->prior != NULL) { /*��ȡ�����ͷָ��*/
            p = p->prior;
        }
        *L = p;
    }
}