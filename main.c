#include <stdio.h>
#include <string.h>

#include "comment_removal.h"
#include "file_inclusion.h"
#include "macro_handler.h"

int main(int argc, char *argv[])
{
    FILE *fp;
    FILE *temp1;
    FILE *temp2;
    FILE *fout;

    char output[256];
    char *dot;

    if(argc != 2)
    {
        printf("Usage: ./mypreprocessor inputfile.c\n");
        return 1;
    }

    fp = fopen(argv[1], "r");

    if(fp == NULL)
    {
        printf("Unable to open input file\n");
        return 1;
    }

    if(strlen(argv[1]) > sizeof(output) - 4)
    {
        printf("Filename is too long\n");
        fclose(fp);
        return 1;
    }

    strcpy(output, argv[1]);

    dot = strrchr(output, '.');

    if(dot != NULL)
        strcpy(dot, ".i");
    else
        strcat(output, ".i");

    fout = fopen(output, "w");

    if(fout == NULL)
    {
        printf("Unable to create output file\n");
        fclose(fp);
        return 1;
    }

    temp1 = fopen("temp1.txt", "w");

    if(temp1 == NULL)
    {
        printf("Unable to create temporary file\n");
        fclose(fp);
        fclose(fout);
        return 1;
    }

    remove_comments(fp, temp1);

    fclose(fp);
    fclose(temp1);

    temp1 = fopen("temp1.txt", "r");
    temp2 = fopen("temp2.txt", "w");

    if(temp1 == NULL || temp2 == NULL)
    {
        printf("Unable to open temporary files\n");

        if(temp1 != NULL)
            fclose(temp1);

        if(temp2 != NULL)
            fclose(temp2);

        fclose(fout);
        remove("temp1.txt");
        remove("temp2.txt");
        return 1;
    }

    file_inclusion(temp1, temp2);

    fclose(temp1);
    fclose(temp2);

    temp2 = fopen("temp2.txt", "r");

    if(temp2 == NULL)
    {
        printf("Unable to open temporary file\n");
        fclose(fout);
        remove("temp1.txt");
        remove("temp2.txt");
        return 1;
    }

    macro_handler(temp2, fout);

    fclose(temp2);
    fclose(fout);

    remove("temp1.txt");
    remove("temp2.txt");

    return 0;
}
