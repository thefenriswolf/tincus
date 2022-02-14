#!/bin/bash

CC="clang"
LD="-fuse-ld=lld"
SRC="*.c"
CFLAGS="-Wall -Wextra -Wshadow -Weverything -pedantic -std=c18 -g -O3"
LDFLAGS=""
INFER="../plotplot/tools/infer-linux64-v1.1.0/bin/infer"

function build_help() {
    echo -e "
  █████     ███                                        
 ░░███     ░░░                                         
 ███████   ████  ████████    ██████  █████ ████  █████ 
░░░███░   ░░███ ░░███░░███  ███░░███░░███ ░███  ███░░  
  ░███     ░███  ░███ ░███ ░███ ░░░  ░███ ░███ ░░█████ 
  ░███ ███ ░███  ░███ ░███ ░███  ███ ░███ ░███  ░░░░███
  ░░█████  █████ ████ █████░░██████  ░░████████ ██████ 
   ░░░░░  ░░░░░ ░░░░ ░░░░░  ░░░░░░    ░░░░░░░░ ░░░░░░  
                                                       
                                                       
                                                       
"
    echo -e "Usage:\n \t build.sh [command]\n"
    echo -e "Available commands:\n"
    echo -e "build: build | c | com | compile\n"
    echo -e "clean: clean\n"
    echo -e "tidy: tidy | t\n"
    echo -e "analyze: analyze | lint | a | l\n"
}

function build_clean(){
    set -xe
    rm -rfv *.o a.out tincus *~ infer-out
}

function build_tidy(){
    set -xe
    clang-tidy *.c *.h
}

function build_analyze(){
    set -xe
    $INFER run --reactive --continue -- clang $SRC
}

function build_compile(){
    set -xe
    $CC $CFLAGS $LD $LDFLAGS -o tincus $SRC
}

function build_play(){
    ffplay /resources/sample.wav
}
case $1 in
    clean)
        build_clean
        ;;
    tidy | t)
        build_tidy
        ;;
    analyze | lint | a | l)
        build_analyze
        ;;
    com | compile | c | build)
       build_compile
       ;;
    *)
        clear
        build_help
        ;;
esac


