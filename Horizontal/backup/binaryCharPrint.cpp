/*
 * FileName: binaryCharPrint.cpp
 * Author: Vansh
 * Date: 2/18/16
 * Purpose: Enact a horizontal compression
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

const uint_8 BLACK = 255;
const uint_8 WHITE = 0;

#define S_NEWLINE "\n"
#define C_NEWLINE '\n'

#define C_BLANKSPACE ' '


using namespace std;

uint_8 binary_Values[8] = {128, 64, 32, 16, 8, 4, 2, 1};

int main(int argc, char** argv) {
    ifstream inputFile (argv[1], ios::in);
    ofstream outputFile ("yuv/binASCII.yuv", ios::out | ios::binary | 
            ios::trunc);

    ofstream debugstream ("debug/debug_bin.txt", ios::out | ios::trunc);

    /* chroma is zero for this particular assignment */
    uint_8 u[U_BUFSIZ] = {0};
    uint_8 v[V_BUFSIZ] = {0};

    string line;
    int y_itr;  /* iterate through line from file input */

    int u_itr;  /* iterate through U chroma array */
    int v_itr;  /* iterate through V chroma array */
    
    int frame = -1;  /* to y_itr the frame indeces  we go through; */
    int lineNumber; /* which line */

    uint_8 pixelValue; /* The value of the picture */

    int columnCount; /*this will be used to count the number of lines we write 
                       to the yuv file. This is for debug purposes and its value
                       will be printed to debugStream */

    while (getline(inputFile, line)) {
    
        if (line.size() == 0 || line == S_NEWLINE) /* we start on a new frame */
            continue; 
        
        if (isalpha(line[0])) {     /* This is a frame title */
            
            lineNumber = 0;

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


        lineNumber ++;
        columnCount = 0; /* set columncount to zero before parsing line */

        y_itr = 0;  /* set y_itr to 0. This is used to iterate through each set
                       of eight pixels */

        pixelValue = 0; /* the value of the summation of ten pixels at a time */

        for(int count = 0; count < line.length(); count ++) {

            if (line[count] == C_BLANKSPACE)
                continue;

            if (line[count] == C_NEWLINE) 
                continue;

            if (line[count] == '1') {
               pixelValue += binary_Values[ y_itr ];
            }

            y_itr ++;

            /* if we encounter a nonzero in the set of eight pixels or we
             * iterate through eight pixels, write to outputFile and move to
             * next block of eight pixels in the row */
            if( y_itr == COMPRESSION_FACTOR ) {
            
                outputFile.write( reinterpret_cast<const char*>(&pixelValue),
                        sizeof(uint_8) );
                 
                columnCount ++;
                y_itr = 0;
            
                debugstream << "frame: " << frame << " column: " << columnCount 
                    << " line number: " << lineNumber << endl;

                pixelValue = 0;
            } 
        }

    }

    /* this adds the u and v for the last frame read */
    for(u_itr = 0; u_itr < U_BUFSIZ; u_itr++) {
        outputFile.write( reinterpret_cast<const char*> (&u[u_itr]),
                sizeof(uint_8));
    }

    for(v_itr = 0; v_itr < V_BUFSIZ; v_itr++) {
        outputFile.write( reinterpret_cast<const char*> (&v[v_itr]),
                sizeof(uint_8));
    }

    /* close files*/
    debugstream.close();
    outputFile.close();
    inputFile.close();

    return 0;
}
