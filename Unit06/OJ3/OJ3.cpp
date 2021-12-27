#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <map>

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
		setPriorAndNext();
	}

	void levelOrderTravel() {
		queue<TreeNode*> q;
		q.push(root);
		TreeNode* front = nullptr;

		while (!q.empty()) {
			front = q.front();
			q.pop();
			
			cout << prior[front->val] << " " << next[front->val] << " ";
			if (front->lchild != nullptr) {
				q.push(front->lchild);
			}
			if (front->rchild != nullptr) {
				q.push(front->rchild);
			}
		}
		cout << "\n";
	}

private:
	TreeNode* root = nullptr;

	map<int, int> prior;
	map<int, int> next;

	void destory(TreeNode* node) {
		if (node == nullptr) {
			return;
		}
		destory(node->lchild);
		destory(node->rchild);
		delete node;
	}

	void setPriorAndNext() {
		vector<int> values = {0};
		inOrderTravelRecursive(root, values);
		values.push_back(0);
		for (int i = 1; i < values.size() - 1; ++i) {
			prior.insert(pair<int, int>(values[i], values[i - 1]));
			next.insert(pair<int, int>(values[i], values[i + 1]));
		}
	}

	void inOrderTravelRecursive(TreeNode* node, vector<int>& values) {
		if (node == nullptr) {
			return;
		}
		inOrderTravelRecursive(node->lchild, values);
		values.push_back(node->val);
		inOrderTravelRecursive(node->rchild, values);
	}
};

int main()
{
	int group;
	cin >> group;
	while (group--) {
		BinaryTree tree;
		tree.levelOrderCreate();
		tree.levelOrderTravel();
	}
	return 0;
}
