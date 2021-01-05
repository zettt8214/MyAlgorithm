/**
* @file			heap.h
* @author		tanghf
* @date			2021-01-03
* @version		V1.0
* @copyright    Copyright (c) 2021
*/
#ifndef HEAP_H_
#define HEAP_H_

/// ����ָ�룬ָ��һ���ȽϺ���
using pfunc = bool(*)(const int&, const int&);			

void swap(int& num1, int& num2);
inline bool GreaterThan(const int& num1, const int& num2) { return num1 > num2; }
inline bool LesserThan(const int& num1, const int& num2) { return num1 < num2; }

void HeapSort(std::vector<int>& nums, pfunc cmp = GreaterThan);					// ������

void HeapIfy(std::vector<int>& nums, int root, int heap_size, pfunc cmp);		// ������
void BuildHeap(std::vector<int>& nums, pfunc cmp);								// ������
#endif // !HEAP_H_


