#include <stdio.h>

typedef struct Node {
    int index;
    int pwd;
    Node* next;

    Node(int index, int pwd) :
        index(index),
        pwd(pwd),
        next(nullptr) {}
};

typedef struct List {
    Node* pre;
    Node* head;

    List(int index, int pwd) : head(new Node(index, pwd)), pre(head) {
        head->next = head;
    }

    ~List() {}

    void insert(int index, int pwd) {
        Node* node = new Node(index, pwd);
        Node* temp = head;
        while (index != 2) {
            temp = temp->next;
            --index;
        }
        temp->next = node;
        node->next = head;
    }

    Node* remove() {
        
        Node* next = head->next;
        pre->next = next;

        delete head;
        return next;
    }
};

int main()
{
    int init_m, person_cnt, index, pwd;
    scanf_s("%d %d", &init_m, &person_cnt);
    scanf_s("%d %d", &index, &pwd);
    int remove_cnt = person_cnt;
    --person_cnt;
    List list(index, pwd);
    while (person_cnt) {
        scanf_s("%d %d", &index, &pwd);
        list.insert(index, pwd);
        --person_cnt;
    }
    int num = 1;
    while (remove_cnt) {
        if (num == init_m) {
            init_m = list.head->pwd;
            printf("%d ", list.head->index);
            list.head = list.remove();
            --remove_cnt;
            num = 1;
            continue;
        }
        list.pre = list.head;
        list.head = list.head->next;
        ++num;
    }
    return 0;   
}