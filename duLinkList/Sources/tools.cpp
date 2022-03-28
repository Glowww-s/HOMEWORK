#include <iostream>
#include <duLinkedList.h>
#include <conio.h>
#include <Windows.h>

#define H 13

void Fresh_Buffer(void);

int Menu(void) { /*�����˵�*/
    int i;
    int choice = 0;
    char menu[H][50] = {
        {"                                                 "},
        {"    ----------   1.��������        ----------    "},
        {"                                                 "},
        {"    ----------   2.��������        ----------    "},
        {"                                                 "},
        {"    ----------   3.����ڵ㣨ǰ��  ----------    "},
        {"                                                 "},
        {"    ----------   4.����ڵ㣨��  ----------    "},
        {"                                                 "},
        {"    ----------   5.ɾ���ڵ�        ----------    "},
        {"                                                 "},
        {"    ----------   6.���������˳�  ----------    "},
        {"                                                 "},
    };
    system("cls");
    for (i = 0; i < H; i++) {
        printf("%s\n", menu[i]);
    }
    printf("��������ѡ���ܵ���ţ�");
    if (scanf_s("%d", &choice) == 0) {
        choice = OVERFLOW;
    }
    else {
        system("cls");
    }
    Fresh_Buffer();
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

void Visit(ElemType e) { /*���ʽڵ�����*/
    printf("�ڵ�data��%d\n", int(e));
}

void Reset(DuLinkedList* L) { /*�ҵ�����ͷָ��ĺ���*/
    DuLNode* p = *L;
    if (p != NULL) {
        while (p->prior != NULL) { /*��ȡ�����ͷָ��*/
            p = p->prior;
        }
        *L = p;
    }
}

void Fresh_Buffer(void) {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}