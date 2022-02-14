#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;

static const byte ChunkID[4] = {'R', 'I', 'F', 'F'};
static const byte Format[4] = {'W', 'A', 'V', 'E'};
static const byte Subchunk1ID[4] = {'f', 'm', 't', 0};
static const uint32_t Subchunk1Size = 16;
static const uint16_t AudioFormat = 1;
static const uint16_t NumChannels = 1;
static const uint32_t SampleRate = 44100;
static const uint32_t ByteRate = 88200;
static const uint16_t BlockAlign = 2;
static const uint16_t BitsPerSample = 16;
static const byte Subchunk2ID[4] = {'d', 'a', 't', 'a'};

typedef struct {
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
  // DATA
} wav_header;

int main(int argc, char **argv) {
  wav_header a = {.ChunkID[0] = ChunkID[0],
                  .ChunkID[1] = ChunkID[1],
                  .ChunkID[2] = ChunkID[2],
                  .ChunkID[3] = ChunkID[3],
                  .ChunkSize = sizeof(a) - 8,
                  .Format[0] = Format[0],
                  .Format[1] = Format[1],
                  .Format[2] = Format[2],
                  .Format[3] = Format[3],
                  .Subchunk1ID[0] = Subchunk1ID[0],
                  .Subchunk1ID[1] = Subchunk1ID[1],
                  .Subchunk1ID[2] = Subchunk1ID[2],
                  .Subchunk1ID[3] = Subchunk1ID[3],
                  .Subchunk1Size = Subchunk1Size,
                  .AudioFormat = AudioFormat,
                  .NumChannels = NumChannels,
                  .SampleRate = SampleRate,
                  .ByteRate = ByteRate,
                  .BlockAlign = BlockAlign,
                  .BitsPerSample = BitsPerSample,
                  .Subchunk2ID[0] = Subchunk2ID[0],
                  .Subchunk2ID[1] = Subchunk2ID[1],
                  .Subchunk2ID[2] = Subchunk2ID[2],
                  .Subchunk2ID[3] = Subchunk2ID[3],
                  .Subchunk2Size = 0};
  char *program = *argv++;
  char *filepath = *argv++;
  FILE *file = fopen(filepath, "wb");
  printf("hello wav\n");
  void *hbuf = malloc(44);
  memcpy(hbuf, &a, 44);
  // void *memcpy(void *restrict dest, const void *restrict src, size_t n);
  size_t n = fwrite(hbuf, 44, 1, file);

  fclose(file);
  return 0;
}
