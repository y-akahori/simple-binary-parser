#include "sample.h"

long long factorial(int n) {
    if (n < 0) {
        return -1; // エラーケース
    }
    if (n == 0) {
        return 1;
    }
    long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}