#include "cachelab.h"
#include <stdio.h>
int s,S,E,b;
FILE *fp;
int char2num(char *arg)
{
    int num = 0,i = 0;
    while(arg[i] != '\0'){
        num = num * 10 + arg[i++] - '0';
    }
    return num;
}
void parse(int argc, char **argv)
{
    for(int i = 0; i < argc; i++){
        if(argv[i][0] == '-'){
            if(argv[i][1] == 's')
            {
                s = char2num(argv[++i][2]);
                S = 1 << s;
            }
            else if(argv[i][1] == 'E'){
                E = char2num(argv[++i][2]);
            }
            else if(argv[i][1] == 'b'){
                b = char2num(argv[++i][2]);
            }
            else if(argv[i][1] == 't'){
                fp = fopen(argv[++i],'r');
            }
        }
    }
}
int main(int argc, char* argv[])
{
    int hit_count,miss_count,eviction_count;
    parse(argc,argv);
    
    printSummary(hit_count,miss_count,eviction_count);
    return 0;
}
