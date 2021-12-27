#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

template <typename T>
class Stack {
public:
    Stack() : vals(new T[16]), vals_size(0), capacity(16)
    {}

    ~Stack() {
        delete[] vals;
        vals_size = 0;
        capacity = 0;
    }
    void push(T val) {
        if (vals_size == capacity) {
            allocate();
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

    void allocate() {
        delete[] vals;
        capacity *= 2;
        vals = new T[capacity];
    }
};

bool isValid(string input) {
    if (input.size() % 2 == 1) {
        return false;
    }

    unordered_map<char, char> pairs = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };

    Stack<char> s;
    for (char ch : input) {
        // 判断是左括号还是右括号
        if (pairs.count(ch)) {
            if (s.empty() || s.top() != pairs[ch]) {
                return false;
            }
            s.pop();
        } else {
            s.push(ch);
        }
    }
    return s.empty();
}

int main()
{
    string input;
    cin >> input;
    if (isValid(input)) {
        cout << "匹配" << endl;
    } else {
        cout << "此串括号匹配不合法" << endl;
    }
    return 0;
}