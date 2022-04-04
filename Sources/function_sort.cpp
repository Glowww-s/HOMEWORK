#include "../Headers/sort.h"
#include "../Headers/tools.h"
#include <iostream>


void insertSort(int* a, int n)
{
	int i, j;
	int t;
	for (i = 0; i < n; i++) {
		t = *(a + i);
		for (j = i; j > 0 && t < *(a + j - 1); j--) {
			*(a + j) = *(a + j - 1);
		}
		*(a + j) = t;
	}
}

void MergeArray(int* a, int begin, int mid, int end, int* temp)
{
	int i = begin;
	int n = begin, m = mid + 1;
	while (n < mid + 1 && m < end + 1) {
		if (*(a + n) < *(a + m)) {
			temp[i++] = a[n++];
		}
		else {
			temp[i++] = a[m++];
		}
	}
	while (n < mid + 1) {
		temp[i++] = a[n++];
	}
	while (m < end + 1) {
		temp[i++] = a[m++];
	}
}

void MergeSort(int* a, int begin, int end, int* temp)
{
	int mid;
	int* t = (int*)calloc(end + 1, sizeof(int));
	if (begin == end) {
		temp[begin] = a[begin];
	}
	else {
		mid = (begin + end) / 2;
		MergeSort(a, begin, mid, t);
		MergeSort(a, mid + 1, end, t);
		MergeArray(t, begin, mid, end, temp);
	}
	free(t);
}

void QuickSort_Recursion(int* a, int begin, int end) {
	int i, j;
	int mid;
	int t;
	int n = end - begin + 1;
	if (n <= 20) { /*小于20直接插入排序*/
		insertSort(a + begin, n);
	}
	else {
		mid = Partition(a, begin, end); /*获得枢轴的值*/
		i = begin;
		j = end - 2;
		while (i < j) { /*大小值互换直到ij相遇*/
			if (*(a + i) <= mid) {
				i++;
			}
			if (*(a + j) >= mid) {
				j--;
			}
			if (*(a + i) > mid && *(a + j) < mid) {
				t = *(a + i);
				*(a + i) = *(a + j);
				*(a + j) = t;
				i++;
				j--;
			}
		}
		*(a + end - 1) = *(a + i); /*i与枢轴互换*/
		*(a + i) = mid; /*i所在位置即枢轴*/
		QuickSort_Recursion(a, begin, i - 1);
		QuickSort_Recursion(a, i + 1, end);
	}
}

int Partition(int* a, int begin, int end) { /*三分取中?*/
	int mid = (begin + end) / 2;
	int t;
	if (*(a + begin) > *(a + mid)) { /*三数排序*/
		t = *(a + begin);
		*(a + begin) = *(a + mid);
		*(a + mid) = t;
	}
	if (*(a + begin) > *(a + end)) {
		t = *(a + begin);
		*(a + begin) = *(a + end);
		*(a + end) = t;
	}
	if (*(a + mid) > *(a + end)) {
		t = *(a + mid);
		*(a + mid) = *(a + end);
		*(a + end) = t;
	}
	t = *(a + mid); /*将枢轴置尾*/
	*(a + mid) = *(a + end - 1);
	*(a + end - 1) = t;
	return t;
}

void CountSort(int* a, int size, int max)
{
	int i, j, k;
	int n;
	int* count = (int*)calloc(max + 1, sizeof(int));
	if (count == NULL) {
		fprintf(stderr, "*** 申请内存空间失败 ***");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < size; i++) { /*收集计数过程*/
		n = *(a + i);
		*(count + n) += 1;
	}
	n = 0;
	for (i = 0; i < max + 1; i++) {
		n += *(count + i); /*计数累加统计过程*/
		*(count + i) = n;
	}
	n = 0;
	k = 0;
	for (i = 0; i < max + 1; i++) { /*获得结果数组过程*/
		for (j = 0; j < *(count + i) - n; j++) {
			a[k++] = i;
		}
		n = *(count + i);
	}
	free(count); /*释放内存空间*/
}

void RadixCountSort(int* a, int size)
{
	int i, j; /*控制二维数组*/
	int n; /*控制数据*/
	int m, radix = 1; /*控制位数*/
	int cnt[10] = { 0 };
	int* temp[10];
	for (i = 0; i < 10; i++) { /*创建一个指针数组用于存放数据*/
		temp[i] = (int*)calloc(size, sizeof(int));
		if (temp[i] == NULL) {
			fprintf(stderr, "*** 申请内存空间失败 ***");
			exit(EXIT_FAILURE);
		}
	}
	for (m = 0; m < 5; m++) {
		memset(cnt, 0, sizeof(cnt));
		for (n = 0; n < size; n++) { /*按照基数放入二维数组*/
			i = (*(a + n) % (radix * 10)) / radix;
			j = cnt[i];
			temp[i][j] = *(a + n);
			cnt[i] += 1;
		}
		n = 0; 
		for (i = 0; i < 10; i++) { /*按由小到大顺序取出来放回原数组*/
			for (j = 0; j < cnt[i]; j++) {
				*(a + n) = temp[i][j];
				n++; /*给原数组计数用*/
			}
		}
		radix *= 10;
	}
	for (i = 0; i < 10; i++) { /*释放内存空间*/
		free(temp[i]);
	}
}

void ColorSort(int* a, int size)
{
	int i;
	int* p0, * p1, * p2;
	p0 = p1 = a;
	p2 = a + size - 1;
	printf("原数组："); /*输出原数组*/
	for (i = 0; i < size; i++) {
		printf(" %d ", *(a + i));
	}
	printf("\n");

	while (p1 != p2) { /*排序操作*/
		p1 += 1;
		if (*p1 == 2) {
			*p1 = *p2;
			*p2 = 2;
			p2 -= 1;
		}
		if (*p1 == 0) {
			*p1 = *p0;
			*p0 = 0;
			p0 += 1;
		}
	}

	printf("排序后数组："); /*输出原数组*/
	for (i = 0; i < size; i++) {
		printf(" %d ", *(a + i));
	}
	printf("\n");
	Stop();
}

void FindSpecificSize(int* a, int size)
{
	int i, j;
	int K = 3; /*找到第三小的数*/
	int begin = 0, mid, end = size - 1;
	int t;
	printf("原数组："); /*输出原数组*/
	for (i = 0; i < size; i++) {
		printf(" %d ", *(a + i));
	}
	printf("\n");

	do {
		mid = Partition(a, begin, end); /*获得枢轴的值*/
		i = begin;
		j = end - 2;
		while (i < j) { /*大小值互换直到ij相遇*/
			if (*(a + i) <= mid) {
				i++;
			}
			if (*(a + j) >= mid) {
				j--;
			}
			if (*(a + i) > mid && *(a + j) < mid) {
				t = *(a + i);
				*(a + i) = *(a + j);
				*(a + j) = t;
				i++;
				j--;
			}
		}
		*(a + size - 2) = *(a + i); /*i与枢轴互换*/
		*(a + i) = mid; /*i所在位置即枢轴*/
		if (K < i + 1) { /*对数据分段*/
			end = i - 1;
		}
		else if (K > i+1) {
			begin = i + 1;
		}
	} while (K != i + 1);

	printf("数组中第%d小的数据为：%d\n", K, *(a + i));
	Stop();
}