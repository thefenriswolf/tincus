#pragma once
#include <stdint.h>
#include <stdio.h>

typedef uint8_t byte; // 8 bit = 1 byte

#pragma pack(push, 1)
struct wav_header {
  // in case I fucked up:  __attribute__((aligned(1)))
  byte ChunkID[4];
  uint32_t ChunkSize; // size of the entire file in bytes minus 8 bytes
  byte Format[4];
  byte Subchunk1ID[4];
  uint32_t Subchunk1Size;
  uint16_t AudioFormat;
  uint16_t NumChannels;
  uint32_t SampleRate;
  uint32_t ByteRate;   // (Sample Rate * BitsPerSample * Channels) / 8
  uint16_t BlockAlign; // (NumChannels * BitsPerSample) / 8
  uint16_t BitsPerSample;
  byte Subchunk2ID[4];
  uint32_t Subchunk2Size; // (NumSamples * NumChannels * BitsPerSample)/8
  // int16_t DATA
};
#pragma pack(pop)

void writeHeader(struct wav_header *headerData, FILE *dest, char *filepath);
