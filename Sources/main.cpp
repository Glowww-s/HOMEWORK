#include "../Headers/sort.h"
#include "../Headers/tools.h"
#include <iostream>
#include <Windows.h>


int main()
{
    HideCursor();
    system("mode con cols=60 lines=21");
    int choice;
	while (true)
	{
		choice = Menu_Main();
		switch (choice) {
		case 1: /*大数据量单次测试*/
			Menu_LargeData();
			break;
		case 2: /*小数据量多次测试*/
			Menu_SmallData();
			break;
		case 3: /*两道应用题*/
			Menu_Apply();
			break;
		}
	}
    return 0;
}