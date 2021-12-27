#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

constexpr int MAX_CAPACITY = 100;

template <typename T>
class Stack {
public:
    Stack() : vals(new T[MAX_CAPACITY]), vals_size(0), capacity(MAX_CAPACITY)
    {}

    ~Stack() {
        delete[] vals;
        vals_size = 0;
        capacity = 0;
    }
    void push(T val) {
        if (vals_size == capacity) {
            cout << "Stack is full!" << endl;
            return;
        }
        vals[vals_size] = val;
        ++vals_size;
    }

    void pop() {
        vals[vals_size - 1] = 0;
        --vals_size;
    }

    T top() {
        return vals[vals_size - 1];
    }

    bool empty() {
        return vals_size == 0;
    }

    size_t size() {
        return vals_size;
    }

private:
    T* vals;
    size_t vals_size;
    size_t capacity;
};

// 优先级
unordered_map<char, int> priority = {
        pair<char, int>('*', 2),
        pair<char, int>('/', 2),
        pair<char, int>('+', 1),
        pair<char, int>('-', 1)
};

void transformInToPost(const string& inExpression) {
    Stack<char> operators;
    for (char c : inExpression) {
        if (isalpha(c)) {
            cout << c;
        } else {
            while (!operators.empty() && priority[c] <= priority[operators.top()]) {
                cout << operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }
    while (!operators.empty()) {
        cout << operators.top();
        operators.pop();
    }
    cout << endl;
}

int main()
{
    int cnt, length;
    string expression;
    string ans;
    cin >> cnt;
    while (cnt) {
        cin >> length;
        cin >> expression;
        transformInToPost(expression);
        --cnt;
    }
    return 0;
}