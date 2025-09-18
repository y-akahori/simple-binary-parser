#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// パケットのルール定義
static const uint16_t STX_MARKER = 0xEB90;
static const uint16_t ETX_MARKER = 0xC579;
static const uint16_t MIN_BODY_LENGTH = 1;
static const uint16_t MAX_BODY_LENGTH = 100;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "使用法: %s <入力ファイルパス>\n", argv[0]);
        return 1;
    }

    long file_size = 0;
    uint8_t* buffer = read_file_to_buffer(argv[1], &file_size);
    if (!buffer) {
        return 1;
    }
    
    // バッファを走査してパケットをパース
    size_t i = 0;
    while (i < file_size) {
        if (i + 1 >= file_size) break;

        if (read_u16_be(&buffer[i]) != STX_MARKER) {
            i++;
            continue;
        }

        size_t min_packet_size = 6;
        if (i + min_packet_size > file_size) {
            i++;
            continue;
        }

        uint16_t body_length = read_u16_be(&buffer[i + 2]);
        if (body_length < MIN_BODY_LENGTH || body_length > MAX_BODY_LENGTH) {
            i++;
            continue;
        }
        
        size_t total_packet_size = 4 + body_length + 2;
        if (i + total_packet_size > file_size) {
            i++;
            continue;
        }

        if (read_u16_be(&buffer[i + 4 + body_length]) != ETX_MARKER) {
            i++;
            continue;
        }

        print_packet_body(&buffer[i + 4], body_length);
        i += total_packet_size;
    }

    free(buffer);

    int number = 5;
    long long result = factorial(number);
    printf("Factorial of %d is: %lld\n", number, result);
    return 0;
}