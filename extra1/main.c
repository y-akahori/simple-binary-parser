#include "streaming_parser.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "使用法: %s <入力ファイルパス>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "rb");
    if (!file) {
        perror("ファイルを開けませんでした");
        return 1;
    }
    
    Parser my_parser;
    parser_init(&my_parser); // パーサーを初期化

    // ファイルから1バイトずつ読み込み、パーサーに渡す
    int byte;
    while ((byte = fgetc(file)) != EOF) {
        parser_process_byte(&my_parser, (uint8_t)byte);
    }

    fclose(file);
    return 0;
}