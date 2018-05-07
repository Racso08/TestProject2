#include <iostream>
#include <fstream>

using namespace std;

void ReadFile(char *name)
{
    FILE *file;
    char *buffer;
    unsigned long fileLen;

    //Open file
    file = fopen(name, "rb");
    if (!file)
    {
        fprintf(stderr, "Unable to open file %s", name);
        return;
    }

    //Get file length
    fseek(file, 0, SEEK_END);
    fileLen=ftell(file);
    fseek(file, 0, SEEK_SET);

    //Allocate memory
    buffer=(char *)malloc(fileLen+1);
    if (!buffer)
    {
        fprintf(stderr, "Memory error!");
        fclose(file);
        return;
    }

    //Read file contents into buffer
    fread(buffer, fileLen, 1, file);
    fclose(file);

    //Do what ever with buffer
    for(int i = 0; i<200; i++){
        printf("%X",buffer[i]);
    }

    free(buffer);
}

int main(){
    cout<<"TEST"<<endl;
    ReadFile("/home/racso/Project#2/Bella.mp3");
    return 0;
}