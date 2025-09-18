#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

uint8_t* read_file_to_buffer(const char* filepath, long* file_size) {
    FILE* file = fopen(filepath, "rb");
    if (!file) {
        perror("ファイルを開けませんでした");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    *file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (*file_size <= 0) {
        fclose(file);
        return NULL;
    }

    uint8_t* buffer = (uint8_t*)malloc(*file_size);
    if (!buffer) {
        fprintf(stderr, "メモリ確保に失敗しました\n");
        fclose(file);
        return NULL;
    }

    if (fread(buffer, 1, *file_size, file) != (size_t)*file_size) {
        fprintf(stderr, "ファイルの読み込みに失敗しました\n");
        free(buffer);
        fclose(file);
        return NULL;
    }
    
    fclose(file);
    return buffer;
}

uint16_t read_u16_be(const uint8_t* buffer) {
    return (uint16_t)((buffer[0] << 8) | buffer[1]);
}

void print_packet_body(const uint8_t* body_ptr, uint16_t length) {
    for (uint16_t i = 0; i < length; ++i) {
        printf("0x%02x%s", body_ptr[i], (i == length - 1) ? "" : " ");
    }
    printf("\n");
}