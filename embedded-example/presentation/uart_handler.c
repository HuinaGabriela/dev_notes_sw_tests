#include "buffer.h"
#include "packet_processor.h"

void uart_rx_interrupt(uint8_t byte) {
    buffer_push(byte);

    uint8_t pkt[4];
    if (buffer_pop_packet(pkt)) {
        process_packet(pkt, 4);
    }
}
