#pragma once
#include<vector>


void insertionSort(std::vector<int>& nums);
void quickSort(std::vector<int>& nums, int left, int right);
void mergeSort(std::vector<int>& nums, int left, int right, std::vector<int>& temp);
void bubbleSort(std::vector<int>& nums);
void selectSort(std::vector<int>& nums);
void shellSort(std::vector<int>& nums);
void swap(std::vector<int>& nums, int i, int j);
void bucketSort(std::vector<int>& nums);

