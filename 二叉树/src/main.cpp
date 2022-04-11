#include <iostream>
#include <Windows.h>
#include "../inc/binary_sort_tree.h"
#include "../inc/tools.h"

int main() {
    HideCursor();
    system("mode con cols=60 lines=21");
    int n;
    BinarySortTreePtr tree; 
    tree = (BinarySortTreePtr)malloc(sizeof(BinarySortTree));
    if (BST_init(tree) == 0) { /*�������ǰ�ȳ�ʼ��һ����*/
        fprintf(stderr, "*** �����������ĳ�ʼ��ʧ�� ***\n");
        exit(EXIT_FAILURE);
    }
    while (true) {
        switch (Menu_Main()) {
        case 1: /*����*/
            ShowCursor();
            printf("��������Ҫ���ҵ����ݣ�");
            if (scanf_s("%d", &n) == 0) {
                printf("*** �Ƿ����룬�������� ***\n");
            }
            else {
                if(BST_search(tree, n))
                    printf("*** �����ݴ������� ***\n");
                else
                    printf("*** �����ݲ��������� ***\n");
            }
            Fresh_Buffer();
            HideCursor();
            Stop();
            break;
        case 2: /*����*/
            ShowCursor();
            printf("��������Ҫ��������ݣ�");
            if (scanf_s("%d", &n) == 0) {
                printf("*** �Ƿ����룬�������� ***\n");
            }
            else {
                if (BST_insert(tree, n))
                    printf("*** ����ɹ� ***\n");
                else
                    printf("*** ����ʧ�� ***\n");
            }
            Fresh_Buffer();
            HideCursor();
            Stop();
            break;
        case 3: /*ɾ��*/
            ShowCursor();
            printf("��������Ҫɾ�������ݣ�");
            if (scanf_s("%d", &n) == 0) {
                printf("*** �Ƿ����룬�������� ***\n");
            }
            else {
                if (BST_delete(tree, n))
                    printf("*** ɾ���ɹ� ***\n");
                else
                    printf("*** ɾ��ʧ�� ***\n");
            }
            Fresh_Buffer();
            HideCursor();
            Stop();
            break;
        case 4: /*�������*/
            Menu_ThreeOrder(tree);
            break;
        case 5: /*��α���*/
            BST_levelOrder(tree, Visit);
            Stop();
            break;
        }
        Sleep(150);
    }
    return 0;
}
