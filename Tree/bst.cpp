#include <iostream>
#include "bst.h"


/*
* @brief 将数组转化为二叉搜索树
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
* @brief 按顺序遍历搜索树
*
*/
void BinSearchTree::TreeVist() {
	TreeVistHelper(root_);
	std::cout << std::endl;
}

/**
* @brief 在树中搜索目标值
* @return 若存在返回值为目标值的节点的，否则范围空指针
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
* @brief 在搜索树中插入元素
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
* @brief 删除指定数据
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
			TNode* next = TreeMinimumHelper(p->right);  /// 找到p节点的后继节点
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
* @brief 寻找目标值的下一个元素
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
* @brief 寻找目标值的前一个元素
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



/***********************辅助函数******************/
/**
* @brief 寻找最小节点
* 
*/
TNode* BinSearchTree::TreeMinimumHelper(Root_ t) {
	while (t->left) {
		t = t->left;
	}
	return t;
}

/**
* @brief 寻找最大节点
*
*/
TNode* BinSearchTree::TreeMaximumHelper(Root_ t) {
	while (t->right) {
		t = t->right;
	}
	return t;
}

/**
* @brief 中序遍历
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
* @brief 子树替换，用于辅助节点删除
* @param target 被替换子树的根节点
* @param source 源子树
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
* @brief 寻找指定节点的后继节点
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
* @brief 寻找指定节点的前驱节点
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