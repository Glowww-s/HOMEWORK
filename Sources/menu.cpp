#include "../Headers/sort.h"
#include "../Headers/tools.h"
#include <iostream>
#include <time.h>

int Menu_Main() /*���˵�*/
{
    char menu[E][W] = {
        {"                                                            "},
        {"                     <<<<< ���˵� >>>>>                     "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"        --------      �����������β���      --------        "},
        {"                                                            "},
        {"                                                            "},
        {"        --------      С��������β���      --------        "},
        {"                                                            "},
        {"                                                            "},
        {"        --------        ����Ӧ����          --------        "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"    *** tips:������ʹ�����¼��ͻس���[Enter]����ѡ�� ***    "},
        {"                                                            "},
        {"                                                            "},
    };
    return MenuChoose(menu, 3);
}

int Menu_LargeData() /*�����������β��Զ����˵�*/
{
    int scale;
    char menu[E][W] = {
        {"                                                            "},
        {"                <<<<< �������ݵ������� >>>>>                "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"         --------          10000           --------         "},
        {"                                                            "},
        {"                                                            "},
        {"         --------          50000           --------         "},
        {"                                                            "},
        {"                                                            "},
        {"         --------          200000          --------         "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                *** ��[Esc]���������˵� ***                 "},
        {"                                                            "},
    };
    switch (MenuChoose(menu, 3)) {
    case 1:
        scale = 1e4;
        Menu_Sort(scale, 1);
        break;
    case 2:
        scale = 5e4;
        Menu_Sort(scale, 1);
        break;
    case 3:
        scale = 2e5;
        Menu_Sort(scale, 1);
        break;
    case -1:
        break;
    }
    return 0;
}

int Menu_SmallData() /*С��������β��Զ����˵�*/
{
    int n;
    char menu[E][W] = {
        {"                                                            "},
        {"                <<<<< �������ݵ������� >>>>>                "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"         --------       100��*10k��        --------         "},
        {"                                                            "},
        {"                                                            "},
        {"         --------       100��*100k��       --------         "},
        {"                                                            "},
        {"                                                            "},
        {"         --------       100��*1000k��      --------         "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                *** ��[Esc]���������˵� ***                 "},
        {"                                                            "},
    };
    switch (MenuChoose(menu, 3)) {
    case 1:
        n = 1e4;
        Menu_Sort(100, n);
        break;
    case 2:
        n = 1e5;
        Menu_Sort(100, n);
        break;
    case 3:
        n = 1e6;
        Menu_Sort(100, n);
        break;
    }
    return 0;
}

int Menu_Apply() /*Ӧ��������˵�*/
{
    int data1[7] = { 1,2,1,0,2,0,0 };
    int data2[7] = { 5,2,8,4,3,7,6 };
    char menu[E][W] = {
        {"                                                            "},
        {"                     <<<<< Ӧ���� >>>>>                     "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"         --------         ��ɫ����         --------         "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"        -------- �����������ҵ���K��/С���� --------        "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                *** ��[Esc]���������˵� ***                 "},
        {"                                                            "},
    };
    switch (MenuChoose(menu, 2)) {
    case 1:
        ColorSort(data1, 7);
        break;
    case 2:
        FindSpecificSize(data2, 7);
        break;
    }
    return 0;
}

int Menu_Sort(int scale, int n) /*�����˵�����ѡ�������㷨*/
{
    int total = 0; /*��ʱ��*/
    clock_t start, diff;
    int choice;
    int i, j;
    int max;
    int* data, * temp;
    char menu[E][W] = {
        {"                                                            "},
        {"                  <<<<< �����㷨ѡ�� >>>>>                  "},
        {"                                                            "},
        {"                                                            "},
        {"         --------       ��������             --------       "},
        {"                                                            "},
        {"                                                            "},
        {"         --------       �鲢����             --------       "},
        {"                                                            "},
        {"                                                            "},
        {"         --------       ��������(�ݹ��)     --------       "},
        {"                                                            "},
        {"                                                            "},
        {"         --------       ��������             --------       "},
        {"                                                            "},
        {"                                                            "},
        {"         --------       ������������         --------       "},
        {"                                                            "},
        {"                                                            "},
        {"                *** ��[Esc]���������˵� ***                 "},
        {"                                                            "},
    };
    choice = MenuChoose(menu, 5);
    for (i = 0; i < n; i++) {
        DataSave(scale);
        data = DataRead(); /*��ȡ����Ϊscale������*/
        temp = (int*)calloc(scale, sizeof(int));
        start = clock();
        switch (choice) {
        case 1: /*����*/
            insertSort(data, scale);
            break;
        case 2: /*�鲢*/
            MergeSort(data, 0, scale - 1, temp);
            break;
        case 3: /*����*/
            QuickSort_Recursion(data, 0, scale - 1);
            break;
        case 4: /*��������*/
            max = *data;
            for (j = 0; j < scale; j++) {
                if (max < *(data + j)) {
                    max = *(data + j);
                }
            }
            CountSort(data, scale, max);
            break;
        case 5: /*��������*/
            RadixCountSort(data, scale);
            break;
        }
        diff = clock() - start; 
        total += diff; /*�ۼ��ܺ�ʱ*/
        free(data);
        free(temp);
    }
    /*���������Ϣ*/
    switch (choice) {
    case 1:
        printf("��������\n");
        break;
    case 2:
        printf("�鲢����\n");
        break;
    case 3:
        printf("��������\n");
        break;
    case 4:
        printf("��������\n");
        break;
    case 5:
        printf("������������\n");
        break;
    }
    if (choice != -1) {
        printf("������Ϊ��%d�� �� %d��\n", scale, n);
        printf("�����ܺ�ʱ��%d ms\n", total);
        Stop();
    }
    return 0;
}
