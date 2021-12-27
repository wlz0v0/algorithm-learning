#include <stdio.h>
#include <malloc.h>

int search(int arr[], int size) {
    int left = 0, right = size - 1, mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (arr[mid] - mid == 0) {
            return mid;
        } else if (arr[mid] - mid > 0) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return -1;
}

int main() {
    int cnt, size, * arr;
    scanf("%d", &cnt);
    while (cnt) {
        scanf("%d", &size);
        arr = (int*)malloc(sizeof(int) * size);
        for (int i = 0; i < size; ++i) {
            scanf("%d", arr + i);
        }
        int res = search(arr, size);
        printf("%d\n", res);
        free(arr);
        --cnt;
    }
    return 0;
}