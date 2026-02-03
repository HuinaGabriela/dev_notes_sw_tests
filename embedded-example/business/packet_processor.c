#include "packet_processor.h"

static uint8_t calc_checksum(uint8_t *data) {
    return (data[0] + data[1] + data[2]) % 256;
}

bool process_packet(uint8_t *data, uint8_t len) {
    if (!data || len < 4)
        return false;

    if (data[0] != 0xAA)
        return false;

    if (calc_checksum(data) != data[3])
        return false;

    switch (data[1]) {
        case 0x01:
            // start motor
            return true;
        case 0x02:
            // stop motor
            return true;
        default:
            return false;
    }
}


