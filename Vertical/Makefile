SHELL := /bin/bash

all: mp4

clean:
	rm -rf bin/* yuv/* vid/* debug/*   

mp4: binASCII compressedOutput 
	@ffmpeg -f rawvideo -s 640x60 -pix_fmt yuv420p -r 24 -i yuv/binASCII.yuv \
		-vcodec libx264 -qp 0 vid/bin_ascii.mp4
	@ffmpeg -f rawvideo -s 640x60 -pix_fmt yuv420p -r 24 -i yuv/output.yuv \
		-vcodec libx264 -qp 0 vid/vert.mp4

compressedOutput: compile1
	bin/vertCompress.o ../Data/rawvideo.txt

binASCII: compile2
	bin/binaryCharPrint.o ../Data/rawvideo.txt

compile1: vertCompress.cpp
	g++ -o bin/vertCompress.o vertCompress.cpp
	cp vertCompress.cpp backup

compile2: binaryCharPrint.cpp
	g++ -o bin/binaryCharPrint.o binaryCharPrint.cpp
	cp binaryCharPrint.cpp backup

new:
	make clean
	make all

directories:
	@mkdir backup bin vid yuv debug
