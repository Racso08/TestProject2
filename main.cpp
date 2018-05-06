// Chunks a file by breaking it up into chunks of "chunkSize" bytes.

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <limits.h>


using namespace std;

inline void swap(char *x, char *y) {
    char t = *x; *x = *y; *y = t;
}

char* reverse(char *buffer, int i, int j)
{
    while (i < j)
        swap(&buffer[i++], &buffer[j--]);

    return buffer;
}

char* itoa(int value, char* buffer, int base)
{
    // invalid input
    if (base < 2 || base > 32)
        return buffer;

    // consider absolute value of number
    int n = abs(value);

    int i = 0;
    while (n)
    {
        int r = n % base;

        if (r >= 10)
            buffer[i++] = 65 + (r - 10);
        else
            buffer[i++] = 48 + r;

        n = n / base;
    }

    // if number is 0
    if (i == 0)
        buffer[i++] = '0';

    // If base is 10 and value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base == 10)
        buffer[i++] = '-';

    buffer[i] = '\0'; // null terminate string

    // reverse the string and return it
    return reverse(buffer, 0, i - 1);
}
void chunkFile(char *fullFilePath, char *chunkName, unsigned long chunkSize) {
    ifstream fileStream;
    fileStream.open(fullFilePath, ios::in | ios::binary);

    // File open a success
    if (fileStream.is_open()) {
        ofstream output;
        int counter = 1;

        string fullChunkName;

        // Create a buffer to hold each chunk
        char *buffer = new char[chunkSize];

        // Keep reading until end of file
        while (!fileStream.eof()) {

            // Build the chunk file name. Usually drive:\\chunkName.ext.N
            // N represents the Nth chunk
            fullChunkName.clear();
            fullChunkName.append(chunkName);
            fullChunkName.append(".");

            // Convert counter integer into string and append to name.
            char intBuf[10];
            itoa(counter,intBuf,10);
            fullChunkName.append(intBuf);

            // Open new chunk file name for output
            output.open(fullChunkName.c_str(),ios::out | ios::trunc | ios::binary);

            // If chunk file opened successfully, read from input and
            // write to output chunk. Then close.
            if (output.is_open()) {
                fileStream.read(buffer,chunkSize);
                // gcount() returns number of bytes read from stream.
                output.write(buffer,fileStream.gcount());
                output.close();

                counter++;
            }
        }

        // Cleanup buffer
        delete(buffer);

        // Close input file stream.
        fileStream.close();
        cout << "Chunking complete! " << counter - 1 << " files created." << endl;
    }
    else { cout << "Error opening file!" << endl; }
}

int main(){
    chunkFile("/home/racso/Project#2/Bella.mp3","Chunk",2012);
    return 0;
}