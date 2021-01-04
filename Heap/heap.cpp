/**
* @file			heap.cpp
* @author		tanghf
* @date			2021-01-03
* @version		V1.0
* @copyright    Copyright (c) 2021
*/
#include <vector>
#include <iostream>
#include "heap.h"



/**
* @brief	根据比较函数，递归调整堆
* @param  nums		数组
* @param  heap_size	堆大小
* @param  index		调整节点索引
* @param  pfunc		排序方式
*
*/
void HeapIfy(std::vector<int> &nums, int index,int heap_size, pfunc cmp) {
	int left_child = index * 2 + 1;
	int right_child = index * 2 + 2;
	int temp = index;
	
	if (left_child < heap_size && (*cmp)(nums[left_child], nums[temp])) {
		temp = left_child;
	}

	if (right_child < heap_size && (*cmp)(nums[right_child], nums[temp])) {
		temp = right_child;
	}

	if (temp != index) {
		swap(nums[index], nums[temp]);
		HeapIfy(nums, temp, heap_size, cmp);
	}
}


void BuildHeap(std::vector<int>& nums, pfunc cmp) {
	for (int i = (nums.size() - 1) / 2; i >= 0; i--) {
		HeapIfy(nums, i, nums.size(),cmp);
	}
}

/**
* @brief  堆排序
* @param  nums	数组
* @param  pfunc	排序方式
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


void swap(int& num1, int& num2) {
	int temp = num1;
	num1 = num2;
	num2 = temp;
}



