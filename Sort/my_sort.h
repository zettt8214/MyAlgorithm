/**
* @file			my_sort.h
* @author		tanghf
* @date			2021-01-06
* @version		V1.0
* @copyright    Copyright (c) 2021
*
*/

#ifndef MY_SORT_H_
#define MY_SORT_H_
#include<vector>

using pfunc = bool(*)(const int&, const int&);
void swap(std::vector<int>& nums, int i, int j);

inline bool GreaterThan(const int& num1, const int& num2) { return num1 > num2; }
inline bool LesserThan(const int& num1, const int& num2) { return num1 < num2; }

void HeapIfy(std::vector<int>& nums, int root, int heap_size, pfunc cmp);		// 调整堆
void BuildHeap(std::vector<int>& nums, pfunc cmp);								// 创建堆
void HeapSort(std::vector<int>& nums, pfunc cmp = GreaterThan);					// 堆排序


void InsertionSort(std::vector<int>& nums);
void QuickSort(std::vector<int>& nums, int left, int right);
void MergeSort(std::vector<int>& nums, int left, int right, std::vector<int>& temp);
void BubbleSort(std::vector<int>& nums);
void SelectSort(std::vector<int>& nums);
void ShellSort(std::vector<int>& nums);
void BucketSort(std::vector<int>& nums);



/**
* @todo	排序算法模板化
*/


#endif