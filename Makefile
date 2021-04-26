all:
	go build -o gfm

build:
	go build -o gfm

build-tiny:
	tinygo build -ldflags -fuse-ld=lld -o gfm-tiny

run:
	go run -race main.go

clean:
	rm -v sound.bin *~ gfm gfm-tiny

play:
	ffplay -f f32le -ar 48000 sound.bin

benchmark:
	go test -bench=.

test:
	go test
