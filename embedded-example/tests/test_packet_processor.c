#include <assert.h>
#include "../business/packet_processor.h"

uint8_t make_checksum(uint8_t *d) {
    return (d[0] + d[1] + d[2]) % 256;
}

void test_valid_start_motor() {
    uint8_t pkt[4] = {0xAA, 0x01, 0x10, 0};
    pkt[3] = make_checksum(pkt);
    assert(process_packet(pkt, 4) == true);
}

void test_wrong_header() {
    uint8_t pkt[4] = {0x00, 0x01, 0x10, 0x00};
    assert(process_packet(pkt, 4) == false);
}

void test_bad_checksum() {
    uint8_t pkt[4] = {0xAA, 0x01, 0x10, 0xFF};
    assert(process_packet(pkt, 4) == false);
}

void test_short_packet() {
    assert(process_packet(NULL, 0) == false);
}

int main() {
    test_valid_start_motor();
    test_wrong_header();
    test_bad_checksum();
    test_short_packet();
}
