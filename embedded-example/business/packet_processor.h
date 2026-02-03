#ifndef PACKET_PROCESSOR_H
#define PACKET_PROCESSOR_H

#include <stdint.h>
#include <stdbool.h>

bool process_packet(uint8_t *data, uint8_t len);

#endif
