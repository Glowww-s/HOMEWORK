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
    if (BST_init(tree) == 0) { /*进入程序前先初始化一棵树*/
        fprintf(stderr, "*** 二叉排序树的初始化失败 ***\n");
        exit(EXIT_FAILURE);
    }
    while (true) {
        switch (Menu_Main()) {
        case 1: /*查找*/
            ShowCursor();
            printf("请输入需要查找的数据：");
            if (scanf_s("%d", &n) == 0) {
                printf("*** 非法输入，请检查输入 ***\n");
            }
            else {
                if(BST_search(tree, n))
                    printf("*** 该数据存在树中 ***\n");
                else
                    printf("*** 该数据不存在树中 ***\n");
            }
            Fresh_Buffer();
            HideCursor();
            Stop();
            break;
        case 2: /*插入*/
            ShowCursor();
            printf("请输入需要插入的数据：");
            if (scanf_s("%d", &n) == 0) {
                printf("*** 非法输入，请检查输入 ***\n");
            }
            else {
                if (BST_insert(tree, n))
                    printf("*** 插入成功 ***\n");
                else
                    printf("*** 插入失败 ***\n");
            }
            Fresh_Buffer();
            HideCursor();
            Stop();
            break;
        case 3: /*删除*/
            ShowCursor();
            printf("请输入需要删除的数据：");
            if (scanf_s("%d", &n) == 0) {
                printf("*** 非法输入，请检查输入 ***\n");
            }
            else {
                if (BST_delete(tree, n))
                    printf("*** 删除成功 ***\n");
                else
                    printf("*** 删除失败 ***\n");
            }
            Fresh_Buffer();
            HideCursor();
            Stop();
            break;
        case 4: /*三序遍历*/
            Menu_ThreeOrder(tree);
            break;
        case 5: /*层次遍历*/
            BST_levelOrder(tree, Visit);
            Stop();
            break;
        }
        Sleep(150);
    }
    return 0;
}
