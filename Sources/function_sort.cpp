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
	if (n <= 20) { /*С��20ֱ�Ӳ�������*/
		insertSort(a + begin, n);
	}
	else {
		mid = Partition(a, begin, end); /*��������ֵ*/
		i = begin;
		j = end - 2;
		while (i < j) { /*��Сֵ����ֱ��ij����*/
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
		*(a + end - 1) = *(a + i); /*i�����ụ��*/
		*(a + i) = mid; /*i����λ�ü�����*/
		QuickSort_Recursion(a, begin, i - 1);
		QuickSort_Recursion(a, i + 1, end);
	}
}

int Partition(int* a, int begin, int end) { /*����ȡ��?*/
	int mid = (begin + end) / 2;
	int t;
	if (*(a + begin) > *(a + mid)) { /*��������*/
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
	t = *(a + mid); /*��������β*/
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
		fprintf(stderr, "*** �����ڴ�ռ�ʧ�� ***");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < size; i++) { /*�ռ���������*/
		n = *(a + i);
		*(count + n) += 1;
	}
	n = 0;
	for (i = 0; i < max + 1; i++) {
		n += *(count + i); /*�����ۼ�ͳ�ƹ���*/
		*(count + i) = n;
	}
	n = 0;
	k = 0;
	for (i = 0; i < max + 1; i++) { /*��ý���������*/
		for (j = 0; j < *(count + i) - n; j++) {
			a[k++] = i;
		}
		n = *(count + i);
	}
	free(count); /*�ͷ��ڴ�ռ�*/
}

void RadixCountSort(int* a, int size)
{
	int i, j; /*���ƶ�ά����*/
	int n; /*��������*/
	int m, radix = 1; /*����λ��*/
	int cnt[10] = { 0 };
	int* temp[10];
	for (i = 0; i < 10; i++) { /*����һ��ָ���������ڴ������*/
		temp[i] = (int*)calloc(size, sizeof(int));
		if (temp[i] == NULL) {
			fprintf(stderr, "*** �����ڴ�ռ�ʧ�� ***");
			exit(EXIT_FAILURE);
		}
	}
	for (m = 0; m < 5; m++) {
		memset(cnt, 0, sizeof(cnt));
		for (n = 0; n < size; n++) { /*���ջ��������ά����*/
			i = (*(a + n) % (radix * 10)) / radix;
			j = cnt[i];
			temp[i][j] = *(a + n);
			cnt[i] += 1;
		}
		n = 0; 
		for (i = 0; i < 10; i++) { /*����С����˳��ȡ�����Ż�ԭ����*/
			for (j = 0; j < cnt[i]; j++) {
				*(a + n) = temp[i][j];
				n++; /*��ԭ���������*/
			}
		}
		radix *= 10;
	}
	for (i = 0; i < 10; i++) { /*�ͷ��ڴ�ռ�*/
		free(temp[i]);
	}
}

void ColorSort(int* a, int size)
{
	int i;
	int* p0, * p1, * p2;
	p0 = p1 = a;
	p2 = a + size - 1;
	printf("ԭ���飺"); /*���ԭ����*/
	for (i = 0; i < size; i++) {
		printf(" %d ", *(a + i));
	}
	printf("\n");

	while (p1 != p2) { /*�������*/
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

	printf("��������飺"); /*���ԭ����*/
	for (i = 0; i < size; i++) {
		printf(" %d ", *(a + i));
	}
	printf("\n");
	Stop();
}

void FindSpecificSize(int* a, int size)
{
	int i, j;
	int K = 3; /*�ҵ�����С����*/
	int begin = 0, mid, end = size - 1;
	int t;
	printf("ԭ���飺"); /*���ԭ����*/
	for (i = 0; i < size; i++) {
		printf(" %d ", *(a + i));
	}
	printf("\n");

	do {
		mid = Partition(a, begin, end); /*��������ֵ*/
		i = begin;
		j = end - 2;
		while (i < j) { /*��Сֵ����ֱ��ij����*/
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
		*(a + size - 2) = *(a + i); /*i�����ụ��*/
		*(a + i) = mid; /*i����λ�ü�����*/
		if (K < i + 1) { /*�����ݷֶ�*/
			end = i - 1;
		}
		else if (K > i+1) {
			begin = i + 1;
		}
	} while (K != i + 1);

	printf("�����е�%dС������Ϊ��%d\n", K, *(a + i));
	Stop();
}