#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#define E 21
#define W 61

void HideCursor(); //隐藏光标
void ShowCursor(); //显示光标
char MenuChoose(const char(*menu)[W], int m); //选择功能,m->项数
void HLshow(const char(*p)[W], int n); //高亮显示
int Menu_Main(); /*主菜单*/
int Menu_LargeData(); /*大数据量单次测试二级菜单*/
int Menu_SmallData(); /*小数据量多次测试二级菜单*/
int Menu_Apply(); /*应用题二级菜单*/
int Menu_Sort(int scale, int n); /*三级菜单用于选择排序算法*/

void DataSave(int scale); /*生成并保存数据*/
int* DataRead(void); /*读取数据*/

void Stop(void); /*暂停*/
void Fresh_Buffer(void); /*刷新缓冲区*/

#endif // QUEUE_H_INCLUDED
