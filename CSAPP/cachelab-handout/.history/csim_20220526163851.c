#include "cachelab.h"
int s,S,E,b;
file *fp;
int main(int argc, char* argv[])
{
    int hit_count,miss_count,eviction_count;
    printSummary(hit_count,miss_count,eviction_count);
    return 0;
}
