#include <stdio.h>
#include <stdlib.h>
#include <iostream>

unsigned char byte;

int main(void) {
    FILE *fin, *fout;
    int val;
    fin = fopen ("/home/racso/Project#2/Dura-REMIX.mp3","rb");
    if (fin == NULL) {
        printf("Error opening input file\n");
        system("pause");
        exit(1);
    }

    fout = fopen ("newtext.txt","wb");

    if (fout == NULL) {
        printf("Error opening output file\n");
        system("pause");
        exit(1);
    }

    printf("Files opened, copying beginning.\n");
    while(1) { //infinant loop
        val = fgetc(fin);

        if (val == EOF)
            break;

        byte = (unsigned char) val;

        std::cout<<byte;

        fputc(byte,fout);
    }

    printf("Copy successful!\n");
    //system("pause");
    return 0;

}
