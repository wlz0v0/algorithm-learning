#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Student {
public:
	int id;
	string name;
	vector<int> score;
	int sum;

	Student(int courseNum) : 
		id(0),
		name("\0"),
		score(courseNum),
		sum(0)
	{}

	friend ostream& operator<<(ostream& os, Student& stu) {
		os << stu.id << " " << stu.name << " " << stu.sum << " ";
		for (auto s : stu.score) {
			os << s << " ";
		}
		return os;
	}
};

int main()
{
	int n, m;
	cin >> n >> m;
	vector<Student> scores(n, Student(m));
	for (int i = 0; i < n; ++i) {
		cin >> scores[i].id >> scores[i].name;
		for (int j = 0; j < m; ++j) {
			int score;
			cin >> score;
			scores[i].sum += score;
			scores[i].score[j] = score;
		}
	}
	sort(scores.begin(), scores.end(), 
		[](const Student& lhs, const Student& rhs) {return lhs.sum >= rhs.sum; });
	for (auto st : scores) {
		cout << st << "\n";
	}
	return 0;
}