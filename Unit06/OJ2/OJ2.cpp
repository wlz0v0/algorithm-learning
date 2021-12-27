#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

class TreeNode
{
public:
	int val;
	TreeNode* lchild;
	TreeNode* rchild;
	TreeNode() : val(), lchild(nullptr), rchild(nullptr) {}
	TreeNode(int val, TreeNode* lchild_ = nullptr, TreeNode* rchild_ = nullptr) :
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

	void levelOrderCreate() {
		int val;
		cin >> val;
		vector<int> values;
		while (val != -1) {
			values.push_back(val);
			cin >> val;
		}

		queue<TreeNode*> q;
		int index = 0;
		root = new TreeNode(values[index++]);
		q.push(root);

		TreeNode* front = nullptr;
		while (!q.empty()) {
			front = q.front();
			q.pop();
			if (index < values.size()) {
				if (values[index] != 0) {
					front->lchild = new TreeNode(values[index]);
					q.push(front->lchild);
				}
				++index;
			}
			if (index < values.size()) {
				if (values[index] != 0) {
					front->rchild = new TreeNode(values[index]);
					q.push(front->rchild);
				}
				++index;
			}
		}
	}

	void swapLeftAndRight() {
		queue<TreeNode*> q;
		q.push(root);
		TreeNode* front = nullptr;
		TreeNode* temp = nullptr;

		while (!q.empty()) {
			front = q.front();
			q.pop();
			
			temp = front->lchild;
			front->lchild = front->rchild;
			front->rchild = temp;

			if (front->lchild != nullptr) {
				q.push(front->lchild);
			}
			if (front->rchild != nullptr) {
				q.push(front->rchild);
			}
		}
	}

	void levelOrderTravel() {
		queue<TreeNode*> q;
		q.push(root);
		TreeNode* front = nullptr;
		
		while (!q.empty()) {
			front = q.front();
			q.pop();
			if (front == nullptr) {
				cout << 0 << " ";
				continue;
			} 
			cout << front->val << " ";
			q.push(front->lchild);
			q.push(front->rchild);
		}
		cout << "\n";
	}

private:
	TreeNode* root;

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
	int group;
	cin >> group;
	while (group--) {
		BinaryTree tree;
		tree.levelOrderCreate();
		tree.swapLeftAndRight();
		tree.levelOrderTravel();
	}
	return 0;
}
