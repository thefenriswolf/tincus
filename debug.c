#include <stddef.h>
#include <stdio.h>

#include "./headers/debug.h"

void sizeCheck(struct wav_header a) {
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
