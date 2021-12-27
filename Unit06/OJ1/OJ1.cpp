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

	int getLeavesCount() {
		int count = 0;
		queue<TreeNode*> q;
		q.push(root);
		TreeNode* front = nullptr;
		bool isLeave = true;
		while (!q.empty()) {
			front = q.front();
			q.pop();
			isLeave = true;
			if (front->lchild != nullptr) {
				q.push(front->lchild);
				isLeave = false;
			}
			if (front->rchild != nullptr) {
				q.push(front->rchild);
				isLeave = false;
			}
			if (isLeave) {
				++count;
			}
		}
		return count;
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
		cout << tree.getLeavesCount() << endl;
	}
	return 0;
}
