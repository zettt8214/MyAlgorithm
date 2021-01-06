/**
* @file			my_sort.cpp
* @author		tanghf
* @date			2021-01-06
* @version		V1.0
* @copyright    Copyright (c) 2021
*
*/

#include <iostream>
#include <vector>
#include <map>
#include "my_sort.h"
using namespace std;

void swap(vector<int>& nums, int i, int j) {
	int temp;
	temp = nums[i];
	nums[i] = nums[j];
	nums[j] = temp;
}

void InsertionSort(vector<int>& nums) {
	//O(n^2)
	//С��ģ���ݻ������ݻ�������ʱʮ�ָ�Ч
	for (int i = 1; i < nums.size(); i++) {
		for (int j = i - 1; j >= 0 && nums[j] > nums[j + 1]; j--) {
			swap(nums, j, j+1);
		}
	}
}

void ShellSort(vector<int>& nums) {
	//�Ľ��Ĳ�������ʹ�����������������ٽ��в�������
	for (int d = nums.size() / 2; d > 0; d = d / 2) { //d = 1ʱ���в�������
		for (int i = d; i < nums.size(); i++) {
			for (int j = i - d; j >= 0 && nums[j] > nums[j + d]; j = j - d) {
				swap(nums, j, j + d);
			}
		}
	}
}

void QuickSort(vector<int>& nums, int left, int right) {
	//O(nlogn)
	//[left,right�� 
	if (left + 1 >= right) {  //[left,left+1) indicates one element
		return;
	}
	int mid = left + (right - left) / 2;
	swap(nums, left, mid);
	int j = left;
	for (int i = left + 1; i < right; i++) {
		if (nums[i] < nums[left]) {
			swap(nums, ++j, i);
		}
	}
	
	swap(nums, left, j);
	
	QuickSort(nums, left, j);
	QuickSort(nums, j + 1, right);
}

void MergeSort(vector<int>& nums, int left, int right, vector<int>& temp) {
	//O(nlogn)
	//[left,right�� ��������
	if (left + 1 >= right) {
		return;
	}
	int mid = left + (right - left) / 2;
	MergeSort(nums, left, mid,temp);
	MergeSort(nums, mid, right,temp);

	int index1 = left;
	int index2 = mid;
	int i = left;
	while (index1 < mid || index2 < right) {
		if (index2 == right || (index1 < mid && nums[index1] < nums[index2])) {
			temp[i++] = nums[index1++];
		}
		else {
			temp[i++] = nums[index2++];
		}
	}

	for (i = left; i < right; i++) {
		nums[i] = temp[i];
	}

}

void BubbleSort(vector<int>& nums) {
	//O(n^2)
	int len = nums.size();
	while (len > 1) {
		for (int i = 0; i < len - 1; i++) {
			if (nums[i] > nums[i + 1]) {
				swap(nums, i, i + 1);
			}
		}
		len--;
	}
}

void SelectSort(vector<int>& nums) {
	int len = nums.size();
	int minIndex;
	for (int i = 0; i < len - 1; i++) {
		minIndex = i;
		for (int j = i + 1; j < len; j++) {
			if (nums[j] < nums[minIndex]) {
				minIndex = j;
			}
		}
		swap(nums, i, minIndex);
	}
}

void BucketSort(vector<int>& nums) { //��������
	map<int, int> counts;
	for (auto num : nums) {
		counts[num]++;
	}
	int index = 0;
	for (auto p : counts) {
		for (int i = 0; i < p.second; i++) {
			nums[index++] = p.first;
		}
	}
}


/**
* @brief	���ݱȽϺ������ݹ������
* @param  nums		����
* @param  heap_size	�Ѵ�С
* @param  root		�����ڵ�����
* @param  pfunc		����ʽ
*
*/
void HeapIfy(std::vector<int>& nums, int root, int heap_size, pfunc cmp) {
	int left_child = root * 2 + 1;
	int right_child = root * 2 + 2;
	int temp = root;

	if (left_child < heap_size && (*cmp)(nums[left_child], nums[temp])) {
		temp = left_child;
	}

	if (right_child < heap_size && (*cmp)(nums[right_child], nums[temp])) {
		temp = right_child;
	}

	if (temp != root) {
		swap(nums,root, temp);
		HeapIfy(nums, temp, heap_size, cmp);
	}
}


void BuildHeap(std::vector<int>& nums, pfunc cmp) {
	for (int i = (nums.size() - 1) / 2; i >= 0; i--) {
		HeapIfy(nums, i, nums.size(), cmp);
	}
}

/**
* @brief  ������
* @param  nums	����
* @param  pfunc	����ʽ
*
*/
void HeapSort(std::vector<int>& nums, pfunc cmp) {
	BuildHeap(nums, cmp);
	int heap_size = nums.size();
	for (int i = nums.size() - 1; i > 0; i--) {
		swap(nums[0], nums[i]);
		heap_size--;
		HeapIfy(nums, 0, heap_size, cmp);
	}
}


