#include <stdio.h>
#include <iostream>

using namespace std;

typedef unsigned char BYTE;

long getFileSize(FILE *file)
{
    long lCurPos, lEndPos;
    lCurPos = ftell(file);
    fseek(file, 0, 2);
    lEndPos = ftell(file);
    fseek(file, lCurPos, 0);
    return lEndPos;
}

int main()
{
    const char *filePath = "/home/racso/Project#2/.mp3";
    BYTE *fileBuf;
    FILE *file = NULL;

    if ((file = fopen(filePath, "rb")) == NULL)
        cout << "Could not open specified file" << endl;
    else
        cout << "File opened successfully" << endl;

    long fileSize = getFileSize(file);

    fileBuf = new BYTE[fileSize];

    //char *array = (char *)malloc(fileSize + 1);

    fread(fileBuf , fileSize, 1, file);

    for (int i = 0; i < 4096; i++)
        printf("%X ", fileBuf[i]);

    //cin.get();
    delete[]fileBuf;
    fclose(file);

    return 0;
}
