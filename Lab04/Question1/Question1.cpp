#include <iostream>
#include <string>
#include <stack>
#define ITERATIVE

#ifdef ITERATIVE
#define PRE_ORDER_TRAVEL() preOrderTravelIterative()
#define IN_ORDER_TRAVEL() inOrderTravelIterative()
#define POST_ORDER_TRAVEL() postOrderTravelIterative()
#else
#define PRE_ORDER_TRAVEL() preOrderTravelRecursive(root)
#define IN_ORDER_TRAVEL() inOrderTravelRecursive(root)
#define POST_ORDER_TRAVEL() postOrderTravelRecursive(root)
#endif // ITERATIVE

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

	void preOrderTravel() {
		PRE_ORDER_TRAVEL();
		cout << "\n";
	}

	void inOrderTravel() {
		IN_ORDER_TRAVEL();
		cout << "\n";
	}

	void postOrderTravel() {
		POST_ORDER_TRAVEL();
		cout << "\n";
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
		} else {
			node = new TreeNode(str[index]);
			++index;
			preOrderCreateRecursive(node->lchild, str, index);
			preOrderCreateRecursive(node->rchild, str, index);
		}
	}

	void preOrderTravelRecursive(TreeNode* node) {
		if (node == nullptr) {
			return;
		}
		cout << node->val;
		preOrderTravelRecursive(node->lchild);
		preOrderTravelRecursive(node->rchild);
	}

	void preOrderTravelIterative() {
		stack<TreeNode*> s;
		TreeNode* top = root;
		s.push(top);
		while (!s.empty()) {
			cout << s.top()->val;
			top = s.top();
			s.pop();
			if (top->rchild != nullptr) {
				s.push(top->rchild);
			}
			if (top->lchild != nullptr) {
				s.push(top->lchild);
			}
		}
	}

	void inOrderTravelRecursive(TreeNode* node) {
		if (node == nullptr) {
			return;
		}
		inOrderTravelRecursive(node->lchild);
		cout << node->val;
		inOrderTravelRecursive(node->rchild);
	}

	void inOrderTravelIterative() {
		stack<TreeNode*> s;
		TreeNode* temp = root;
		while (temp != nullptr || !s.empty()) {
			if (temp != nullptr) {
				s.push(temp);
				temp = temp->lchild;
			} else {
				temp = s.top();
				cout << temp->val;
				s.pop();
				temp = temp->rchild;
			}
		}
	}

	void postOrderTravelRecursive(TreeNode* node) {
		if (node == nullptr) {
			return;
		}
		postOrderTravelRecursive(node->lchild);
		postOrderTravelRecursive(node->rchild);
		cout << node->val;
	}

	void postOrderTravelIterative() {
		stack<TreeNode*> s;
		TreeNode* pre = nullptr;
		TreeNode* cur = root;
		s.push(cur);
		while (!s.empty()) {
			cur = s.top();
			if ((cur->lchild == nullptr && cur->rchild == nullptr) ||
				((pre != nullptr) && (pre == cur->lchild || pre == cur->rchild))) {
				cout << cur->val;
				pre = cur;
				s.pop();
			} else {
				if (cur->rchild != nullptr) {
					s.push(cur->rchild);
				}
				if (cur->lchild != nullptr) {
					s.push(cur->lchild);
				}
			}
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
};

int main()
{
	BinaryTree tree;
	string input;
	cin >> input;
	tree.preOrderCreate(input);
	tree.preOrderTravel();
	tree.inOrderTravel();
	tree.postOrderTravel();
    return 0;
}