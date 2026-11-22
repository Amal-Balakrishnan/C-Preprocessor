#include <stdio.h>
#include <string.h>
#include "file_inclusion.h"

void copy_file(FILE *src, FILE *dest)
{
    int ch;

    while((ch = fgetc(src)) != EOF)
    {
        fputc(ch, dest);
    }
}

void file_inclusion(FILE *fp, FILE *fout)
{
    char line[256];
    char filename[100];
    char *start, *end;
    char open_char, close_char;

    FILE *header;
    int i;

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        if(strstr(line, "#include") != NULL)
        {
            start = strchr(line, '<');

            open_char = '<';
            close_char = '>';

            if(start == NULL)
            {
                start = strchr(line, '"');

                open_char = '"';
                close_char = '"';
            }

            if(start != NULL)
            {
                start++;
                end = strchr(start, close_char);

                if(end != NULL)
                {
                    i = 0;

                    while(start < end && i < 99)
                    {
                        filename[i] = *start;
                        i++;
                        start++;
                    }

                    filename[i] = '\0';

                    header = fopen(filename, "r");

                    if(header != NULL)
                    {
                        copy_file(header, fout);
                        fclose(header);
                    }
                    else
                    {
                        /* Keep system header for GCC */
                        fputs(line, fout);
                    }
                }
                else
                {
                    fputs(line, fout);
                }
            }
            else
            {
                fputs(line, fout);
            }
        }
        else
        {
            fputs(line, fout);
        }
    }
}
