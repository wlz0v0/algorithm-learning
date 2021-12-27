#include <iostream>
#include <vector>
#include <exception>
using namespace std;

class String {
public:
    String() {
        length = 0;
        values = new char[length + 1];
        values[length] = '\0';
    }

    String(const char* str) {
        size_t length_ = strlen(str);
        length = length_;
        values = new char[length + 1];
        for (size_t i = 0; i < length; ++i) {
            values[i] = str[i];
        }
        values[length] = '\0';
    }

    String(const String& str) {
        length = str.length;
        values = new char[length + 1];
        for (size_t i = 0; i < length; ++i) {
            values[i] = str.values[i];
        }
        values[length] = '\0';
    }

    String& operator=(const String& str) {
        delete[] values;
        length = str.length;
        values = new char[length + 1];
        for (size_t i = 0; i < length; ++i) {
            values[i] = str.values[i];
        }
        values[length] = '\0';
    }

    ~String() {
        delete[] values;
    }

    size_t getLength() {
        return length;
    }

    char& operator[](size_t index) {
        return values[index];
    }

    friend ostream& operator<<(ostream& os, String& str) {
        os << str.values;
        return os;
    }

    friend istream& operator>>(istream& is, String& str) {
        char buffer[1001];
        memset(buffer, -1, 1001);
        cin >> buffer;
        if (buffer[1000] != -1 && buffer[1000] != '\0') {
            cerr << "String max length is 1000!" << endl;
            throw exception("String max length is 1000");
        }
        
         
        size_t len = strlen(buffer); 
        str.length = len;
        delete[] str.values;
        str.values = new char[len + 1];
        for (int i = 0; i <= len; ++i) {
            str.values[i] = buffer[i];
        }
        return is;
    }

private:
    size_t length;
    char* values;
};

void getNext(vector<int>& next, String& t) {
    int len = t.getLength();
    next[0] = -1;
    int j = 0;
    int k = -1;  
    while (j < len - 1) {
        if (k == -1 || t[j] == t[k]) {
            if (t[++j] == t[++k]) { 
                next[j] = next[k];
            } else {
                next[j] = k;
            }
        } else {
            k = next[k];
        }
    }
}

int KMPMatch(String& s, String& t) {
    vector<int> next(t.getLength());
    getNext(next, t);
    int i = 0;
    int j = 0;
    while (i < (signed)s.getLength() && j < (signed)t.getLength()) {
        if (j == -1 || s[i] == t[j]) {
            ++i;
            ++j;
        } else {
            j = next[j];
        }
    }
    if (j == t.getLength()) {
        return i - j;
    } else {
        return -1;
    }
}

int main()
{
    String s, t;
    cin >> s >> t;
    int a = KMPMatch(s, t);
    if (a != -1) {
        cout << "模式匹配, 起始下标为" << a << "\n";
    } else {
        cout << "匹配失败";
    }
    return 0;
}