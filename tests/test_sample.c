#include "unity.h"
#include "sample.h"

// 各テストの前に呼ばれる準備用の関数
void setUp(void) {}

// 各テストの後に呼ばれる後片付け用の関数
void tearDown(void) {}

// factorial関数をテストする
void test_factorial(void) {
    TEST_ASSERT_EQUAL_INT64(1, factorial(0));       // 0! = 1
    TEST_ASSERT_EQUAL_INT64(1, factorial(1));       // 1! = 1
    TEST_ASSERT_EQUAL_INT64(120, factorial(5));     // 5! = 120
    TEST_ASSERT_EQUAL_INT64(3628800, factorial(10)); // 10! = 3628800
}

// テストランナー
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_factorial);
    return UNITY_END();
}