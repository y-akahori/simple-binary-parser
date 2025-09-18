#ifndef STREAMING_PARSER_H
#define STREAMING_PARSER_H

#include <stdint.h>
#include <stdio.h>

#define PARSER_MAX_BODY_LENGTH 100

// パーサーの状態を定義する列挙型
typedef enum {
    STATE_WAITING_FOR_STX,
    STATE_WAITING_FOR_STX_2,
    STATE_READING_LENGTH_1,
    STATE_READING_LENGTH_2,
    STATE_READING_BODY,
    STATE_READING_ETX_1,
    STATE_READING_ETX_2
} ParserState_e;

// パーサーの状態を管理する構造体
typedef struct {
    ParserState_e state;
    uint8_t body_buffer[PARSER_MAX_BODY_LENGTH];
    uint16_t expected_body_length;
    uint16_t current_body_index;
    uint8_t temp_field_buffer[2]; // LENGTHやETXの一時保存用
} Parser;

// --- 関数プロトタイプ宣言 ---

/**
 * @brief パーサーを初期状態にリセットする
 * @param parser パーサー構造体へのポインタ
 */
void parser_init(Parser* parser);

/**
 * @brief 1バイトのデータを処理する
 * @param parser パーサー構造体へのポインタ
 * @param byte 入力データ (1バイト)
 */
void parser_process_byte(Parser* parser, uint8_t byte);

#endif // STREAMING_PARSER_H