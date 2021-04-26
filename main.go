package main

//TODO: combine writeSoundfile & baseWaveGenerator into one function
//TODO: implement Benchmarks and tests

func main() {
	//step := 0.05
	//volume := 0.5

	baseWave := BaseWaveGenerator(48000) //48000
	//fmt.Println(baseWave)
	sineWave := SineWaveGenerator(baseWave)
	//fmt.Println(sineWave)
	WriteSoundfile(sineWave)

}
