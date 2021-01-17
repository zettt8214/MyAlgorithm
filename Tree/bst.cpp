#include <iostream>
#include "bst.h"


/*
* @brief ������ת��Ϊ����������
* 
*/
BinSearchTree::BinSearchTree(std::vector<Tp> tree) {
	for (const auto& key : tree) {
		TreeInsert(key);
	}
}

BinSearchTree::~BinSearchTree() {
	while (root_) {
		TreeDelete(root_->data);
	}
}

/**
* @brief ��˳�����������
*
*/
void BinSearchTree::TreeVist() {
	TreeVistHelper(root_);
	std::cout << std::endl;
}

/**
* @brief ����������Ŀ��ֵ
* @return �����ڷ���ֵΪĿ��ֵ�Ľڵ�ģ�����Χ��ָ��
*/
TNode* BinSearchTree::TreeSearch(Tp key) {
	TNode* p = root_;
	while (p) {
		if (p->data == key) {
			return p;
		}
		else if (key < p->data) {
			p = p->left;
		}
		else {
			p = p->right;
		}
	}
	return nullptr;
}



/**
* @brief ���������в���Ԫ��
* 
*/
void BinSearchTree::TreeInsert(Tp key) {
	TNode* node = new TNode;
	node->data = key;
	node->parent = nullptr;
	node->left = nullptr;
	node->right = nullptr;

	TNode* pre = nullptr;
	TNode* cur = root_;
	while (cur) {
		pre = cur;
		if (key < cur->data) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}
	node->parent = pre;
	if (!pre) {
		root_ = node;
	}
	else if (key < pre->data) {
		pre->left = node;
	}
	else {
		pre->right = node;
	}
}



/**
* @brief ɾ��ָ������
*
*/
void BinSearchTree::TreeDelete(Tp key) {
	TNode* p = TreeSearch(key);
	if (p) {
		if (!p->left) {
			Transpant(p, p->right);
		}
		else if (!p->right) {
			Transpant(p, p->left);
		}
		else {
			TNode* next = TreeMinimumHelper(p->right);  /// �ҵ�p�ڵ�ĺ�̽ڵ�
			if (next->parent != p) {
				Transpant(next, next->right);
				next->right = p->right;
				p->right->parent = next;
			}
			Transpant(p, next);
			next->left = p->left;
			next->left->parent = next;
		}
		delete p;

	}
	else {
		std::cout << key << " is not in the tree!" << std::endl;
	}
}


/**
* @brief Ѱ��Ŀ��ֵ����һ��Ԫ��
*
*/
Tp BinSearchTree::TreeSuccessor(Tp key) {
	TNode*  p = TreeSearch(key);
	if (p) {
		TNode* next = TreeSuccessorHelper(p);
		if (next) {
			return next->data;
		}
		else {
			return kNInfinity;
		}
		
	}
	else {
		return kNInfinity;
	}
}

/**
* @brief Ѱ��Ŀ��ֵ��ǰһ��Ԫ��
*
*/
Tp BinSearchTree::TreePredecessor(Tp key) {
	TNode* p = TreeSearch(key);
	if (p) {
		TNode* next = TreePredecessorHelper(p);
		if (next) {
			return next->data;
		}
		else {
			return kNInfinity;
		}

	}
	else {
		return kNInfinity;
	}
}



/***********************��������******************/
/**
* @brief Ѱ����С�ڵ�
* 
*/
TNode* BinSearchTree::TreeMinimumHelper(Root_ t) {
	while (t->left) {
		t = t->left;
	}
	return t;
}

/**
* @brief Ѱ�����ڵ�
*
*/
TNode* BinSearchTree::TreeMaximumHelper(Root_ t) {
	while (t->right) {
		t = t->right;
	}
	return t;
}

/**
* @brief �������
*
*/
void BinSearchTree::TreeVistHelper(TNode* p) {
	if (p) {
		TreeVistHelper(p->left);
		std::cout << p->data << " ";
		TreeVistHelper(p->right);
	}
}

/**
* @brief �����滻�����ڸ����ڵ�ɾ��
* @param target ���滻�����ĸ��ڵ�
* @param source Դ����
*/
void BinSearchTree::Transpant(TNode* target, TNode* source) {
	if (!target->parent) {
		root_ = source;
	}
	else if (target->parent->left == target) {
		target->parent->left = source;
	}
	else {
		target->parent->right = source;
	}

	if (source) {
		source->parent = target->parent;
	}
}

/**
* @brief Ѱ��ָ���ڵ�ĺ�̽ڵ�
*/
TNode* BinSearchTree::TreeSuccessorHelper(TNode* p) {
	if (p->right) {
		return TreeMinimumHelper(p->right);
	}
	TNode* next = p->parent;
	while (next && p == next->right) {
		p = next;
		next = next->parent;
	}
	return next;
}


/**
* @brief Ѱ��ָ���ڵ��ǰ���ڵ�
*/
TNode* BinSearchTree::TreePredecessorHelper(TNode* p) {
	if (p->left) {
		return TreeMaximumHelper(p->left);
	}
	TNode* pre = p->parent;
	while (pre && p == pre->left) {
		p = pre;
		pre = pre->parent;
	}
	return pre;
}