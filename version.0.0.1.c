#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>



void create_file(char * address);// directories exist
void create_folder(char * address);
void * read_file(char * address); // this is a valid address , return a string that shows what's in the file
void insert(char * address,int line_number , int start_pos,char * inserting_str);
void remove_by_index(char* address ,int line_number , int start_pos,int size , char direction );
int check_line_pos(char* address ,int line_number , int start_pos); // check if line and pos are valid
void copy_to_clipboard(char* address ,int line_number , int start_pos,int size , char direction );
void cut_to_clipboard(char* address ,int line_number , int start_pos,int size , char direction );
void initialize();
void insert_from_clipboard(char * address,int line_number , int start_pos);
void line_compare(char * address1 , char * address2);

int main()
{
    initialize();
    line_compare("./root/test2.txt","./root/test.txt");

    return 0;
}

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
int check_line_pos(char* address ,int line_number , int start_pos) // check if line and pos are valid
{
    FILE * file = fopen(address,"r");
    int line = 1;
    while(line<line_number)
    {
        char ch = fgetc(file);
        if(ch == '\n')
        {
            line++;
        }
        if( ch==EOF)
        {
            break;
        }
    }
    if (line== line_number)
    {
        int pos = 0;
        while (pos<start_pos)
        {
            char ch = fgetc(file);
            if( ch=='\n' || ch==EOF)
            {
                break;
            }
            pos++;
        }
        if(pos==start_pos)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if(line == line_number -1 && start_pos == 0)
        {

            return 1;
        }
    else
    {
        return 0;
    }

}
void initialize()
{
    create_folder("./root");
    create_folder("./temp");
    if (!fopen("./temp/temp_clipboard.txt","r"))
    {
        fclose(fopen("./temp/temp_clipboard.txt","w"));
    }
}
void copy_to_clipboard(char* address ,int line_number , int start_pos,int size , char direction )
{
    FILE * file1 = fopen(address,"r");
    char ch;
    int line=1 ;
    int char_before_removing = 0;
    int flag =0 ;
    while ((ch=fgetc(file1)) != EOF && flag==0)
    {
        if(line == line_number && flag == 0)
        {
            for(int pos =0 ; pos< start_pos ; pos++)
            {
                char_before_removing ++;
                ch = fgetc(file1);
            }
            flag = 1;
        }
        if(ch=='\n')
        {
            line++;
        }
        char_before_removing += 1-flag;
    }
    if(direction == 'b')
    {
        char_before_removing -= size;
    }
    char_before_removing++;
    fclose(file1);
    FILE * file3 = fopen("./temp/temp_clipboard.txt","w");
    FILE * file4 = fopen(address,"r");

    int i=1;
    while ((ch=fgetc(file4)) != EOF)
    {
        if(char_before_removing == i)
        {
            for(int j=0 ; j<size ;j++)
            {
                fprintf(file3,"%c",ch);
                ch = fgetc(file4);
            }
        }
        i++;
        if(ch==EOF)
            break;
        //fprintf(file3,"%c",ch);
    }
    fclose(file3); fclose(file4);

}//copy_to_clipboard("./root/test2.txt",2,3,6,'b');
void cut_to_clipboard(char* address ,int line_number , int start_pos,int size , char direction )
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
    FILE * file5 = fopen("./temp/temp_clipboard.txt","w");

    int i=1;
    while ((ch=fgetc(file4)) != EOF)
    {
        if(char_before_removing == i)
        {
            for(int j=0 ; j<size ;j++)
            {
                fprintf(file5,"%c",ch);
                ch = fgetc(file4);
            }
        }
        i++;
        if(ch==EOF)
            break;
        fprintf(file3,"%c",ch);
    }
    fclose(file3); fclose(file4); fclose(file5);

}//cut_to_clipboard("./root/test2.txt",2,3,6,'b');
void insert_from_clipboard(char * address,int line_number , int start_pos)
{
    FILE * file1 = fopen(address,"r");
    FILE * file2 = fopen("./temp/temp_paste.txt","w");
    FILE * file25 = fopen("./temp/temp_clipboard.txt","r");
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
            char ch2 = fgetc(file25);
            while(ch2!=EOF){
                fprintf(file2,"%c",ch2);
                ch2 = fgetc(file25);
            }
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
        char ch2 = fgetc(file25);
        while(ch2!=EOF){
            fprintf(file2,"%c",ch2);
            ch2 = fgetc(file25);
        }
    }
    fclose(file1); fclose(file2); fclose(file25); // roy file 2 mohtava ye asli ro neveshtam

    FILE * file3 = fopen(address,"w");
    FILE * file4 = fopen("./temp/temp_paste.txt","r");

    while ((ch=fgetc(file4)) != EOF)
    {
        fprintf(file3,"%c",ch);
    }
    fclose(file3); fclose(file4);
}//insert_from_clipboard("./root/test.txt",1,0);
void line_compare(char * address1 , char * address2) // this function print the result and don't return it;
{
    FILE * file1 = fopen(address1,"r");
    FILE * file2 = fopen(address2,"r");

    char * str1 = (char*)malloc(1000000*sizeof(char));
    char * str2 = (char*)malloc(1000000*sizeof(char));

    int finish1 = 0;
    int finish2 = 0;
    int line = 1;
    while (1)
    {
        if(fgets(str1,1000000,file1) == NULL)
        {
            finish1 = 1;
        }

        if(fgets(str2,1000000,file2) == NULL)
        {
            finish2 = 1;
        }
        if(finish1==1 || finish2==1)
        {
            break;
        }

        for(int i=0; i<1000000; i++)
        {
            if(str2[i]=='\0'&&str2[i-1]!='\n')
            {
                str2[i] = '\n'; str2[i+1] = '\0';

            }
            if(str2[i] == '\0')
                break;

        }
        for(int i=0; i<1000000; i++)
        {
            if(str1[i]=='\0'&&str1[i-1]!='\n')
            {
                str1[i] = '\n'; str1[i+1] = '\0';

            }
            if(str1[i] == '\0')
                break;

        }

        if(strcmp(str1,str2) != 0 )
        {
            printf("============ #%d ============\n",line);
            printf("%s",str1);
            printf("%s",str2);

        }

        line++;
    }

    if(finish1==0)
    {
        fclose(file2);
        int start_line = line;
        int finish_line = line-1;
        while (!finish1)
        {
            if(fgets(str1,1000000,file1) == NULL)
            {
                finish1 = 1;
            }
            finish_line++;
        }
        fclose(file1);
        printf("<<<<<<<<<<<< #%d - #%d<<<<<<<<<<<<\n",start_line,finish_line);

        file1 = fopen(address1,"r");
        for(int i=1 ;i<start_line ; i++)
        {
            fgets(str1,1000000,file1);
        }
        for(int i=start_line ;i<=finish_line ; i++)
        {
            fgets(str1,1000000,file1);
            for(int i=0; i<1000000; i++)
            {
            if(str1[i]=='\0'&&str1[i-1]!='\n')
            {
                str1[i] = '\n'; str1[i+1] = '\0';
            }
            if(str1[i] == '\0')
                break;
            }
            printf("%s",str1);
        }
        fclose(file1);
        return;
    }
    if(finish2==0)
    {
        fclose(file1);
        int start_line = line;
        int finish_line = line-1;
        while (!finish2)
        {
            if(fgets(str2,1000000,file2) == NULL)
            {
                finish2 = 1;
            }
            finish_line++;
        }
        fclose(file2);
        printf(">>>>>>>>>>>> #%d - #%d>>>>>>>>>>>>\n",start_line,finish_line);

        file2 = fopen(address2,"r");
        for(int i=1 ;i<start_line ; i++)
        {
            fgets(str2,1000000,file2);
        }
        for(int i=start_line ;i<=finish_line ; i++)
        {
            fgets(str2,1000000,file2);
            for(int i=0; i<1000000; i++)
            {
            if(str2[i]=='\0'&&str2[i-1]!='\n')
            {
                str2[i] = '\n'; str2[i+1] = '\0';
            }
            if(str2[i] == '\0')
                break;
            }
            printf("%s",str2);
        }
        fclose(file2);
        return;
    }


    fclose(file1);  fclose(file2);
}//line_compare("./root/test2.txt","./root/test.txt");



