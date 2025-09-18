#include "streaming_parser.h"

// --- 定義 (ヘッダーで宣言していない内部定数) ---
static const uint8_t STX_BYTE_1 = 0xEB;
static const uint8_t STX_BYTE_2 = 0x90;
static const uint16_t ETX_MARKER = 0xC579;

// --- 内部ヘルパー関数 ---
static uint16_t read_u16_be(const uint8_t* buffer) {
    return (uint16_t)((buffer[0] << 8) | buffer[1]);
}

// 有効なパケットが見つかったときに呼び出される関数
static void on_packet_found(const uint8_t* body, uint16_t length) {
    for (uint16_t i = 0; i < length; ++i) {
        printf("0x%02x%s", body[i], (i == length - 1) ? "" : " ");
    }
    printf("\n");
}

// --- 公開関数の実装 ---

void parser_init(Parser* parser) {
    parser->state = STATE_WAITING_FOR_STX;
    parser->current_body_index = 0;
    parser->expected_body_length = 0;
}

void parser_process_byte(Parser* parser, uint8_t byte) {
    switch (parser->state) {
        case STATE_WAITING_FOR_STX:
            if (byte == STX_BYTE_1) {
                parser->state = STATE_WAITING_FOR_STX_2;
            }
            break;

        case STATE_WAITING_FOR_STX_2:
            if (byte == STX_BYTE_2) {
                parser->state = STATE_READING_LENGTH_1;
            } else {
                parser_init(parser); // 不正なシーケンスなら初期状態へ
            }
            break;

        case STATE_READING_LENGTH_1:
            parser->temp_field_buffer[0] = byte;
            parser->state = STATE_READING_LENGTH_2;
            break;

        case STATE_READING_LENGTH_2:
            parser->temp_field_buffer[1] = byte;
            parser->expected_body_length = read_u16_be(parser->temp_field_buffer);
            
            if (parser->expected_body_length > 0 && parser->expected_body_length <= PARSER_MAX_BODY_LENGTH) {
                parser->current_body_index = 0;
                parser->state = STATE_READING_BODY;
            } else {
                parser_init(parser); // 不正なLENGTHなら初期状態へ
            }
            break;

        case STATE_READING_BODY:
            parser->body_buffer[parser->current_body_index++] = byte;
            if (parser->current_body_index >= parser->expected_body_length) {
                parser->state = STATE_READING_ETX_1;
            }
            break;

        case STATE_READING_ETX_1:
            parser->temp_field_buffer[0] = byte;
            parser->state = STATE_READING_ETX_2;
            break;

        case STATE_READING_ETX_2:
            parser->temp_field_buffer[1] = byte;
            if (read_u16_be(parser->temp_field_buffer) == ETX_MARKER) {
                // 有効なパケットを検出！
                on_packet_found(parser->body_buffer, parser->expected_body_length);
            }
            parser_init(parser); // 1パケットの処理が完了したので、次のパケットを待つ
            break;
    }
}