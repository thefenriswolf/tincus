#include "./headers/debug.h"
#include "./headers/wavHandler.h"
#include <errno.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const byte ChunkID[4] = {'R', 'I', 'F', 'F'};
static const byte Format[4] = {'W', 'A', 'V', 'E'};
static const byte Subchunk1ID[4] = {'f', 'm', 't', ' '};
static const uint32_t Subchunk1Size = 16;
static const uint16_t AudioFormat = 1;
static const uint16_t NumChannels = 1;
static const uint32_t SampleRate = 44100;
static const uint32_t ByteRate = 88200;
static const uint16_t BlockAlign = 2;
static const uint16_t BitsPerSample = 16;
// each sample is 16bit/2byte wide, but has to be signed!!!
static const byte Subchunk2ID[4] = {'d', 'a', 't', 'a'};
static uint16_t NumSamples = 1;

static const long double PI = 3.1415926535897;

void usage(FILE *file, char *program) {
  fprintf(file, "Usage: %s <output.wav>\n", program);
}

int main(int argc, char **argv) {
  (void)argc;
  char *program = *argv++;
  char *filepath = *argv++;
  if (filepath == NULL) {
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
                         .Subchunk2Size =
                             NumSamples * NumChannels * BitsPerSample /
                             8}; // size of the audio data in bytes
                                 // (n-Samples*NumChannels*BitsPerSample/8)

  // sizeCheck(a);

  uint32_t Duration = 1000;
  long double amp = 300.0;
  long double Freq = 440.0;
  long double constant = 2.0 * PI * Freq;
  // int16_t sineWave[SampleRate * Duration];
  int16_t *sineWave = calloc(2 * SampleRate * Duration, sizeof(int16_t));
  if (sineWave == NULL) {
    printf("Error: could not allocate %d bytes for data chunk\n",
           sizeof(int16_t) * (SampleRate * Duration));
    exit(1);
  }

  printf("double: %d\nlong long double: %d\n", sizeof(double),
         sizeof(long double));
  printf("exp: %d\n", (SampleRate * Duration));
  // printf("%d %d\n", sineWave[0], (sizeof(sineWave) / sizeof(sineWave[0])));
  // TODO: this takes forever
  // TODO: too little amplitude
  // TODO: numbers too close together
  for (size_t i = 0; i <= (SampleRate * Duration); i++) {
    int16_t commit = 0;
    long double temp = 0.0;
    // 2PI = 0°
    // completes 1 cycle in N number of samples (SampleRate)
    // Amplification*sin(2*PI*Frequency*iterator/N)
    temp = amp * sinl(constant * ((long double)i) / ((long double)SampleRate));
    // printf("tmp: %f\n", temp);
    commit = (int16_t)roundl(temp * 32767.0);
    if (commit < -32768) {
      commit = -32767;
    }
    if (commit > 32767) {
      commit = 32767;
    }
    // printf("tmp: %i \n", commit);
    sineWave[i] = commit;
    // printf("%d\n", sineWave[i]);
  }
  for (size_t i = 0; i <= 100; i++) {
    printf("%d\n", sineWave[i]);
  }
  /* int16_t *dataChunk = calloc(SampleRate * Duration, sizeof(int16_t)); */
  /* if (dataChunk == NULL) { */
  /*   printf("Error: could not allocate %d bytes for data chunk\n", */
  /*          sizeof(int16_t) * (SampleRate * Duration)); */
  /*   exit(1); */
  /* } */
  /* for (size_t i = 0; i <= (sizeof(sineWave) / sizeof(sineWave[0])); i++) { */
  /*   dataChunk[i] = sineWave[i]; */
  /*   // printf("%d ", dataChunk[i]); // this segfaults. why??? */
  /* } */

  writeHeader(&a, file, filepath);
  int seekErr = fseek(file, sizeof(a) + 1, SEEK_SET);
  if (seekErr != 0) {
    printf("ERROR: fseek to pos: %d was unsuccessful\n", sizeof(a));
    exit(1);
  }
  // TODO: ptr can be array???
  // size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
  size_t nDataWritten =
      fwrite(sineWave, sizeof(int16_t), (SampleRate * Duration), file);
  if (nDataWritten == 0) {
    printf("ERROR: data chunk could not be written\n");
    exit(1);
  }
  free(sineWave);
  fclose(file);
  return 0;
}
