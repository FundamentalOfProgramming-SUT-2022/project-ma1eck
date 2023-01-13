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
    int end = 0 ;
    char * temp_address = (char*) malloc(10000*sizeof(char));

    while(address[end]!='/'&&address[end]!='\0')
    {
        temp_address[end] = address[end];
        end++;
    }

    temp_address[end] = '\0';


    while (mkdir(temp_address ) ==  -1 || address[end]!='\0')
    {
        temp_address[end] = address[end];
        if(address[end]=='\0')
        {
            free(temp_address);
            return;
        }
        end++;
        while(address[end]!='/'&&address[end]!='\0')
        {

            temp_address[end] = address[end];
            end++;
        }
        temp_address[end] = '\0';
    }
    free(temp_address);
}//create_folder("root/folder1/f/f/f");

void * read_file(char * address) // this is a valid address , return a string that shows what's in the file
{
    char ch;
    char* result = (char*) malloc(1000000*sizeof(char));  // 10000 is max number of characters
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
void insert(char * address,int line_number , int start_pos,char * inserting_str)
{

    FILE * file1 = fopen(address,"r");
    FILE * file2 = fopen("./temp/temp_insert.txt","w");
    char ch;
    int line=1 ;
    int is_inserted = 0;
    while ((ch=fgetc(file1)) != EOF)
    {
        if(line == line_number && is_inserted == 0)
        {
            for(int pos =0 ; pos< start_pos ; pos++)
            {
                fprintf(file2,"%c",ch);
                ch = fgetc(file1);
            }
            fprintf(file2,"%s",inserting_str);
            is_inserted =1 ;
        }
        if(ch=='\n')
        {
            line++;
        }
        fprintf(file2,"%c",ch);
    }
    if(is_inserted == 0)
    {

        if(line<line_number)
        {
            fprintf(file2,"\n");
        }
        fprintf(file2,"%s",inserting_str);
    }
    fclose(file1); fclose(file2); // roy file 2 mohtava ye asli ro neveshtam

    FILE * file3 = fopen(address,"w");
    FILE * file4 = fopen("./temp/temp_insert.txt","r");

    while ((ch=fgetc(file4)) != EOF)
    {
        fprintf(file3,"%c",ch);
    }
    fclose(file3); fclose(file4);
}//insert("./root/test2.txt",1,0,"\nsalam ino insert kardam\n ");
void remove_by_index(char* address ,int line_number , int start_pos,int size , char direction )
{
    FILE * file1 = fopen(address,"r");
    FILE * file2 = fopen("./temp/temp_remove.txt","w");
    char ch;
    int line=1 ;
    int char_before_removing = 0;
    int flag =0 ;
    while ((ch=fgetc(file1)) != EOF)
    {
        if(line == line_number && flag == 0)
        {
            for(int pos =0 ; pos< start_pos ; pos++)
            {
                char_before_removing ++;
                fprintf(file2,"%c",ch);
                ch = fgetc(file1);
            }
            flag = 1;
        }
        if(ch=='\n')
        {
            line++;
        }
        char_before_removing += 1-flag;
        fprintf(file2,"%c",ch);
    }
    //printf("%d",char_before_removing);
    if(direction == 'b')
    {
        char_before_removing -= size;
    }
    char_before_removing++;
    fclose(file1); fclose(file2);

    FILE * file3 = fopen(address,"w");
    FILE * file4 = fopen("./temp/temp_remove.txt","r");

    int i=1;
    while ((ch=fgetc(file4)) != EOF)
    {
        if(char_before_removing == i)
        {
            for(int j=0 ; j<size ;j++)
            {
                ch = fgetc(file4);
            }
        }
        i++;
        if(ch==EOF)
            break;
        fprintf(file3,"%c",ch);
    }
    fclose(file3); fclose(file4);

}//remove_by_index("./root/test_insert.txt",1,1,1,'b');


int main()
{


    return 0;
}

