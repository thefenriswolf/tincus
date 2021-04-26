package main

import (
	"encoding/binary"
	"fmt"
	"math"
	"os"
)

func WriteSoundfile(payload []float64) {
	file, err := os.Create("sound.bin")
	if err != nil {
		fmt.Errorf("could not create file %v", err)
	}
	defer file.Close()

	err = binary.Write(file, binary.LittleEndian, payload)
	if err != nil {
		fmt.Errorf("could not write to file %v", err)
	}
}

func BaseWaveGenerator(lengh int) []int {
	peak := lengh / 2
	var baseWave []int
	for i := 1; i <= peak; i++ {
		baseWave = append(baseWave, i)
	}
	for i := peak; i >= 1; i-- {
		baseWave = append(baseWave, i)
	}
	return baseWave
}

func SineWaveGenerator(baseWave []int) []float64 {
	var sineWave []float64
	for i := 0; i < len(baseWave); i++ {
		sineWave = append(sineWave, math.Sin(float64(baseWave[i])))
	}
	return sineWave
}
