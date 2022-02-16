#!/bin/bash

CC="clang"
LD="-fuse-ld=lld"
SRC="main.c debug.c wavHandler.c"
HEADERS="./headers/*.h"
CFLAGS="-W -Wall -Wextra -pedantic -std=c18 -g3 -O2"
EXTRAFLAGS="-Wshadow -Wdouble-promotion -Wconversion -Wpadded"
CLANGFLAGS="-Wdocumentation"
LDFLAGS="-lm"
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
    rm -rfv *.o *.out tincus *~ infer-out
}

function build_tidy(){
    set -xe
    clang-tidy $SRC $HEADERS
}

function build_analyze(){
    set -xe
    $INFER run --reactive --continue -- clang $LDFLAGS $SRC -o inf.out
}

function build_compile(){
    set -xe
    $CC $CFLAGS $CLANGFLAGS $EXTRAFLAGS $LD $LDFLAGS -o tincus $SRC
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


