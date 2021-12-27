#include <iostream>
#include <string>
#include <queue>

using namespace std;

class TreeNode
{
public:
	char val;
	TreeNode* lchild;
	TreeNode* rchild;
	TreeNode() : val(), lchild(nullptr), rchild(nullptr) {}
	TreeNode(char val, TreeNode* lchild_ = nullptr, TreeNode* rchild_ = nullptr) :
		val(val), lchild(lchild_), rchild(rchild_)
	{}
};

class BinaryTree
{
public:
	BinaryTree() = default;
	~BinaryTree() {
		destory(root);
	}

	void preOrderCreate(const string& str) {
		int index = 0;
		preOrderCreateRecursive(root, str, index);
	}

	void print() {
		string space = "\0";
		printRecursive(root, space);
	}

private:
	TreeNode* root;
	void preOrderCreateRecursive(TreeNode*& node, const string& str, int& index) {
		if (index == str.length()) {
			return;
		}
		if (str[index] == '0') {
			node = nullptr;
			++index;
		}
		else {
			node = new TreeNode(str[index]);
			++index;
			preOrderCreateRecursive(node->lchild, str, index);
			preOrderCreateRecursive(node->rchild, str, index);
		}
	}

	void destory(TreeNode* node) {
		if (node == nullptr) {
			return;
		}
		destory(node->lchild);
		destory(node->rchild);
		delete node;
	}

	void printRecursive(TreeNode* node, string space) {
		if (node == nullptr) {
			return;
		}
		space += "  ";
		printRecursive(node->rchild, space);
		cout << space << node->val << endl;
		printRecursive(node->lchild, space);
	}
};

int main()
{
	BinaryTree tree;
	string str;
	cin >> str;
	tree.preOrderCreate(str);
	tree.print();
    return 0;
}