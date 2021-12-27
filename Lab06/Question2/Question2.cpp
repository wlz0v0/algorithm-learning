#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

class HashTable {
public:
	int findCnt;

	HashTable(int size, int p) : size(size), table(size), findCnt(0), p(p) {}
	void insert(const string& name) {
		int h = getHash(name);
		table[h % p].push_back(name);
	}

	bool find(const string& name) {
		int h = getHash(name);
		auto arr = table[h % p];
		for (int i = 0; i < arr.size(); ++i) {
			++findCnt;
			if (arr[i] == name) {
				return true;
			}
		}
		return false;
	}

	int getHash(const string& name) {
		int res = 0;
		for (int i = 0; i < name.size(); ++i) {
			res += (name[i] * (i + 1));
		}
		return res;
	}

	void print() {
		for (int i = 0; i < table.size(); ++i) {
			if (table[i].empty()) {
				continue;
			}
			cout << i;
			for (int j = 0; j < table[i].size(); ++j) {
				  cout << " " << table[i][j] << " ";
			}
			cout << "\n";
		}
	}

private:
	// 用vector当链表
	vector<vector<string>> table;
	int size;
	int p;
};

int main() {
	int cnt[40] = { 0 };
	const string names[30] = {
			"donghaonan",
			"fanghanhui",
			"fangchunyu",
			"fengminyan",
			"huangyitian",
			"lijinze",
			"limingyang",
			"lixin",
			"linjiale",
			"majun",
			"maxiangyu",
			"mazhi",
			"minnan",
			"shezihan",
			"wangjincheng",
			"wuchangxv",
			"xiaohaoyue",
			"yangcan",
			"yangzhenye",
			"zhangshihao",
			"zhaoyuquan",
			"baoguanqun",
			"guoziyu",
			"linjiaqi",
			"songzhiyi",
			"xieyuxin",
			"zhangyiming",
			"anqiucheng",
			"chuzhibo",
			"xiajunhao"
	};
	HashTable table(40, 40);
	for (int i = 0; i < 30; ++i) {
		table.insert(names[i]);
	}
	for (int i = 0; i < 30; ++i) {
		table.find(names[i]);
	}
	table.print();
	cout << "AST: " << table.findCnt / 30.0 << "\n";
	return 0;
}