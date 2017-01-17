SHELL := /bin/bash

all: mp4

clean:
	rm -rf bin/* yuv/* vid/* debug/*

mp4: output.yuv
	@ffmpeg -f rawvideo -s 640x480 -pix_fmt yuv420p -r 24 -i yuv/output.yuv \
		-vcodec libx264 -qp 0 vid/out.mp4

output.yuv: compile 
	bin/convert.o ../Data/rawvideo.txt

compile: convert.cpp
	g++ -o bin/convert.o convert.cpp
	cp convert.cpp backup

new:
	make clean
	make all

directories:
	@mkdir backup bin vid yuv debug
