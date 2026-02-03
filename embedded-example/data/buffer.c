#include "buffer.h"

static uint8_t buf[64];
static int idx = 0;

void buffer_push(uint8_t byte) {
    if (idx < 64)
        buf[idx++] = byte;
}

int buffer_pop_packet(uint8_t *out) {
    if (idx < 4)
        return 0;

    for (int i = 0; i < 4; i++)
        out[i] = buf[i];

    idx = 0;
    return 4;
}
