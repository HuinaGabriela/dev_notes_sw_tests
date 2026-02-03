#include <assert.h>
#include "../data/buffer.h"

void test_buffer_packet() {
    uint8_t out[4];

    buffer_push(0xAA);
    buffer_push(0x01);
    buffer_push(0x10);
    buffer_push(0xBB);

    assert(buffer_pop_packet(out) == 4);
}
