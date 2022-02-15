#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t byte; // 8 bit = 1 byte

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

static void sizeCheck(struct wav_header a) {
  printf("wav header: %u bytes\t\texpected: 44\n", sizeof(a));
  printf("chunkid size: %u bytes\t\texpected: 4\toffset: %u\texpected: 0\n",
         sizeof(a.ChunkID), offsetof(struct wav_header, ChunkID));
  printf("chunk size: %u bytes\t\texpected: 4\toffset: %u\texpected: 4\n",
         sizeof(a.ChunkSize), offsetof(struct wav_header, ChunkSize));
  printf("format size: %u bytes\t\texpected: 4\toffset: %u\texpected: 8\n",
         sizeof(a.Format), offsetof(struct wav_header, Format));
  printf(
      "Subchunk1ID size: %u bytes\t\texpected: 4\toffset: %u\texpected: 12\n",
      sizeof(a.Subchunk1ID), offsetof(struct wav_header, Subchunk1ID));
  printf(
      "Subchunk1Size size: %u bytes\t\texpected: 4\toffset: %u\texpected: 16\n",
      sizeof(a.Subchunk1Size), offsetof(struct wav_header, Subchunk1Size));
  printf(
      "AudioFormat size: %u bytes\t\texpected: 2\toffset: %u\texpected: 20\n",
      sizeof(a.AudioFormat), offsetof(struct wav_header, AudioFormat));
  printf(
      "NumChannels size: %u bytes\t\texpected: 2\toffset: %u\texpected: 22\n",
      sizeof(a.NumChannels), offsetof(struct wav_header, NumChannels));
  printf("SampleRate size: %u bytes\t\texpected: 4\toffset: %u\texpected: 24\n",
         sizeof(a.SampleRate), offsetof(struct wav_header, SampleRate));
  printf("ByteRate size: %u bytes\t\texpected: 4\toffset: %u\texpected: 28\n",
         sizeof(a.ByteRate), offsetof(struct wav_header, ByteRate));
  printf("BlockAlign size: %u bytes\t\texpected: 2\toffset: %u\texpected: 32\n",
         sizeof(a.BlockAlign), offsetof(struct wav_header, BlockAlign));
  printf(
      "BitsPerSample size: %u bytes\t\texpected: 2\toffset: %u\texpected: 34\n",
      sizeof(a.BitsPerSample), offsetof(struct wav_header, BitsPerSample));
  printf(
      "Subchunk2ID size: %u bytes\t\texpected: 4\toffset: %u\texpected: 36\n",
      sizeof(a.Subchunk2ID), offsetof(struct wav_header, Subchunk2ID));
  printf(
      "Subchunk2Size size: %u bytes\t\texpected: 4\toffset: %u\texpected: 40\n",
      sizeof(a.Subchunk2Size), offsetof(struct wav_header, Subchunk2Size));
}

int main(int argc, char **argv) {
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
  // sizeCheck(a);
  int16_t i = 1;
  while (i >= 1) {
    ++i;
  }
  printf("max int16_t: %d\n", i);
  char *program = *argv++;
  char *filepath = *argv++;
  FILE *file = fopen(filepath, "wb");
  if (file == NULL) {
    printf("ERROR: could not open file %s: %s\n", filepath, strerror(errno));
    exit(1);
  }
  void *hbuf = calloc(44, sizeof(byte));
  if (hbuf == NULL) {
    printf("ERROR: memory allocation failed\n");
    exit(1);
  }
  memcpy(hbuf, &a, 44);
  // void *memcpy(void *restrict dest, const void *restrict src, size_t n);
  size_t n = fwrite(hbuf, 44, 1, file);
  if (n == 0) {
    printf("ERROR: no data has been written to %s\n", filepath);
    exit(1);
  }
  free(hbuf);
  fclose(file);
  return 0;
}
