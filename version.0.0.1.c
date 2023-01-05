#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//printf("%d",mkdir((char *)"rot"));
void creat_file(char * address)// directories exist
{
    FILE *fp = NULL;
    fp = fopen(address ,"w");
    fclose(fp);
}
//creat_file("root/test.txt");





int main()
{

    return 0;
}

