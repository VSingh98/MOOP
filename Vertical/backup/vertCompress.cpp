/*
 * FileName: vertCompress.cpp
 * Author: Vansh
 * Date: 2/18/16
 * Purpose: Enact a vertical compression
 */

#include <iostream>
#include <fstream>
#include <string>

typedef unsigned char uint_8;

const int WIDTH = 640;
const int HEIGHT = 480;

#define SUBSAMP_RATIO 1/4
#define COMPRESSION_FACTOR 8

#define Y_BUFSIZ (WIDTH*HEIGHT/COMPRESSION_FACTOR)
#define U_BUFSIZ (WIDTH*HEIGHT/COMPRESSION_FACTOR*SUBSAMP_RATIO)
#define V_BUFSIZ (WIDTH*HEIGHT/COMPRESSION_FACTOR*SUBSAMP_RATIO)

const uint_8 BLACK = 0;
const uint_8 WHITE = 255;

#define S_NEWLINE "\n"
#define C_NEWLINE '\n'

#define C_BLANKSPACE ' '


using namespace std;

int main(int argc, char** argv) {
    ifstream inputFile (argv[1], ios::in);
    ofstream debugStream("debug/vert.txt", ios::out | ios::trunc);
    ofstream outputFile ("yuv/output.yuv", ios::out | ios::binary | ios::trunc);


    /* chroma is zero for this particular assignment */
    uint_8 u[U_BUFSIZ] = {0};
    uint_8 v[V_BUFSIZ] = {0};

    string line;
    int y_itr;  /* iterate through line from file input */

    int u_itr;  /* iterate through U chroma array */
    int v_itr;  /* iterate through V chroma array */
    
    int frame = -1;  /* to y_itr the frame indeces  we go through; */
    int lineNumber; /* which line */

    bool isZero;    /* this will be used to designate a color value for every
                       block of COMPRESSION_FACTOR  pixels. If there is a one 
                       in a row of pixels, it will default to the color BLACK.
                       Otherwise, it will default to WHITE. */

    int rowCount;   /* this will be used to count the number of lines we write 
                       to the yuv file. This is for debug purposes and its value
                       will be printed to debugStream */

    int columnCount; /*this will be used to count the number of lines we write 
                       to the yuv file. This is for debug purposes and its value
                       will be printed to debugStream */

    string * readBuffer = new string [COMPRESSION_FACTOR];

    lineNumber = 0;
    rowCount = 0;
    columnCount = 0;

    while (getline(inputFile, readBuffer[lineNumber])) {
        
        line = readBuffer[lineNumber];

        if (line.size() == 0 || line == S_NEWLINE) /* we start on a new frame */
            continue; 
        
        if (isalpha(line[0])) {     /* This is a frame title */
            
            rowCount = 0;

        	if (++frame) {  /* if frame is not zero, write u and v to
                               outputFile. otherwise, write y first */
                for(u_itr = 0; u_itr < U_BUFSIZ; u_itr++) {
                    outputFile.write( reinterpret_cast<const char*> (&u[u_itr]),
                            sizeof(uint_8));
                }

                for(v_itr = 0; v_itr < V_BUFSIZ; v_itr++) {
                    outputFile.write( reinterpret_cast<const char*> (&v[v_itr]),
                            sizeof(uint_8));
                }

            }
		
            continue;   /*continue to start reading lines of data */
        }

        isZero = true;


        rowCount ++;
        if(++ lineNumber == COMPRESSION_FACTOR) {
            for(int count = 0; count < line.length(); count ++, isZero = true) {
                                
                if (line[count] == C_BLANKSPACE)
                    continue;

                if (line[count] == C_NEWLINE) 
                    continue;
                
                for(y_itr = 0; y_itr < COMPRESSION_FACTOR; y_itr ++) {

                    if(readBuffer[y_itr][count] == '1') {
                        isZero = false;
                        break;
                    }
                }

                if(! isZero || y_itr == COMPRESSION_FACTOR) {
                    outputFile.write( reinterpret_cast<const char*> 
                            (isZero ? &BLACK : &WHITE), sizeof(uint_8));
                    columnCount ++;
                    lineNumber = 0;
                }
                
                debugStream << "frame " << frame << " column: " << columnCount
                            << " row: " << rowCount << endl;

            } /* end for */
            debugStream << "got here" << endl;
        } /* end if */
        
        columnCount = 0;
    } /* end while */

    debugStream << "got to end" << endl;

    /* this adds the u and v for the last frame read */
    for(u_itr = 0; u_itr < U_BUFSIZ; u_itr++) {
        outputFile.write( reinterpret_cast<const char*> (&u[u_itr]),
                sizeof(uint_8));
    }

    for(v_itr = 0; v_itr < V_BUFSIZ; v_itr++) {
        outputFile.write( reinterpret_cast<const char*> (&v[v_itr]),
                sizeof(uint_8));
    }

    outputFile.close();
    debugStream.close();
    inputFile.close();
    return 0;
}
