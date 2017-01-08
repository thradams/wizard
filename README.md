# wizard

Tool for generating code

```c

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

const char* Upper(const char* p)
{
    static char buffer[100] = { 0 };
    char *pDest = buffer;
    while (*p)
    {
        *pDest = toupper(*p);
        p++;
        pDest++;
    }
    return buffer;
}

void usage()
{
    printf("exe templatefile.txt [arg1..argN]\n");
    printf("@1 is replaced by arg1, @@1 is replaced by uppercase of arg1\n");
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        usage();
        return 1;
    }

    const char* className = argv[1];

    FILE *file = fopen(argv[1], "r");
    if (file)
    {
        for (;;)
        {
            char ch = fgetc(file);
            if (ch == '@')
            {
                ch = fgetc(file);
                if (ch >= '0' && ch <= '9')
                {
                    printf("%s", argv[1 + ch - '0']);
                }                
                else if (ch == '@')
                {
                    ch = fgetc(file);
                    if (ch >= '0' && ch <= '9')
                    {
                        printf("%s", Upper(argv[1 + ch - '0']));
                    }
                    else
                    {
                        printf("@@");
                        printf("%c", ch);
                    }
                }
                else
                {
                    printf("@");
                    printf("%c", ch);
                }
            }
            else
            {
                printf("%c", ch);
            }
            
            if (feof(file))
                break;
        }
    }

    return 0;
}


```

