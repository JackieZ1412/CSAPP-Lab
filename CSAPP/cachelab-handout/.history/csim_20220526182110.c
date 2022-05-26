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
int char2hex(char c){
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
void cache_option(int op,int addr,int size,int time)
{
    int tag,offset,index,sign;
    offset = addr & ((1 << b) - 1);
    tag = (addr >> b) & ((-1U) >> (32 - s));
    sign = (1 << s) - 1;
    sign = sign << b;
    index = (addr & sign) >> b;
    printf("addr=%x tag:%x index=%x offset=%x\n",addr,tag,index,offset);
    if(op == 1){    // I_type

    }
    else if(op == 2){   // S_type

    }
    else if(op == 3){   // L_type

    }
    else if(op == 4){   // M_type
        
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
        int flag = 0;
        int size;
        int addr;
        int len = strlen(input) - 1;
        int op;
        for(int i = 0;i < len;i++){
            if(input[i] == 'I'){
                op = 1;
            }
            else if(input[i] == 'S'){
                op = 2;
            }
            else if(input[i] == 'L'){
                op = 3;
            }
            else if(input[i] == 'M'){
                op = 4;
            }
            else if(input[i] == ' '){
                continue;
            }
            else if(input[i] == ','){
                flag = 1;
            }
            else{
                if(flag == 0){
                    addr = addr * 16 + char2hex(input[i]);
                }
                else{
                    size = size * 10 + char2num(input[i]);
                }
            }
            cache_option(op,addr,size,time);
        }
    }
    printSummary(hit_count,miss_count,eviction_count);
    return 0;
}
