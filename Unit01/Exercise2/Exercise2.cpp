#include <stdio.h>
#include <ctime>

using namespace std;

long long foo(long long n) {
    int sum = 0;
    clock_t start = clock();
    for (long long i = 0; i < n; i++)
        for (long long j = 0; j < i * i; j++)
            if (j % i == 0)
            for (long long k = 0; k < j; ++k)
            sum++;
    return (clock() - start);
}

int main()
{
    long long n = 300;
    long long ret = foo(n);
    printf("When n=%lld, it takes %lld ms", n, ret);
}