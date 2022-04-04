#include "../Headers/sort.h"
#include "../Headers/tools.h"
#include <iostream>
#include <time.h>

int Menu_Main() /*主菜单*/
{
    char menu[E][W] = {
        {"                                                            "},
        {"                     <<<<< 主菜单 >>>>>                     "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"        --------      大数据量单次测试      --------        "},
        {"                                                            "},
        {"                                                            "},
        {"        --------      小数据量多次测试      --------        "},
        {"                                                            "},
        {"                                                            "},
        {"        --------        两道应用题          --------        "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"    *** tips:本程序使用上下键和回车键[Enter]进行选择 ***    "},
        {"                                                            "},
        {"                                                            "},
    };
    return MenuChoose(menu, 3);
}

int Menu_LargeData() /*大数据量单次测试二级菜单*/
{
    int scale;
    char menu[E][W] = {
        {"                                                            "},
        {"                <<<<< 测试数据的数量级 >>>>>                "},
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
        {"                *** 按[Esc]键返回主菜单 ***                 "},
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

int Menu_SmallData() /*小数据量多次测试二级菜单*/
{
    int n;
    char menu[E][W] = {
        {"                                                            "},
        {"                <<<<< 测试数据的数量级 >>>>>                "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"         --------       100个*10k次        --------         "},
        {"                                                            "},
        {"                                                            "},
        {"         --------       100个*100k次       --------         "},
        {"                                                            "},
        {"                                                            "},
        {"         --------       100个*1000k次      --------         "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                *** 按[Esc]键返回主菜单 ***                 "},
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

int Menu_Apply() /*应用题二级菜单*/
{
    int data1[7] = { 1,2,1,0,2,0,0 };
    int data2[7] = { 5,2,8,4,3,7,6 };
    char menu[E][W] = {
        {"                                                            "},
        {"                     <<<<< 应用题 >>>>>                     "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"         --------         颜色排序         --------         "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"        -------- 无序序列中找到第K大/小的数 --------        "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                *** 按[Esc]键返回主菜单 ***                 "},
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

int Menu_Sort(int scale, int n) /*三级菜单用于选择排序算法*/
{
    int total = 0; /*总时间*/
    clock_t start, diff;
    int choice;
    int i, j;
    int max;
    int* data, * temp;
    char menu[E][W] = {
        {"                                                            "},
        {"                  <<<<< 排序算法选择 >>>>>                  "},
        {"                                                            "},
        {"                                                            "},
        {"         --------       插入排序             --------       "},
        {"                                                            "},
        {"                                                            "},
        {"         --------       归并排序             --------       "},
        {"                                                            "},
        {"                                                            "},
        {"         --------       快速排序(递归版)     --------       "},
        {"                                                            "},
        {"                                                            "},
        {"         --------       计数排序             --------       "},
        {"                                                            "},
        {"                                                            "},
        {"         --------       基数计数排序         --------       "},
        {"                                                            "},
        {"                                                            "},
        {"                *** 按[Esc]键返回主菜单 ***                 "},
        {"                                                            "},
    };
    choice = MenuChoose(menu, 5);
    for (i = 0; i < n; i++) {
        DataSave(scale);
        data = DataRead(); /*获取数量为scale的数据*/
        temp = (int*)calloc(scale, sizeof(int));
        start = clock();
        switch (choice) {
        case 1: /*插排*/
            insertSort(data, scale);
            break;
        case 2: /*归并*/
            MergeSort(data, 0, scale - 1, temp);
            break;
        case 3: /*快排*/
            QuickSort_Recursion(data, 0, scale - 1);
            break;
        case 4: /*计数排序*/
            max = *data;
            for (j = 0; j < scale; j++) {
                if (max < *(data + j)) {
                    max = *(data + j);
                }
            }
            CountSort(data, scale, max);
            break;
        case 5: /*基数计数*/
            RadixCountSort(data, scale);
            break;
        }
        diff = clock() - start; 
        total += diff; /*累加总耗时*/
        free(data);
        free(temp);
    }
    /*输出排序信息*/
    switch (choice) {
    case 1:
        printf("插入排序：\n");
        break;
    case 2:
        printf("归并排序：\n");
        break;
    case 3:
        printf("快速排序：\n");
        break;
    case 4:
        printf("计数排序：\n");
        break;
    case 5:
        printf("基数计数排序：\n");
        break;
    }
    if (choice != -1) {
        printf("数据量为：%d个 × %d次\n", scale, n);
        printf("排序总耗时：%d ms\n", total);
        Stop();
    }
    return 0;
}
