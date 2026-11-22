#include <stdio.h>
#include <string.h>
#include "macro_handler.h"

int is_identifier_char(char ch)
{
    if((ch >= 'A' && ch <= 'Z') ||
       (ch >= 'a' && ch <= 'z') ||
       (ch >= '0' && ch <= '9') ||
       ch == '_')
    {
        return 1;
    }

    return 0;
}

/* Replace parameter with argument */
void replace_parameter(char body[], char parameter[],
                       char argument[], FILE *fout)
{
    int i = 0;
    int len = strlen(parameter);
    int body_len = strlen(body);

    while(i < body_len)
    {
        if(i + len <= body_len &&
           strncmp(&body[i], parameter, len) == 0 &&
           (i == 0 || !is_identifier_char(body[i-1])) &&
           !is_identifier_char(body[i+len]))
        {
            fputs(argument, fout);
            i = i + len;
        }
        else
        {
            fputc(body[i], fout);
            i++;
        }
    }
}

/* Process normal code lines */
void process_line(char line[],
                  char macro_name[][50],
                  char macro_value[][256],
                  char macro_param[][50],
                  int macro_type[],
                  int count,
                  FILE *fout)
{
    int i = 0, j, k, len, found;
    int depth, arg_len;
    char argument[256];

    while(line[i] != '\0')
    {
        found = 0;

        for(j = 0; j < count; j++)
        {
            len = strlen(macro_name[j]);

            if(strncmp(&line[i], macro_name[j], len) == 0 &&
               (i == 0 || !is_identifier_char(line[i-1])) &&
               !is_identifier_char(line[i+len]))
            {
                /* Function-like macro */
                if(macro_type[j] == 1)
                {
                    k = i + len;

                    while(line[k] == ' ' || line[k] == '\t')
                        k++;

                    if(line[k] == '(')
                    {
                        k++;
                        depth = 1;
                        arg_len = 0;

                        while(line[k] != '\0' && depth > 0)
                        {
                            if(line[k] == '(')
                                depth++;

                            if(line[k] == ')')
                                depth--;

                            if(depth > 0 && arg_len < 255)
                            {
                                argument[arg_len] = line[k];
                                arg_len++;
                            }

                            k++;
                        }

                        argument[arg_len] = '\0';

                        if(depth == 0)
                        {
                            replace_parameter(macro_value[j],
                                              macro_param[j],
                                              argument, fout);

                            i = k;
                            found = 1;
                            break;
                        }
                    }
                }
                /* Object-like macro */
                else
                {
                    fputs(macro_value[j], fout);

                    i = i + len;
                    found = 1;
                    break;
                }
            }
        }

        if(found == 0)
        {
            fputc(line[i], fout);
            i++;
        }
    }
}

/* Main macro handler */
void macro_handler(FILE *fp, FILE *fout)
{
    char line[512];

    char macro_name[10][50];
    char macro_value[10][256];
    char macro_param[10][50];

    int macro_type[10];

    int count = 0;
    int i;

    char *ptr;

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        ptr = line;

        /* Skip leading spaces */
        while(*ptr == ' ' || *ptr == '\t')
            ptr++;

        /* Check #define */
        if(strncmp(ptr, "#define", 7) == 0 &&
           (ptr[7] == ' ' || ptr[7] == '\t'))
        {
            ptr = ptr + 7;

            while(*ptr == ' ' || *ptr == '\t')
                ptr++;

            if(count >= 10)
                continue;

            i = 0;

            /* Read macro name */
            while(is_identifier_char(*ptr) && i < 49)
            {
                macro_name[count][i] = *ptr;
                i++;
                ptr++;
            }

            macro_name[count][i] = '\0';

            if(i > 0)
            {
                /* Function-like macro */
                if(*ptr == '(')
                {
                    macro_type[count] = 1;
                    ptr++;

                    i = 0;

                    while(*ptr != ')' && *ptr != '\0' &&
                          i < 49)
                    {
                        macro_param[count][i] = *ptr;
                        i++;
                        ptr++;
                    }

                    macro_param[count][i] = '\0';

                    if(*ptr == ')')
                        ptr++;

                    while(*ptr == ' ' || *ptr == '\t')
                        ptr++;

                    strcpy(macro_value[count], ptr);

                    /* Remove newline from macro body */
                    macro_value[count][strcspn(macro_value[count], "\n")] = '\0';
                }
                /* Object-like macro */
                else
                {
                    macro_type[count] = 0;

                    while(*ptr == ' ' || *ptr == '\t')
                        ptr++;

                    strcpy(macro_value[count], ptr);

                    /* Remove newline from macro value */
                    macro_value[count][strcspn(macro_value[count], "\n")] = '\0';

                    macro_param[count][0] = '\0';
                }

                count++;
            }
        }
        else
        {
            process_line(line, macro_name, macro_value,
                         macro_param, macro_type, count, fout);
        }
    }
}
