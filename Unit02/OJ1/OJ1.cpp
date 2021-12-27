#include <stdio.h>

typedef struct Node {
	int val;
	Node* next;

	Node() : Node(0) {}
	Node(int val) : val(val), next(nullptr) {}
};

typedef struct List {
	Node* pre;

	List() {
		pre = new Node();
	}

	~List() {
		Node* temp = pre;
		while (pre != nullptr) {
			temp = temp->next;
			delete pre;
			pre = temp;
		}
	}

	void insert(int val) {
		Node* node = new Node;
		Node* temp = pre;
		while (temp->next != nullptr && val <= temp->next->val)
		{
			temp = temp->next;
		}
		node->val = val;
		node->next = temp->next;
		temp->next = node;
	}

	void print() {
		Node* temp = pre->next;
		while (temp != nullptr) {
			printf("%d ", temp->val);
			temp = temp->next;
		}
		printf("\n");
	}

	void merge(List& list_)
	{
		Node* temp1 = pre->next;
		Node* temp2 = list_.pre->next;
		Node* temp3 = pre;
		while (temp1 != nullptr && temp2 != nullptr)
		{
			if (temp1->val >= temp2->val)
			{
				temp3->next = temp1;
				temp3 = temp1;
				temp1 = temp1->next;
			}
			else
			{
				temp3->next = temp2;
				temp3 = temp2;
				temp2 = temp2->next;
			}
		}
		while (temp1 != nullptr)
		{
			temp3->next = temp1;
			temp3 = temp1;
			temp1 = temp1->next;
		}
		while (temp2 != nullptr)
		{
			temp3->next = temp2;
			temp3 = temp2;
			temp2 = temp2->next;
		}
		temp3->next = nullptr;
		list_.pre = nullptr;
	}
};

int main()
{
	int cnt, len1, len2, temp;
	scanf("%d", &cnt);
	while (cnt) {
		List l1, l2;
		scanf("%d %d", &len1, &len2);
		while (len1) {
			scanf("%d", &temp);
			l1.insert(temp);
			--len1;
		}
		while (len2) {
			scanf("%d", &temp);
			l2.insert(temp);
			--len2;
		}
		l1.merge(l2);
		l1.print();
		--cnt;
	}
	return 0;
}