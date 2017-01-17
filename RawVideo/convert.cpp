/*
 * FileName: convert.cpp
 * Author: Vansh
 * Date: 2/8/16
 */

#include <iostream>
#include <fstream>
#include <string>

typedef unsigned char uint_8;

const int WIDTH = 640;
const int HEIGHT = 480;

#define SUBSAMP_RATIO 1/4

#define Y_BUFSIZ (WIDTH*HEIGHT)
#define U_BUFSIZ (WIDTH*HEIGHT*SUBSAMP_RATIO)
#define V_BUFSIZ (WIDTH*HEIGHT*SUBSAMP_RATIO)

const uint_8 BLACK = 0;
const uint_8 WHITE = 255;

#define S_NEWLINE "\n"
#define C_NEWLINE '\n'

#define C_BLANKSPACE ' '


using namespace std;

int main(int argc, char** argv) {
	ifstream inputFile (argv[1], ios::in);
	ofstream outputFile ("yuv/output.yuv", ios::out | ios::binary | ios::trunc);


	/* chroma is zero for this particular assignment */
	uint_8 u[U_BUFSIZ] = {0};
	uint_8 v[V_BUFSIZ] = {0};

	string line;
	int y_itr;	/* iterate through line from file input */

	int u_itr;	/* iterate through U chroma array */
	int v_itr;	/* iterate through V chroma array */
    
    int frame = -1;  /* to count the frame indeces  we go through; */
    int lineNumber; /* which line */

	while (getline(inputFile, line)) {
	
		if (line.size() == 0 || line == S_NEWLINE) /* we start on a new frame */
			continue; 
		
		if (isalpha(line[0])) { 	/* This is a frame title */
            lineNumber = 0;

			frame++;
            if (frame) {
                for(u_itr = 0; u_itr < U_BUFSIZ; u_itr++) {
                    outputFile.write( reinterpret_cast<const char*> (&u[u_itr]),
                            sizeof(uint_8));
                }

                for(v_itr = 0; v_itr < V_BUFSIZ; v_itr++) {
                    outputFile.write( reinterpret_cast<const char*> (&v[v_itr]),
                            sizeof(uint_8));
                }

            }

            continue;
		}

		for(y_itr = 0; y_itr < line.length(); y_itr++) {
            if (line[y_itr] == C_BLANKSPACE)
                continue;

            if (line[y_itr] == C_NEWLINE) 
                continue;

			outputFile.write( reinterpret_cast<const char*> 
                    (line[y_itr]=='0' ? &BLACK : &WHITE), sizeof(uint_8));
		}

	}

	outputFile.close();
	inputFile.close();
	return 0;
}
