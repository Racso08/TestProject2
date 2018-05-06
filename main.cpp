/* fread example: read an entire file */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>         // std::string
using namespace std;

int main () {
    FILE * pFile;
    long lSize;
    char * buffer;
    size_t result;

    pFile = fopen ( "/home/racso/Project#2/Bella.mp3" , "rb" );
    if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);

    // allocate memory to contain the whole file:
    buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

    // copy the file into the buffer:
    //result = fread (buffer,1,lSize,pFile);
    //if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

    result = fread (buffer,1,200,pFile);//read 200 bytes to test only

    //For loop added by me
    for( unsigned i = 0; i <= result; ++i ) {
        printf("%x",buffer[i]);
    }
    /* the whole file is now loaded in the memory buffer. */
    // terminate
    fclose (pFile);
    free (buffer);
    return 0;
}