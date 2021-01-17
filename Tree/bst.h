/**
* @file			bst.h
* @author		tanghf
* @date			2021-01-17
* @version		V1.0
* @copyright    Copyright (c) 2021
*
*/
#ifndef BST_H_
#include <vector>

typedef int Tp;
typedef struct TNode {
	Tp data;
	TNode* parent;
	TNode* left;
	TNode* right;
}TNode;

/**
* @brief ¶þ²æËÑË÷Ê÷
* 
*/
class BinSearchTree {
private:
	
	typedef TNode* Root_ ;
	Root_ root_ = nullptr;

private:
	enum { kNInfinity = -65535};
	void TreeVistHelper(TNode* p);
	void Transpant(TNode* target, TNode* source);
	TNode* TreeMinimumHelper(Root_ t);
	TNode* TreeMaximumHelper(Root_ t);
	TNode* TreeSuccessorHelper(TNode* p);
	TNode* TreePredecessorHelper(TNode* p);
public:
	BinSearchTree(){}
	BinSearchTree(std::vector<Tp> tree);
	~BinSearchTree();
	void TreeVist();
	TNode* TreeSearch(Tp key);
	void TreeInsert(Tp key);	
	void TreeDelete(Tp key);	
	Tp TreeMinimum() { 
		if (!root_) 
			return kNInfinity;
		return TreeMinimumHelper(root_)->data;
	}
	Tp TreeMaximum(){ 
		if (!root_)
			return kNInfinity;
		return TreeMaximumHelper(root_)->data; 
	}
	Tp TreeSuccessor(Tp key);
	Tp TreePredecessor(Tp key);
};

#endif // !BST_H_

