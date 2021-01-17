/**
* @file			priority_queue.h
* @author		tanghf
* @date			2021-01-03
* @version		V1.0
* @copyright    Copyright (c) 2021
*/

#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include <vector>
#include <iostream>
/**
 *  @brief 优先队列
 */
template<typename T>
class PriorityQueue{
private:
	std::vector<T> priority_queue_;	
	int queue_size_;								/// < 实现优先队列，堆结构的大小
	using cmp_ptr = bool (*)(const T&, const T&);	/// <函数指针，指向队列排序所需比较函数
	cmp_ptr cmp_;

	void BuildHeap();								/// < 创建堆
	void HeapIfy(int root);							/// < 调整堆
	void swap(T& data1, T& data2);

public:
	PriorityQueue(std::vector<T> priority_queue, cmp_ptr cmp);
	
	///  @brief 查看队首元素
	const T& ViewTop() const {  
		if (!priority_queue_.empty()) return priority_queue_[0];
	};
	T ExtractTop();

	///  @todo 修改队列元素优先级
	bool ChangeKey();

	///  @todo 插入元素到队列中
	bool insert(T& element);	
	bool find(const T& element)const;
	void ShowQueue() const;
	bool empty() { return queue_size_ == 0; }

};


template<typename T>
PriorityQueue<T>::PriorityQueue(std::vector<T> priority_queue, cmp_ptr cmp) :
	priority_queue_(priority_queue), queue_size_(priority_queue.size()),cmp_(cmp) {
	BuildHeap();
}


template<typename T>
void PriorityQueue<T>::BuildHeap() {
	for (int i = (queue_size_ - 1) / 2; i >= 0; i--) {
		HeapIfy(i);
	}
}

/**
* @brief	根据比较函数，递归调整堆
* @param  heap_size	堆大小
* @param  root		调整节点的索引
*
*/
template<typename T>
void PriorityQueue<T>::HeapIfy(int root) {
	int left_child = root * 2 + 1;  /// < 节点索引从0开始，所以左孩子为index * 2 +1;
	int right_child = root * 2 + 2;
	int temp = root;	/// < 选择节点与左右孩子的最大或最小值

	if (left_child < queue_size_ && (*cmp_)(priority_queue_[left_child], priority_queue_[temp])) {
		temp = left_child;
	}

	if (right_child < queue_size_ && (*cmp_)(priority_queue_[right_child], priority_queue_[temp])) {
		temp = right_child;
	}

	if (temp != root) {
		swap(priority_queue_[root], priority_queue_[temp]);
		HeapIfy(temp);
	}
	
}

template<typename T>
void PriorityQueue<T>::swap(T& data1, T& data2) {
	T temp;
	temp = data1;
	data1 = data2;
	data2 = temp;
}


template<typename T>
void PriorityQueue<T>::ShowQueue() const {
	for (auto value : priority_queue_) {
		std::cout << value << " ";
	}
}

/**
* @brief 提取队首元素
*/
template<typename T>
T PriorityQueue<T>::ExtractTop() {
	if (queue_size_ == 0) {
		std::cout << "Queue had been empty";
	}
	T top = priority_queue_[0];
	priority_queue_[0] = priority_queue_[priority_queue_.size() - 1];
	priority_queue_.pop_back();
	queue_size_--;
	HeapIfy(0);
	return top;
}

/**
* @brief 查找元素是否在队列中
*/
template<typename T>
bool PriorityQueue<T>::find(const T& element)const {
	for (int i = 0; i < queue_size_; i++) {
		if (element == priority_queue_[i]) {
			return true;
		}
	}
	return false;
}
#endif


