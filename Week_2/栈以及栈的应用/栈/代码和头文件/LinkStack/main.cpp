#include "../head/LinkStack.h" 
#include <iostream>

int Menu();
void Stop(void); /*暂停*/
void Fresh_Buffer(void); /*刷新缓冲区*/

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
        case 1: /*初始化链栈*/
            if (state) {
                printf("链栈已存在，请先销毁栈。\n");
            }
            else {
                s = (LinkStack*)malloc(sizeof(LinkStack));
                if (initLStack(s)) {
                    printf("链栈初始化成功！\n");
                    state = SUCCESS;
                }
                else
                    printf("链栈初始化失败！\n");
            }
            Stop();
            break;
        case 2: /*入栈*/
            if (state) {
                printf("请输入入栈数据：");
                if (scanf_s("%d", &data) == 0) {
                    printf("\n*** 非法输入，请检查输入 ***\n");
                    Fresh_Buffer();
                }
                else {
                    if (pushLStack(s, data))
                        printf("数据入栈成功。\n");
                    else
                        printf("数据入栈失败。\n");
                }
            }
            else {
                printf("链栈不存在，请先初始化链栈。\n");
            }
            Stop();
            break;
        case 3: /*出栈*/
            if (state) {
                if (isEmptyLStack(s)) {
                    printf("链栈为空，无法操作。\n");
                }
                else {
                    if (popLStack(s, &data))
                        printf("数据%d出栈成功。\n", data);
                    else
                        printf("数据出栈失败。\n");
                }
            }
            else {
                printf("链栈不存在，请先初始化链栈。\n");
            }
            Stop();
            break;
        case 4: /*得到栈顶元素*/
            if (state) {
                if (isEmptyLStack(s)) {
                    printf("链栈为空，无法操作。\n");
                }
                else {
                    if (getTopLStack(s, &data))
                        printf("栈顶元素数据为%d。\n", data);
                    else
                        printf("获取栈顶元素失败。\n");
                }
            }
            else {
                printf("链栈不存在，请先初始化链栈。\n");
            }
            Stop();
            break;
        case 5: /* 判断链栈是否为空*/
            if (state) {
                if (isEmptyLStack(s)) {
                    printf("链栈为空。\n");
                }
                else {
                    printf("链栈不为空。\n");
                }
            }
            else {
                printf("链栈不存在，请先初始化链栈。\n");
            }
            Stop();
            break;
        case 6: /*检测栈长度*/
            if (state) {
                if (LStackLength(s, &length) && length == s->count)
                    printf("检测成功，长度为%d。\n", length);
                else
                    printf("检测失败。\n");
            }
            else {
                printf("链栈不存在，请先初始化链栈。\n");
            }
            Stop();
            break;
        case 7: /*清空栈*/
            if (state) {
                if (clearLStack(s))
                    printf("清空栈成功。\n");
                else
                    printf("清空栈失败。\n");
            }
            else {
                printf("链栈不存在，请先初始化链栈。\n");
            }
            Stop();
            break;
        case 8: /*销毁栈*/
            if (state) {
                if (destroyLStack(s)) {
                    printf("销毁栈成功。\n");
                    state = ERROR;
                }
                else
                    printf("销毁栈失败。\n");
            }
            else {
                printf("链栈不存在，请先初始化链栈。\n");
            }
            Stop();
            break;
		}
	}
	return 0;
}