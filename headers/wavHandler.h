#pragma once
#include <stdint.h>
#include <stdio.h>

typedef uint8_t byte; // 8 bit = 1 byte

struct wav_header {
  byte ChunkID[4] __attribute__((aligned(1)));
  uint32_t ChunkSize __attribute__((
      aligned(1))); // size of the entire file in bytes minus 8 bytes
  byte Format[4] __attribute__((aligned(1)));
  byte Subchunk1ID[4] __attribute__((aligned(1)));
  uint32_t Subchunk1Size __attribute__((aligned(1)));
  uint16_t AudioFormat __attribute__((aligned(1)));
  uint16_t NumChannels __attribute__((aligned(1)));
  uint32_t SampleRate __attribute__((aligned(1)));
  uint32_t ByteRate __attribute__((
      aligned(1))); // (Sample Rate * BitsPerSample * Channels) / 8
  uint16_t BlockAlign
      __attribute__((aligned(1))); // (NumChannels * BitsPerSample) / 8
  uint16_t BitsPerSample __attribute__((aligned(1)));
  byte Subchunk2ID[4] __attribute__((aligned(1)));
  uint32_t Subchunk2Size __attribute__((
      aligned(1))); // (NumSamples * NumChannels * BitsPerSample)/8
  // int16_t DATA
};

void writeHeader(struct wav_header *headerData, FILE *dest, char *filepath);
