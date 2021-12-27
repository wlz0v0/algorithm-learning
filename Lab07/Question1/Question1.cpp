#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

typedef struct Performance {
	int compareCnt = 0;
	int moveCnt = 0;
};

// 交换
void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

// 直接插入排序
Performance insertionSort(int a[], int size)
{
	Performance p;
	int i, key;
	for (int j = 1; j < size; j++)
	{
		key = a[j];
		++p.moveCnt;
		i = j - 1;
		while (i >= 0 && a[i] > key)
		{
			++p.compareCnt;
			a[i + 1] = a[i--];
			++p.moveCnt;
		}
		a[i + 1] = key;
		++p.moveCnt;
	}
	return p;
}

// 折半插入排序
Performance binaryInsertionSort(int a[], int size)
{
 
	Performance p;
	int i, key;
	for (int j = 1; j < size; j++)
	{
		key = a[j];
		++p.moveCnt;
		int left = 0;
		int right = j - 1;
		while (left <= right)
		{
			int mid = left + (right - left) / 2;
			++p.compareCnt;
			if (a[mid] < a[j])
			{
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}
		}
		i = j - 1;
		while (i >= left)
		{
			a[i + 1] = a[i--];
			++p.moveCnt;
		}
		a[i + 1] = key;
		++p.moveCnt;
	}
	return p;
}

// 二路插入排序
Performance doubleWayInsertionSort(int a[], int size)
{
	Performance p;
	vector<int> sup(size);
	sup[0] = a[0];
	++p.moveCnt;
	int head = 0;
	int tail = 0;
	
	for (int j = 1; j < size; ++j) 
	{
		++p.compareCnt;
		if (a[j] < sup[head]) 
		{
			++p.moveCnt;
			head = (head - 1 + size) % size;
			sup[head] = a[j];
		}
		else if (a[j] > sup[tail])
		{
			++p.moveCnt;
			tail = (tail + 1) % size;
			sup[tail] = a[j];
		}
		else 
		{
			int pos = (tail + 1 + size) % size;
			while (sup[((pos - 1) + size) % size] > a[j])
			{
				++p.compareCnt;
				++p.moveCnt;
				sup[pos] = sup[(pos - 1 + size) % size];
				pos = (pos - 1 + size) % size;
			}
			++p.moveCnt;
			sup[pos] = a[j];
			tail = (tail + 1 + size) % size;
		}
		
	}
	for (int j = 0; j < size; j++)
	{
		++p.moveCnt;
		a[j] = sup[(head + j + size) % size];
	}
	return p;
}

Performance shellSort(int a[], int size)
{
	Performance p;
	int i, key;
	int interval = size >> 1;
	do 
	{
		for (int k = 0; k < interval; ++k)
		{
			for (int j = k + interval; j < size; j += interval)
			{
				key = a[j];
				++p.moveCnt;
				i = j - interval;
				while (i >= 0 && a[i] > key)
				{
					++p.compareCnt;
					a[i + interval] = a[i];
					i -= interval;
					++p.moveCnt;
				}
				a[i + interval] = key;
				++p.moveCnt;
			}
		}
		interval >>= 1;
	} while (interval != 0);
	return p;
}


//冒泡排序
Performance bubbleSort(int a[], int size)
{
	Performance p;
	int i, j;
	bool swapFlag;
	for (i = 0; i < size - 1; i++)
	{
		swapFlag = false;
		for (j = size - 1; j > i; j--)
		{
			++p.compareCnt;
			if (a[j] < a[j - 1])
			{
				p.moveCnt += 3;
				swap(a[j], a[j - 1]);
				swapFlag = true;
			}
		}
		if (!swapFlag) break;
	}
	return p;
}

//快速排序
void quickSortBasis(int a[], int start, int end, Performance& p)
{
	if (start < end)
	{
		int key = a[start];
		int i = start;
		int j = end;
		while (i < j)
		{
			while (i < j && a[j] >= key)
			{
				++p.compareCnt;
				j--;
			}
			if (i < j)
			{
				++p.moveCnt;
				a[i] = a[j];
				i++;
			}
			while (i < j && a[i] < key) 
			{
				++p.compareCnt;
				i++;
			}
			if (i < j)
			{
				++p.moveCnt;
				a[j] = a[i];
				j--;
			}
		}
		++p.moveCnt;
		a[i] = key;
		quickSortBasis(a, start, i - 1, p);
		quickSortBasis(a, i + 1, end, p);
	}
}

Performance quickSort(int a[], int size) {
	Performance p;
	quickSortBasis(a, 0, size - 1, p);
	return p;
}

