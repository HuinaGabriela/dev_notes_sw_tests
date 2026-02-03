#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>

void buffer_push(uint8_t byte);
int buffer_pop_packet(uint8_t *out);

#endif
