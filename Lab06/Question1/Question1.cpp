#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

int main()
{
    int cnt;
    cin >> cnt;
    int val;
    cin >> val;
    BinarySearchTree t(val);
    --cnt;
    while (cnt--) {
        cin >> val;
        t.nodeInsert(val);
    }
    t.print();
    cout << "输入查找数据个数\n";
    int findCnt;
    cin >> findCnt;
    while (findCnt--) {
        int findNum;
        cin >> findNum;
        TreeNode* n = t.nodeFind(findNum);
        if (n == nullptr) {
            cout << "没有这个\n";
        }
        else {
            cout << "有\n";
        }
    }
    return 0;
}