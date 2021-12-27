#pragma once
#define ITERATIVE
#include <utility>
#include <string>
class TreeNode
{
public:
	int val;
	TreeNode* lchild;
	TreeNode* rchild;
	TreeNode();
	TreeNode(int val_, TreeNode* lchild_ = nullptr, TreeNode* rchild_ = nullptr);
};

class BinarySearchTree
{
public:
	BinarySearchTree(int val_);
	~BinarySearchTree();
	void nodeInsert(int val_);
	bool nodeDelete(int val_);
	TreeNode* nodeFind(int val_);
	void preOrder();
	void inOrder();
	void postOrder();
	void levelOrder();
	void print();
private:
	TreeNode* root;
	void nodeInsertIterative(int val_);
	void nodeInsertRecursive(int val_, TreeNode*& node);

	TreeNode* nodeFindIterative(int val_, TreeNode* node);
	TreeNode* nodeFindRecursive(int val_, TreeNode* node);

	void destructorRecursive(TreeNode* node);

	void preOrderRecursive(TreeNode* node);
	void inOrderRecursive(TreeNode* node);
	void postOrderRecursive(TreeNode* node);

	std::pair<TreeNode*, TreeNode*> nodeMaxIterative(TreeNode* node);
	TreeNode* nodeMaxRecursive(TreeNode* node);

	void printRecursive(TreeNode* node, std::string space);
};
