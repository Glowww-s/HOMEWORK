#include <iostream>
#include <time.h>
#include "../inc/binary_sort_tree.h"
#include "../inc/tools.h"


int Menu_Main() /*主菜单*/
{
    char menu[E][W] = {
        {"                                                            "},
        {"                   <<<<< 二叉排序树 >>>>>                   "},
        {"                                                            "},
        {"                                                            "},
        {"        --------            查找            --------        "},
        {"                                                            "},
        {"                                                            "},
        {"        --------            插入            --------        "},
        {"                                                            "},
        {"                                                            "},
        {"        --------            删除            --------        "},
        {"                                                            "},
        {"                                                            "},
        {"        --------          三序遍历          --------        "},
        {"                                                            "},
        {"                                                            "},
        {"        --------          层次遍历          --------        "},
        {"                                                            "},
        {"                                                            "},
        {"    *** tips:本程序使用上下键和回车键[Enter]进行选择 ***    "},
        {"                                                            "},
    };
    return MenuChoose(menu, 5);
}

int Menu_ThreeOrder(BinarySortTreePtr tree) /*三序遍历的二级菜单*/
{
    char menu[E][W] = {
        {"                                                            "},
        {"               <<<<< 三种次序的遍历方式 >>>>>               "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"         --------         前序遍历         --------         "},
        {"                                                            "},
        {"                                                            "},
        {"         --------         中序遍历         --------         "},
        {"                                                            "},
        {"                                                            "},
        {"         --------         后序遍历         --------         "},
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
        switch (Menu_ior()) {
        case 1:
            BST_preorderR(tree, Visit);
            Stop();
            break;
        case 2:
            BST_preorderI(tree, Visit);
            Stop();
            break;
        }
        break;
    case 2:
        switch (Menu_ior()) {
        case 1:
            BST_inorderR(tree, Visit);
            Stop();
            break;
        case 2:
            BST_inorderI(tree, Visit);
            Stop();
            break;
        }
        break;
    case 3:
        switch (Menu_ior()) {
        case 1:
            BST_postorderR(tree, Visit);
            Stop();
            break;
        case 2:
            BST_postorderI(tree, Visit);
            Stop();
            break;
        }
        break;
    }
    return 0;
}

int Menu_ior() /*递归选择三级菜单*/
{
    char menu[E][W] = {
        {"                                                            "},
        {"                    <<<<< 递归选择 >>>>>                    "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"         --------           递归           --------         "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"        --------           非递归           --------        "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                *** 按[Esc]键返回主菜单 ***                 "},
        {"                                                            "},
    };
    return MenuChoose(menu, 2);
}
