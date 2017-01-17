SHELL := /bin/bash

# make:           creates the convert.o file
# make clean:     cleans the directory
# make new:       cleans directory and then creates convert.o file
# make run:       run ffmpeg tool to create out.mp4 file

all: 
	make -C	RawVideo/ all
	make -C Horizontal/ all
	make -C Vertical/ all

directories:
	make -C RawVideo/ directories
	make -C Horizontal/ directories
	make -C Vertical/ directories

clean:
	make -C	RawVideo/ clean
	make -C Horizontal/ clean
	make -C Vertical/ clean

new:
	make clean
	make all
