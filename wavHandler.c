#include "./headers/wavHandler.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeHeader(struct wav_header *headerData, FILE *dest, char *filepath) {
  uint8_t header_sz = 44;
  void *hbuf = calloc(header_sz, sizeof(byte));
  if (hbuf == NULL) {
    printf("ERROR: memory allocation failed\n");
    exit(1);
  }
  memcpy(hbuf, headerData, header_sz);
  size_t n = fwrite(hbuf, header_sz, 1, dest);
  if (n == 0) {
    printf("ERROR: no data has been written to %s\n", filepath);
    exit(1);
  }
  free(hbuf);
}