// 选择排序
Performance selectionSort(int a[], int size)
{
	Performance p;
	for (int i = 0; i < size; i++)
	{
		int min = i;
		for (int j = i + 1; j < size; j++)
		{
			++p.compareCnt;
			if (a[j] < a[min])
			{
				min = j;
			}
		}
		if (min != i)
		{
			p.moveCnt += 3;
			swap(a[min], a[i]);
		}
	}
	return p;
}

void makeHeap(int a[], int start, int end, Performance& p)
{
	int dad = start;
	int son = 2 * dad + 1;
	while (son <= end)
	{
		++p.compareCnt;
		if (son + 1 <= end && a[son] < a[son + 1])
		{
			++son;
		}
		++p.compareCnt;
		if (a[dad] > a[son])
		{
			return;
		}
		swap(a[dad], a[son]);
		p.moveCnt += 3;
		dad = son;
		son = 2 * son + 1;
	}
}

// 堆排序
Performance heapSort(int a[], int size)
{
	Performance p;
	for (int i = size / 2 - 1; i >= 0; --i)
	{
		makeHeap(a, i, size - 1, p);
	}
	for (int i = size - 1; i > 0; --i)
	{
		swap(a[0], a[i]);
		p.moveCnt += 3;
		makeHeap(a, 0, i - 1, p);
	}
	return p;
}

//归并排序
void mergeSortBasis(int arr[], int reg[], int start, int end, Performance& p)
{
	if (start >= end)
		return;
	int mid = (end - start) / 2 + start;
	int start1 = start;
	int start2 = mid + 1;
	int end1 = mid;
	int end2 = end;
	mergeSortBasis(arr, reg, start1, end1, p);
	mergeSortBasis(arr, reg, start2, end2, p);
	int k = start;
	while (start1 <= end1 && start2 <= end2)
	{
		reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
		++p.compareCnt;
		++p.moveCnt;
	}
	while (start1 <= end1)
	{
		reg[k++] = arr[start1++];
		++p.moveCnt;
	}
	while (start2 <= end2)
	{
		reg[k++] = arr[start2++];
		++p.moveCnt;
	}
	for (k = start; k <= end; k++)
	{
		++p.moveCnt;
		arr[k] = reg[k];
	}
}

Performance mergeSort(int a[], int size)
{
	Performance p;
	int* reg = new int[size];
	mergeSortBasis(a, reg, 0, size - 1, p);
	delete[] reg;
	return p;
}

int main()
{
	constexpr int SIZE = 100;
	for (int j = 0; j < 5; ++j)
	{
		int arr[9][SIZE];
		for (int k = 0; k < SIZE; ++k)
		{
			arr[0][k] = rand() % 200;
		}
		for (int i = 1; i < 9; ++i) 
		{
			for (int j = 0; j < SIZE; ++j)
			{
				arr[i][j] = arr[0][j];
			}
		}
		Performance is = insertionSort(arr[0], SIZE);
		Performance bis = binaryInsertionSort(arr[1], SIZE);
		Performance dwis = doubleWayInsertionSort(arr[2], SIZE);
		Performance ss = shellSort(arr[3], SIZE);
		Performance bs = bubbleSort(arr[4], SIZE);
		Performance qs = quickSort(arr[5], SIZE);
		Performance sss = selectionSort(arr[6], SIZE);
		Performance hs = heapSort(arr[7], SIZE);
		Performance ms = mergeSort(arr[8], SIZE);
		cout << "第" << (j + 1) << "次\n";
		cout << "排序类型\t" << "比较次数\t" << "移动次数\n";
		cout << "直接插入排序\t" << is.compareCnt << "\t\t" << is.moveCnt << "\n";
		cout << "折半插入排序\t" << bis.compareCnt << "\t\t" << bis.moveCnt << "\n";
		cout << "二路插入排序\t" << dwis.compareCnt << "\t\t" << dwis.moveCnt << "\n";
		cout << "希尔排序\t" << ss.compareCnt << "\t\t" << ss.moveCnt << "\n";
		cout << "冒泡排序\t" << bs.compareCnt << "\t\t" << bs.moveCnt << "\n";
		cout << "快速排序\t" << qs.compareCnt << "\t\t" << qs.moveCnt << "\n";
		cout << "简单选择排序\t" << sss.compareCnt << "\t\t" << sss.moveCnt << "\n";
		cout << "堆排序\t\t" << hs.compareCnt << "\t\t" << hs.moveCnt << "\n";
		cout << "归并排序\t" << ms.compareCnt << "\t\t" << ms.moveCnt << "\n";
	}
	return 0;
}