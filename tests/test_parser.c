#include "unity.h"
#include "parser.h"

// <<< この2つの関数を追加 >>>
// 各テストの前に呼ばれる準備用の関数
void setUp(void) {
    // 今回は準備不要なので中身は空
}

// 各テストの後に呼ばれる後片付け用の関数
void tearDown(void) {
    // 今回は後片付け不要なので中身は空
}

// テストケース1: STXマーカーを正しく変換できるか
void test_read_u16_be_for_STX(void) {
    uint8_t stx_bytes[] = {0xEB, 0x90};
    uint16_t expected = 0xEB90;
    uint16_t actual = read_u16_be(stx_bytes);
    TEST_ASSERT_EQUAL_HEX16(expected, actual);
}

// テストケース2: ETXマーカーを正しく変換できるか
void test_read_u16_be_for_ETX(void) {
    uint8_t etx_bytes[] = {0xC5, 0x79};
    uint16_t expected = 0xC579;
    uint16_t actual = read_u16_be(etx_bytes);
    TEST_ASSERT_EQUAL_HEX16(expected, actual);
}

// テストランナー
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_read_u16_be_for_STX);
    RUN_TEST(test_read_u16_be_for_ETX);
    return UNITY_END();
}