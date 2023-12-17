
all: build

build:
	gcc -g -DLSB_FIRST primo.c -o primo $(shell pkg-config sdl2 --cflags) $(shell pkg-config sdl2 --libs)

run-original:
	dosbox-x -fastlaunch -exit -conf ../original/dosbox-x.conf ../original/OS-PRIMO/os-primo.exe

run-ultimo:
	wine ~/Applications/Primo/Ultimo.exe
