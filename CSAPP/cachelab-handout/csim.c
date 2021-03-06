#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int s,S,E,b;
FILE *fp;
int hit_count,miss_count,eviction_count;
typedef struct _Cache{
    int valid,tag,last_visited;
}Cache;
Cache ** cache= NULL; 
char input[100];
unsigned int char2hex(char c){
	//printf("arg=%c\n",c);
	if(c >= '0'&& c <= '9'){
	 //printf("value = %d\n",c - '0');
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
                s = atoi(argv[++i]);
                S = 1 << s;
            }
            else if(argv[i][1] == 'E'){
                E = atoi(argv[++i]);
            }
            else if(argv[i][1] == 'b'){
                b = atoi(argv[++i]);
            }
            else if(argv[i][1] == 't'){
            	i++;
                fp = fopen((argv[i]),"r");
            }
        }
    }
}
void cache_option(int op,unsigned int addr,int size,int time)
{
    int tag,index;
    index = (addr >> b) & ((-1U) >> (32 - s));
    tag = addr >> (s + b);
    printf("op=%d addr=%x tag:%x index=%x\n",op,addr,tag,index);
    if(op == 1){    // I_type
        return;
    }
    if(op == 2 || op == 4){   // S_type or M_type need to write to the cache
        int hit = 0;
        for(int i = 0;i < E;i++){
            if(cache[index][i].tag == tag){   //hit
                cache[index][i].last_visited = 0;
                hit_count++;
                hit = 1;
                printf("hit\n");
                break;
            }
        }
        if(hit == 0){
            int sign = 0;
            for(int i = 0;i < E;i++){
                if(cache[index][i].valid == 0){
                    cache[index][i].valid = 1;
                    cache[index][i].last_visited = 0;
                    cache[index][i].tag = tag; 
                    sign = 1;
                    miss_count++;
                    printf("miss\n");
                    break;
                }
            }
            if(sign == 0){
                eviction_count++;
                miss_count++;
                printf("eviction\nmiss\n");
                int flag = 0,max_last_visited = 0;
                for(int i = 0;i < E;i++){
                    if(cache[index][i].last_visited > max_last_visited){
                        max_last_visited = cache[index][i].last_visited;
                        flag = i;
                    }
                }
                cache[index][flag].last_visited = 0;
                cache[index][flag].tag = tag;
            }
        }
    }
    if(op == 3 || op == 4){ // L_type or M_type need to write the cache
        int hit = 0;
        for(int i = 0;i < E;i++){
            if(cache[index][i].tag == tag){   //hit
                cache[index][i].last_visited = 0;
                hit_count++;
                printf("hit\n");
                hit = 1;
                break;
            }
        }
        if(hit == 0){
            int sign = 0;
            for(int i = 0;i < E;i++){
                if(cache[index][i].valid == 0){
                    cache[index][i].valid = 1;
                    cache[index][i].last_visited = 0;
                    cache[index][i].tag = tag; 
                    sign = 1;
                    miss_count++;
                    printf("miss\n");
                    break;
                }
            }
            if(sign == 0){
                eviction_count++;
                miss_count++;
                printf("eviction\nmiss\n");
                int flag = 0,max_last_visited = 0;
                for(int i = 0;i < E;i++){
                    if(cache[index][i].last_visited > max_last_visited){
                        max_last_visited = cache[index][i].last_visited;
                        flag = i;
                    }
                }
                cache[index][flag].last_visited = 0;
                cache[index][flag].tag = tag;
            }
        }      
    }
    for(int i = 0;i < S;i++){
        for(int j = 0;j < E;j++){
            if(cache[i][j].valid == 1){
                cache[i][j].last_visited++;
            }
        }
    }
}
int main(int argc, char* argv[])
{
    parse(argc,argv);
    //printf("s:%d S:%d E:%d b:%d",s,S,E,b);
    hit_count = 0;
    miss_count = 0;
    eviction_count = 0;
    cache = (Cache **)malloc(sizeof(Cache *) * S);
    for(int i = 0;i < S;i++){
        cache[i] = (Cache *)malloc(sizeof(Cache) * E);
    }
    for(int i = 0;i < S;i++){
        for(int j = 0;j < E;j++){
            cache[i][j].last_visited = -1;
            cache[i][j].valid = 0;
            cache[i][j].tag = -1;
        }
    }
    int time = 0;
    while(fgets(input,200,fp)){
        //printf("%s\n",input);
        int flag = 0;
        int size = 0;
        unsigned int addr = 0;
        int len = strlen(input) - 1;
        int op = 0;
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
                //op = 0;
            }
            else{
                if(flag == 0){
                    //printf("%c\n",input[i]);
                    addr = addr * 16 + char2hex(input[i]);
                    //printf("ADDR=%x\n",addr);
                }
                else{
                    size = size * 10 + (input[i] - '0');
                }
            }
            //cache_option(op,addr,size,time);
        }
        //printf("addr=%x size=%x\n",addr,size);
        cache_option(op,addr,size,time);
    }
    printSummary(hit_count,miss_count,eviction_count);
    for(int i = 0;i < S;i++){
        free(cache[i]);
    }
    free(cache);
    fclose(fp);
    return 0;
}
