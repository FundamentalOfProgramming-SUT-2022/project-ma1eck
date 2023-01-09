#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


//printf("%d",mkdir((char *)"rot"));
void create_file(char * address)// directories exist
{
    FILE *fp = NULL;
    fp = fopen(address ,"w");
    fclose(fp);
}
//create_file("root/test.txt");
void create_folder(char * address)
{
    int end = 0 , start = 0;

    while(address[end]!='/'&&address[end]!='\0')
    {   end++;
    }
    printf("%lld ",sizeof(address));
    char ch = address[end];
    address[end] = '\0';
    printf("%d",end);

    while (mkdir(address ) ==  -1)
    {

        address[end] = ch;
        if (ch=='\0')
        {   break;  }
        start = end;

        while(address[end]!='/'&&address[end]!='\0')
        {   end++;
           // printf("%d ",address[end]);
        }
        char ch = address[end];
        address[end] = '\0';
    }
} // not working

void * read_file(char * address) // this is a valid address , return a string that shows what's in the file
{
    char ch;
    char* result = (char*) malloc(10000*sizeof(char));  // 10000 is max number of characters
    FILE * file = fopen(address,"r");
    int i=0;
    do {
        ch = fgetc(file);
        result[i] = ch;
        i++;
    } while (ch != EOF);

    fclose(file);
    return result;

}// printf("%s",read_file("./root/test.txt"));




int main()
{
    printf("%s",read_file("./root/test.txt"));

    return 0;
}

