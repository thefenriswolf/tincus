package main

import "testing"

func BenchmarkBaseWaveGenerator(b *testing.B) {
	for i := 0; i < b.N; i++ {
		BaseWaveGenerator(48000)
	}
}

func BenchmarkSineWaveGenerator(b *testing.B) {
	wav := BaseWaveGenerator(48000)
	for i := 0; i < b.N; i++ {
		SineWaveGenerator(wav)
	}
}
