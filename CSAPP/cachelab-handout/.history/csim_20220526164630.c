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

            }
        }
    }
}
int main(int argc, char* argv[])
{
    int hit_count,miss_count,eviction_count;
    printSummary(hit_count,miss_count,eviction_count);
    return 0;
}
