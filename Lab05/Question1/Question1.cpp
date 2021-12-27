#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class TableBody {
public:
	int index;
	TableBody* next;

	TableBody(int index, TableBody* next = nullptr) :
		index(index),
		next(next)
	{}
};

template <typename T>
class TableHead {
public:
	T data;
	TableBody* first;

	TableHead(const T& data, TableBody* first = nullptr) :
		data(data),
		first(first)
	{}

	~TableHead() {
		TableBody* cur = first;
		TableBody* pre = nullptr;
		while (cur != nullptr) {
			pre = cur;
			cur = cur->next;
			delete pre;
		}
	}

	// 尾插法
	void push_back(int index) {
		TableBody* temp = new TableBody(index);
		if (first == nullptr) {
			first = temp;
			return;
		}

		TableBody* node = first;
		while (node->next != nullptr) {
			node = node->next;
		}
		node->next = temp;
	}
};

class Graph {
public:
	Graph() {
		int vertexCnt, arcCnt;
		cout << "请输入顶点数和边数\n";
		cin >> vertexCnt >> arcCnt;

		char data;
		cout << "请输入所有点的数据\n";
		while (vertexCnt--) {
			cin >> data;
			vertices.push_back(TableHead<char>(data));
		}

		// 建立邻接表
		int srcIndex, destIndex;
		cout << "请输入所有边的数据\n";
		while (arcCnt--) {
			cin >> srcIndex >> destIndex;
			vertices[srcIndex].push_back(destIndex);
		}
	}

	void dfsTravel() {
		vector<int> visited(vertices.size(), 0);
		for (int i = 0; i < vertices.size(); ++i) {
			dfsTravelRecursive(i, visited);
		}
		cout << "\n";
	}

	void bfsTravel() {
		queue<TableHead<char>> q;
		vector<int> visited(vertices.size(), 0);
		for (int i = 0; i < vertices.size(); ++i) {
			if (!visited[i]) {
				q.push(vertices[i]);
				visited[i] = true;
			}
			while (!q.empty()) {
				cout << q.front().data << " ";
				auto& first = q.front().first;
				while (first != nullptr) {
					int index = first->index;
					if (!visited[index]) {
						q.push(vertices[index]);
						visited[index] = true;
					}
					first = first->next;
				}
				q.pop();
			}
		}
		cout << "\n";
	}

private:
	vector<TableHead<char>> vertices;

	void dfsTravelRecursive(int index, vector<int>& visited) {
		if (visited[index]) {
			return;
		}

		visited[index] = true;
		cout << vertices[index].data << " ";

		auto first = vertices[index].first;
		while (first != nullptr) {
			dfsTravelRecursive(first->index, visited);
			first = first->next;
		}
	}
};

int main()
{
	Graph g;
	g.dfsTravel();
	g.bfsTravel();
	return 0;
}