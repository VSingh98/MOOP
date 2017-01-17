SHELL := /bin/bash

all: mp4

clean:
	rm -rf bin/* yuv/* vid/* debug/*   

mp4: compressedOutput binASCII
	@ffmpeg -f rawvideo -s 80x480 -pix_fmt yuv420p -r 24 -i yuv/output.yuv \
		-vcodec libx264 -qp 0 vid/horz.mp4
	@ffmpeg -f rawvideo -s 80x480 -pix_fmt yuv420p -r 24 -i yuv/binASCII.yuv \
		-vcodec libx264 -qp 0 vid/bin_ascii.mp4
	
compressedOutput: compile1
	bin/horzCompress.o ../Data/rawvideo.txt

binASCII: compile2
	bin/binaryCharPrint.o ../Data/rawvideo.txt


compile1: horzCompress.cpp
	g++ -o bin/horzCompress.o horzCompress.cpp
	cp horzCompress.cpp backup

compile2: binaryCharPrint.cpp	
	g++ -o bin/binaryCharPrint.o binaryCharPrint.cpp
	cp binaryCharPrint.cpp backup

new:
	make clean
	make all

directories:
	@mkdir backup bin vid yuv debug 

qp: 
