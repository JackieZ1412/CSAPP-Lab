#include "cachelab.h"
#include <stdio.h>
int s,S,E,b;
FILE *fp;
int hit_count,miss_count,eviction_count;
typedef struct _Cache{
    int valid,tag,last_visited;
}Cache;
Cache ** cache= NULL; 
char input[100];
long char2num(char *arg)
{
    long num = 0,i = 0;
    while(arg[i] != '\0'){
        num = num * 10 + arg[i++] - '0';
    }
    return num;
}
int hexnumber(char c){
	if(c >= '0'&& c <= '9'){
         return c - '0';
    }
	else if(c >= 'a' && c <= 'f'){
        return c - 'a' + 10;
    }
    else if(c >= 'A' && c <= 'F'){
        return c - 'A' + 10;
    }
	return 0;
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
    parse(argc,argv);
    printf("s:%d S:%d E:%d b:%d",s,S,E,b);
    hit_count = 0;
    miss_count = 0;
    eviction_count = 0;
    cache = (Cache **)malloc(sizeof(Cache *) * S);
    for(int i = 0;i < S;i++){
        cache[i] = (Cache *)malloc(sizeof(Cache) * E);
    }
    int time = 0;
    while(fgets(input,200,fp)){
        int size;
        int addr;
        int len = strlen(input) - 1;
        for(int i = 0;i < len;i++){
            
        }
    }
    printSummary(hit_count,miss_count,eviction_count);
    return 0;
}
