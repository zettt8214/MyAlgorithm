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
 *  @brief ���ȶ���
 */
template<typename T>
class PriorityQueue{
private:
	std::vector<T> priority_queue_;	
	int queue_size_;								/// < ʵ�����ȶ��У��ѽṹ�Ĵ�С
	using cmp_ptr = bool (*)(const T&, const T&);	/// <����ָ�룬ָ�������������ȽϺ���
	cmp_ptr cmp_;

	void BuildHeap();								/// < ������
	void HeapIfy(int root);							/// < ������
	void swap(T& data1, T& data2);

public:
	PriorityQueue(std::vector<T> priority_queue, cmp_ptr cmp);
	
	///  @brief �鿴����Ԫ��
	const T& ViewTop() const {  
		if (!priority_queue_.empty()) return priority_queue_[0];
	};
	T ExtractTop();

	///  @todo �޸Ķ���Ԫ�����ȼ�
	bool ChangeKey();

	///  @todo ����Ԫ�ص�������
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
* @brief	���ݱȽϺ������ݹ������
* @param  heap_size	�Ѵ�С
* @param  root		�����ڵ������
*
*/
template<typename T>
void PriorityQueue<T>::HeapIfy(int root) {
	int left_child = root * 2 + 1;  /// < �ڵ�������0��ʼ����������Ϊindex * 2 +1;
	int right_child = root * 2 + 2;
	int temp = root;	/// < ѡ��ڵ������Һ��ӵ�������Сֵ

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
* @brief ��ȡ����Ԫ��
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
* @brief ����Ԫ���Ƿ��ڶ�����
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


