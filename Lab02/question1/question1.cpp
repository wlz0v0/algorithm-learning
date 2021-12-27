#include <iostream>

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

int main()
{
    Stack<int> s;
    int decimal;
    cout << "请输入要转换的十进制数" << endl;
    cin >> decimal;
    while (decimal) {
        s.push(decimal % 8);
        decimal /= 8;
    }
    while (!s.empty()) {
        cout << s.top();
        s.pop();
    }
    cout << endl;
}