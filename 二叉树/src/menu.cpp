#include <iostream>
#include <time.h>
#include "../inc/binary_sort_tree.h"
#include "../inc/tools.h"


int Menu_Main() /*���˵�*/
{
    char menu[E][W] = {
        {"                                                            "},
        {"                   <<<<< ���������� >>>>>                   "},
        {"                                                            "},
        {"                                                            "},
        {"        --------            ����            --------        "},
        {"                                                            "},
        {"                                                            "},
        {"        --------            ����            --------        "},
        {"                                                            "},
        {"                                                            "},
        {"        --------            ɾ��            --------        "},
        {"                                                            "},
        {"                                                            "},
        {"        --------          �������          --------        "},
        {"                                                            "},
        {"                                                            "},
        {"        --------          ��α���          --------        "},
        {"                                                            "},
        {"                                                            "},
        {"    *** tips:������ʹ�����¼��ͻس���[Enter]����ѡ�� ***    "},
        {"                                                            "},
    };
    return MenuChoose(menu, 5);
}

int Menu_ThreeOrder(BinarySortTreePtr tree) /*��������Ķ����˵�*/
{
    char menu[E][W] = {
        {"                                                            "},
        {"               <<<<< ���ִ���ı�����ʽ >>>>>               "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"         --------         ǰ�����         --------         "},
        {"                                                            "},
        {"                                                            "},
        {"         --------         �������         --------         "},
        {"                                                            "},
        {"                                                            "},
        {"         --------         �������         --------         "},
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

int Menu_ior() /*�ݹ�ѡ�������˵�*/
{
    char menu[E][W] = {
        {"                                                            "},
        {"                    <<<<< �ݹ�ѡ�� >>>>>                    "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"         --------           �ݹ�           --------         "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"        --------           �ǵݹ�           --------        "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                                                            "},
        {"                *** ��[Esc]���������˵� ***                 "},
        {"                                                            "},
    };
    return MenuChoose(menu, 2);
}
