#include <iostream>
#include <deque>
#include <cassert>
#include "BinarySearchTree.h"

using namespace std;

TreeNode::TreeNode() :
	val(0),
	lchild(nullptr),
	rchild(nullptr)
{}

TreeNode::TreeNode(int val_, TreeNode* lchild_, TreeNode* rchild_) :
	val(val_),
	lchild(lchild_),
	rchild(rchild_)
{}

BinarySearchTree::BinarySearchTree(int val_)
{
	root = new TreeNode();
	root->val = val_;
}

BinarySearchTree::~BinarySearchTree()
{
	destructorRecursive(root);
}

void BinarySearchTree::nodeInsert(int val_)
{
#ifdef ITERATIVE
	nodeInsertIterative(val_);
#else
	nodeInsertRecursive(val_, root);
#endif
}

void BinarySearchTree::nodeInsertIterative(int val_)
{
	TreeNode* parent = nullptr;
	TreeNode* cur = root;
	assert(cur != nullptr);
	while (cur != nullptr)
	{
		parent = cur;
		if (val_ < cur->val)
			cur = cur->lchild;
		else if (val_ > cur->val)
			cur = cur->rchild;
	}
	cur = new TreeNode(val_);
	if (val_ <= parent->val)
		parent->lchild = cur;
	else if (val_ >= cur->val)
		parent->rchild = cur;
}

void BinarySearchTree::nodeInsertRecursive(int val_, TreeNode*& node)
{
	if (node == nullptr)
	{
		node = new TreeNode(val_);
		return;
	}
	if (val_ < node->val)
		nodeInsertRecursive(val_, node->lchild);
	else
		nodeInsertRecursive(val_, node->rchild);
}

bool BinarySearchTree::nodeDelete(int val_)
{
	TreeNode* parent = nullptr;
	TreeNode* cur = root;
	while (cur != nullptr)
	{
		if (val_ == cur->val)
			break;
		else if (val_ < cur->val)
		{
			parent = cur;
			cur = cur->lchild;
		}
		else
		{
			parent = cur;
			cur = cur->rchild;
		}
	}

	if (cur == nullptr)
		return false;
	else if (cur->lchild == nullptr && cur->rchild == nullptr)
	{
		if (cur == parent->lchild) 
		{
			parent->lchild = nullptr;
		} 
		else
		{
			parent->rchild = nullptr;
		}
		delete cur;
		return true;
	}
	else if (cur->lchild == nullptr)
	{
		cur->val = cur->rchild->val;
		delete cur->rchild;
		cur->rchild = nullptr;
		return true;
	}
	else if (cur->rchild == nullptr)
	{
		cur->val = cur->lchild->val;
		delete cur->lchild;
		cur->lchild = nullptr;
		return true;
	}
	else // 节点度为2
	{
#ifdef ITERATIVE
		std::pair<TreeNode*, TreeNode*> max = nodeMaxIterative(cur->lchild);
#else
		TreeNode* max = nodeMaxRecursive(cur->lchild);
#endif
		max.first->lchild == max.second ? max.first->lchild = nullptr : max.first->rchild = nullptr;
		cur->val = max.second->val;
		delete max.second;
		max.second = nullptr;
		return true;
	}
}

TreeNode* BinarySearchTree::nodeFind(int val_)
{
#ifdef ITERATIVE
	return nodeFindIterative(val_, root);
#else
	return nodeFindRecursive(val_, root);
#endif
}

TreeNode* BinarySearchTree::nodeFindIterative(int val_, TreeNode* node)
{
	while (node != nullptr)
	{
		if (val_ == node->val)
			return node;
		else if (val_ > node->val)
			node = node->rchild;
		else
			node = node->lchild;
	}
	return nullptr;
}

TreeNode* BinarySearchTree::nodeFindRecursive(int val_, TreeNode* node)
{
	if (node == nullptr)
		return nullptr;
	if (val_ == node->val)
		return node;
	else if (val_ < node->val)
		return nodeFindRecursive(val_, node->lchild);
	else
		return nodeFindRecursive(val_, node->rchild);
}

void BinarySearchTree::preOrder()
{
	preOrderRecursive(root);
	std::cout << std::endl;
}

void BinarySearchTree::preOrderRecursive(TreeNode* node)
{
	if (node == nullptr)
		return;
	std::cout << node->val << std::endl;
	preOrderRecursive(node->lchild);
	preOrderRecursive(node->rchild);
}

void BinarySearchTree::inOrder()
{
	inOrderRecursive(root);
	std::cout << std::endl;
}

void BinarySearchTree::inOrderRecursive(TreeNode* node)
{
	if (node == nullptr)
		return;
	inOrderRecursive(node->lchild);
	std::cout << node->val << std::endl;
	inOrderRecursive(node->rchild);
}

void BinarySearchTree::postOrder()
{
	postOrderRecursive(root);
	std::cout << std::endl;
}

void BinarySearchTree::levelOrder()
{
	std::deque<TreeNode*> q;
	q.push_back(root);
	while (!q.empty())
	{
		TreeNode* front = q.front();
		std::cout << front->val << std::endl;
		q.pop_front();
		if (front->lchild)
			q.push_back(front->lchild);
		if (front->rchild)
			q.push_back(front->rchild);
	}
}

void BinarySearchTree::print()
{
	string space = "\0";
	printRecursive(root, space);
}

void BinarySearchTree::postOrderRecursive(TreeNode* node)
{
	if (node == nullptr)
		return;
	postOrderRecursive(node->lchild);
	postOrderRecursive(node->rchild);
	std::cout << node->val << std::endl;
}

void BinarySearchTree::destructorRecursive(TreeNode* node)
{
	if (node != nullptr)
	{
		return destructorRecursive(node->lchild);
		return destructorRecursive(node->rchild);
	}
	delete node;
}

std::pair<TreeNode*, TreeNode*> BinarySearchTree::nodeMaxIterative(TreeNode* node)
{
	TreeNode* parent = nullptr;
	while (node->rchild != nullptr)
	{
		parent = node;
		node = node->rchild;
	}
	return std::pair<TreeNode*, TreeNode*>(parent, node);
}

TreeNode* BinarySearchTree::nodeMaxRecursive(TreeNode* node)
{
	if (node->rchild == nullptr)
		return node;
	return nodeMaxRecursive(node->rchild);
}

void BinarySearchTree::printRecursive(TreeNode* node, string space)
{
	if (node == nullptr) {
		return;
	}
	space += "  ";
	printRecursive(node->rchild, space);
	cout << space << node->val << endl;
	printRecursive(node->lchild, space);
}
