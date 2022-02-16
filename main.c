#include "./headers/debug.h"
#include "./headers/wavHandler.h"
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const byte ChunkID[4] = {'R', 'I', 'F', 'F'};
static const byte Format[4] = {'W', 'A', 'V', 'E'};
static const byte Subchunk1ID[4] = {'f', 'm', 't'};
static const uint32_t Subchunk1Size = 16;
static const uint16_t AudioFormat = 1;
static const uint16_t NumChannels = 1;
static const uint32_t SampleRate = 44100;
static const uint32_t ByteRate = 88200;
static const uint16_t BlockAlign = 2;
static const uint16_t BitsPerSample = 16;
// each sample is 16bit/2byte wide, but has to be signed!!!
static const byte Subchunk2ID[4] = {'d', 'a', 't', 'a'};

void usage(FILE *file, char *program) {
  fprintf(file, "Usage: %s <output.wav>\n", program);
}

int main(int argc, char **argv) {
  (void)argc;
  char *program = *argv++;
  char *filepath = *argv++;
  if (*argv == NULL) {
    usage(stderr, program);
    exit(1);
  }
  FILE *file = fopen(filepath, "wb");
  if (file == NULL) {
    printf("ERROR: could not open file %s: %s\n", filepath, strerror(errno));
    exit(1);
  }
  struct wav_header a = {.ChunkID[0] = ChunkID[0],
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
                         //.Subchunk1ID[3] = Subchunk1ID[3],
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

  sizeCheck(a);
  writeHeader(&a, file, filepath);

  fclose(file);
  return 0;
}
