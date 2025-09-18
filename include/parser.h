#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>
#include <stdio.h>

uint8_t* read_file_to_buffer(const char* filepath, long* file_size);
uint16_t read_u16_be(const uint8_t* buffer);
void print_packet_body(const uint8_t* body_ptr, uint16_t length);

#endif // PARSER_H