#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

static inline void println_bin_8(uint8_t byte) {
  printf(BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(byte));
}

static inline void println_bin_32(uint32_t w) {
  printf(BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN "\n",
      BYTE_TO_BINARY(w>>24), BYTE_TO_BINARY(w>>16), BYTE_TO_BINARY(w>>8), BYTE_TO_BINARY(w)
  );
}

#endif