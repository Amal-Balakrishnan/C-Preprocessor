#include <stdio.h>
#include "comment_removal.h"

void remove_comments(FILE *fp, FILE *fout)
{
    int ch, next, prev;

    while((ch = fgetc(fp)) != EOF)
    {
        if(ch == '/')
        {
            next = fgetc(fp);

            // Single-line comment
            if(next == '/')
            {
                while((ch = fgetc(fp)) != '\n' && ch != EOF)
                {
                }

                if(ch == '\n')
                    fputc('\n', fout);
            }

            // Multi-line comment
            else if(next == '*')
            {
                prev = 0;

                while((ch = fgetc(fp)) != EOF)
                {
                    if(prev == '*' && ch == '/')
                        break;

                    if(ch == '\n')
                        fputc('\n', fout);

                    prev = ch;
                }
            }
            else
            {
                fputc(ch, fout);

                if(next != EOF)
                    ungetc(next, fp);
            }
        }
        else
        {
            fputc(ch, fout);
        }
    }
}
