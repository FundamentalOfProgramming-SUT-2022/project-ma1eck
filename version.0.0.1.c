#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*
to do list :

1) bayad bebinam function haii ke output daran ro che konam :
- read_file    : return a string
- line_compare : printf
- find
- grep
 - simple
 - l
- tree : instead of printf , write in file

2) invalid inputs
- file's existence
- folder's existence

3) wildcard of find
- simple find -> ending with *
- count find ->beginning and ending with *

find function is not finished




*/

/*
some notes for using this program

- when I get string from user first convert the input string before passing it to "find" and "insert"


*/


void create_file(char * address);// directories exist
void create_folder(char * address);
void * read_file(char * address); // this is a valid address , return a string that shows what's in the file
void insert(char * address,int line_number , int start_pos,char * inserting_str); // must first convert the input string
void remove_by_index(char* address ,int line_number , int start_pos,int size , char direction );
int check_line_pos(char* address ,int line_number , int start_pos); // check if line and pos are valid
void copy_to_clipboard(char* address ,int line_number , int start_pos,int size , char direction );
void cut_to_clipboard(char* address ,int line_number , int start_pos,int size , char direction );
void initialize();
void insert_from_clipboard(char * address,int line_number , int start_pos);
void line_compare(char * address1 , char * address2);
void simple_find(char *address , char * str); // must first convert the input string
char * convert_input_str(char * str);
int strcmp2(char * str1 , char * str2 , int lenght);
int find_counter(char *address , char * str);
char * nth_word(char * str, int n);
int strcmp_wildcard(char * str1 , char * str2);//first string has *
int strcmp_beginning_with_star(char * str1 , char * str2);//first string has *
int strcmp_ending_with_star(char * str1 , char * str2);//first string has *
char strmatch_wildcard(char str[], char pattern[], int n, int m);
void simple_grep(char * str ,int n ,char * addresses[n]); // n : number of files
int count_grep  (char * str ,int n ,char * addresses[n]);
void l_grep     (char * str ,int n ,char * addresses[n]);
char tree(char * path, int depth_level , int final_depth); // depth can be -1
int isDir(const char* fileName);
void closing_pair(char * address);








int main()
{
    initialize();

    closing_pair("./root/closing pair temp.txt");
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
void insert(char * address,int line_number , int start_pos,char * inserting_str) // must first convert the input string
{

    FILE * file1 = fopen(address,"r");
    FILE * file2 = fopen("./temp/temp_insert.txt","w");
    //char * inserting_str = convert_input_str(inserting_str0);
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
void simple_find(char *address , char * str)
{
    int lenght = strlen(str);
    char * copy_str = (char*)malloc((lenght+1)*sizeof(char));
    int i = 0;
    int counter = 0;
    int flag4star = 0 ;

    while(i<lenght+1 && (str[i-1] != '\0' || i==1 ))
    {
        if(str[i]=='\\' && str[i+1]=='*')
        {
            copy_str[counter] = '*';
            i+=2;
            counter++;
            continue;
        }
        else if(str[i]!='\\' && str[i+1]=='*')
        {
            flag4star = 1;
            copy_str[counter] = str[i];
            copy_str[counter+1] = str[i+1];
            i+=2;
            counter+=1;
            continue;
        }
        else
        {
            copy_str[counter] = str[i];
            counter++;
            i++;
        }
    }
    if(str[0]=='*')
    {
        flag4star = 1;
    }
    if(flag4star == 0)
    {
        str = copy_str;
        int str_lenght = strlen(str);
        FILE * file = fopen(address,"r");
        char * a_line = (char*)malloc(1000000*sizeof(char));

        int char_before = 0;
        int main_result = -1;
        while(fgets(a_line,1000000,file) != NULL)
        {
            int line_lenght = strlen(a_line);
            int result = -1;
            int flag = 0;

            for(int i= 0 ; i<line_lenght ; i++)
            {
                if(flag == 1)
                {
                    break;
                }

                int comp_result = strcmp2(a_line+i,str,str_lenght);
                if(comp_result==1)
                {
                    result = i;
                    flag ++ ;
                }
                else if(comp_result == -1)
                {
                    break;
                }


            }
            if(flag == 1)
            {
                main_result = char_before + result;
                break;
            }

            char_before +=line_lenght;
        }
        printf("result : %d",main_result);


        fclose(file);
    }
    else
    {
        if(str[0]=='*')
        {
            str = copy_str;
            int str_lenght = strlen(str);
            FILE * file = fopen(address,"r");
            char * a_line = (char*)malloc(1000000*sizeof(char));

            int char_before = 0;
            int main_result = -1;
            while(fgets(a_line,1000000,file) != NULL)
            {
                int line_lenght = strlen(a_line);
                int result = strcmp_beginning_with_star(str,a_line);
                if(result != -1)
                {
                    main_result = result+char_before;
                    break;
                }
                char_before +=line_lenght;
            }
            printf("result : %d",main_result);

            fclose(file);
        }
        if(str[strlen(str-1)]=='*')
        {
            str = copy_str;
            int str_lenght = strlen(str);
            FILE * file = fopen(address,"r");
            char * a_line = (char*)malloc(1000000*sizeof(char));

            int char_before = 0;
            int main_result = -1;
            while(fgets(a_line,1000000,file) != NULL)
            {
                int line_lenght = strlen(a_line);
                int result = strcmp_beginning_with_star(str,a_line);
                if(result != -1)
                {
                    main_result = result+char_before;
                    break;
                }
                char_before +=line_lenght;
            }
            printf("result : %d",main_result);

            fclose(file);
        }
    }
}
char * convert_input_str(char * str)
{
    char * result = (char *)malloc((strlen(str)+1)*sizeof(char));
    int i=0;
    int counter = 0;
    while(i<strlen(str)+1 && str[i-1] != '\0')
    {
        if(str[i]=='\\' && str[i+1]=='n')
        {
            result[counter] = '\n';
            i+=2;
            counter++;
            continue;
        }
        else if(str[i]=='\\' && str[i+1]=='\\')
        {
            result[counter] = '\\';
            i+=2;
            counter++;
            continue;
        }
        else
        {
            result[counter] = str[i];
            counter++;
            i++;
        }
    }

    return result;
}
int strcmp2(char * str1 , char * str2 , int lenght)
{
    if(strlen(str1) < lenght || strlen(str2) < lenght )
    {
        return -1;
    }

    for(int i = 0 ; i<lenght ; i++)
    {
        if (str1[i] != str2[i])
        {
            return 0;
        }
    }
    return 1;

}
int find_counter(char *address , char * str)
{
    int lenght = strlen(str);
    char * copy_str = (char*)malloc((lenght+1)*sizeof(char));
    int i = 0;
    int counter = 0;
    int flag4star = 0 ;

    while(i<lenght+1 && (str[i-1] != '\0' || i==1 ))
    {
        if(str[i]=='\\' && str[i+1]=='*')
        {
            copy_str[counter] = '*';
            i+=2;
            counter++;
            continue;
        }
        else if(str[i]!='\\' && str[i+1]=='*')
        {
            flag4star = 1;
            copy_str[counter] = str[i];
            copy_str[counter+1] = str[i+1];
            i+=2;
            counter+=1;
            continue;
        }
        else
        {
            copy_str[counter] = str[i];
            counter++;
            i++;
        }
    }
    if(flag4star == 0)
    {
        str = copy_str;
        int str_lenght = strlen(str);
        FILE * file = fopen(address,"r");
        char * a_line = (char*)malloc(1000000*sizeof(char));

        int main_result = 0;
        while(fgets(a_line,1000000,file) != NULL)
        {
            int line_lenght = strlen(a_line);
            int result = -1;

            for(int i= 0 ; i<line_lenght ; i++)
            {
                int comp_result = strcmp2(a_line+i,str,str_lenght);
                if(comp_result==1)
                {
                    result = i;
                    main_result ++ ;
                }
                else if(comp_result == -1)
                {
                    break;
                }
            }

        }
        return main_result;


        fclose(file);
    }
}
char * nth_word(char * str,int n)
{
    char * result = (char *)malloc(strlen(str)*sizeof(char));
    int word_counter = 1;
    int counter=0;

    for (int i=0 ; i<strlen(str)+1 ; i++)
    {
        if(str[i] == ' ' || str[i]=='\n' || str[i]=='\0' || str[i]==EOF )
        {
            if(word_counter == n)
            {
                result[counter] = '\0';
                return result;
            }
            result[counter] = '\0';
            word_counter++;
            counter = -1;
        }
        else
        {
            result[counter] = str[i];
        }
        counter++;
    }
    result[0] = '\0';
    return result;
}
int strcmp_beginning_with_star(char * str1 , char * str2)//first string has *
{
    str1++;
    int result;
    int flag = 0;
    for(int i=1 ; i<strlen(str2) ; i++)
    {
        if(flag == 1)
        {
            break;
        }

        int comp_result = strcmp2(str1,str2+i,strlen(str1));
        if(comp_result==1 && str2[i-1]!=' ')
        {
            result = i;
            flag ++ ;
        }
        else if(comp_result == -1)
        {
            break;
        }

    }
    if (flag == 0)
    {
        return -1;
    }
    int main_result=-1;
    for(int i=0 ; i<result ; i++)
    {
        if(str2[i]==' ')
        {
            main_result = i+1;
        }
    }
    return main_result;
}
int strcmp_ending_with_star(char * str1 , char * str2)//first string has *
{
    str1;

    int str1_lenght = strlen(str1) - 1;
    int result;
    int flag = 0;
    for(int i=0 ; i<strlen(str2) - str1_lenght ; i++)
    {
        if(flag == 1)
        {
            break;
        }

        int comp_result = strcmp2(str1,str2+i,str1_lenght);
        if(comp_result==1 && str2[i+str1_lenght]!=' ' && str2[i+str1_lenght]!='\0' )
        {
            result = i;
            flag ++ ;
        }
        else if(comp_result == -1)
        {
            break;
        }

    }
    if (flag == 0)
    {
        return -1;
    }
    int main_result=-1;
    for(int i=0 ; i<result ; i++)
    {
        if(str2[i]==' ')
        {
            main_result = i+1;
        }
    }
    return main_result;
}
char strmatch_wildcard(char str[], char pattern[], int n, int m)
{
    if (m == 0)
        return (n == 0);

    char lookup[n + 1][m + 1];

    memset(lookup, 0, sizeof(lookup));

    lookup[0][0] = 1;

    for (int j = 1; j <= m; j++)
        if (pattern[j - 1] == '*')
            lookup[0][j] = lookup[0][j - 1];

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (pattern[j - 1] == '*')
                lookup[i][j] = lookup[i][j - 1] || lookup[i - 1][j];
            else if (str[i - 1] == pattern[j - 1])
                lookup[i][j] = lookup[i - 1][j - 1];

            else
                lookup[i][j] = 0;
        }
    }

    return lookup[n][m];
}
void simple_grep(char * str ,int n ,char * addresses[n]) // n : number of files
{
    char flag = 0 ;
    int str_lenght = strlen(str);
    for(int j=0 ; j<n ; j++ )
    {
        FILE * file = fopen(addresses[j],"r");
        char * a_line = (char*)malloc(1000000*sizeof(char));

        while(fgets(a_line,1000000,file)!= NULL)
        {
            int line_lenght = strlen(a_line);

            for(int i= 0 ; i<line_lenght ; i++)
            {
                int comp_result = strcmp2(a_line+i,str,str_lenght);
                if(comp_result==1)
                {
                    printf("%s: %s",addresses[j],a_line);
                    if(a_line[line_lenght-1]!='\n')
                    {
                        printf("\n");
                    }
                    flag = 1;
                    break;

                }
                else if(comp_result == -1)
                {
                    break;
                }
            }

        }
        fclose(file);
    }
    if(flag == 0)
    {
        printf("-1\n");
    }


}
void l_grep(char * str , int n , char * addresses[n])
{
    char flag = 0 ;
    int str_lenght = strlen(str);
    for(int j=0 ; j<n ; j++ )
    {
        FILE * file = fopen(addresses[j],"r");
        char * a_line = (char*)malloc(1000000*sizeof(char));

        char end = 0;
        while(fgets(a_line,1000000,file)!= NULL && !end)
        {
            int line_lenght = strlen(a_line);

            for(int i= 0 ; i<line_lenght ; i++)
            {
                int comp_result = strcmp2(a_line+i,str,str_lenght);
                if(comp_result==1)
                {
                    printf("%s\n",addresses[j]);
                    end = 1;
                    break;

                }
                else if(comp_result == -1)
                {
                    break;
                }
            }

        }
        fclose(file);
    }
}
int count_grep  (char * str ,int n ,char * addresses[n])
{
    int counter = 0 ;
    int str_lenght = strlen(str);
    for(int j=0 ; j<n ; j++ )
    {
        FILE * file = fopen(addresses[j],"r");
        char * a_line = (char*)malloc(1000000*sizeof(char));

        while(fgets(a_line,1000000,file)!= NULL)
        {
            int line_lenght = strlen(a_line);

            for(int i= 0 ; i<line_lenght ; i++)
            {
                int comp_result = strcmp2(a_line+i,str,str_lenght);
                if(comp_result==1)
                {
                    counter++ ;
                    break;

                }
                else if(comp_result == -1)
                {
                    break;
                }
            }

        }
        fclose(file);
    }
    return counter;

}
int isDir(const char* fileName)
{
    struct stat path;

    stat(fileName, &path);

    return 1 - S_ISREG(path.st_mode);
}
char tree(char * path, int depth_level , int final_depth)
{
    if(depth_level == final_depth+1 && final_depth!=-1)
    {
        return 0 ;
    }
    else if(isDir(path)==0)
    {
        return 0 ;
    }
    DIR *dir;
    struct dirent *file;

    dir = opendir(path);

    while((file = readdir(dir))!=NULL)
    {

        if(file->d_name[0]=='.')
        {
            continue;
        }

        for(int i=0 ; i<depth_level ; i++)
        {
            printf("|  ");
        }
        printf("|__%s\n",file->d_name);

        char * file_path = (char *)malloc(1000000);
        strcpy(file_path,path);
        if(file_path[strlen(path)-1]!='/')
        {
            strcat(file_path,"/");
        }
        strcat(file_path,file->d_name);
        tree(file_path,depth_level+1,final_depth);

    }

return 1;
}//tree("./root/",0,2);
void closing_pair(char * address)
{
    FILE * file = fopen(address,"r");
    FILE * temp_file = fopen("./temp/temp_closingPair.txt","w");
    char * a_line= (char *)malloc(1000000);


    char flag = 1;
    int pairs = 0 ;
    char pre_char = '\n';
    while(fgets(a_line,1000000,file)!=NULL)
    {
        pre_char = '\n';
        int space_number = 0;
        for(int i=0 ; i<strlen(a_line) ; i++)
        {
            if(a_line[i]=='{' ){
                pairs ++;
                if(pre_char!='\n'){
                    fprintf(temp_file," ");
                }
                space_number=0;
                fprintf(temp_file,"{");
                pre_char = '{';
            }
            if(a_line[i]=='}'){
                pairs --;
                space_number=0;
                if(pre_char!='\n'){
                        fprintf(temp_file,"\n");
                }
                fprintf(temp_file,"}");
                pre_char = '}';

                if(pairs<0)
                {
                    flag = 0;
                }
            }
            if((a_line[i]=='{' || a_line[i]=='}') && a_line[i+1]!='\n' && a_line[i+1]!=EOF && a_line[i+1]!='\0')
                {
                    fprintf(temp_file,"\n");
                    pre_char='\n';
                }
            else if(a_line[i]!='}' && a_line[i]!='{')
            {
                if(a_line[i]!=' '){
                    for(int j=0 ; j<space_number ; j++)
                    {
                        fprintf(temp_file," ");
                    }
                        pre_char = ' ';
                    space_number = 0;
                    fprintf(temp_file,"%c",a_line[i]);
                    pre_char = a_line[i];
                }
                else{
                    space_number++;
                }

            }
        }
        for(int j=0 ; j<space_number ; j++)
        {
            fprintf(temp_file," ");
        }
    }
    fclose(file); fclose(temp_file);
    if (pairs != 0)
    {
        flag = 0;
    }




    file = fopen(address,"w");
    temp_file = fopen("./temp/temp_closingPair.txt","r");

    if(flag == 1){
        int tabs = 0;
        char pre_ch2 , pre_ch;
        while(fgets(a_line,1000000,temp_file)!=NULL)
        {

            if(a_line[0]=='}'){
                tabs--;
            }
            for(int j=0 ; j<tabs ;j++)
            {
                fprintf(file,"    ");
            }

            for(int i=0; i<strlen(a_line); i++)
            {
                if(a_line[i]=='{')
                {
                    tabs++;
                    fprintf(file,"{");
                    pre_ch2= pre_ch;
                    pre_ch = '{';
                }
                else if(a_line[i]=='}')
                {
                    if(pre_ch2 == '{')
                    {
                        for(int j=0 ; j<tabs+1 ;j++)
                        {
                            fprintf(file,"    ");
                        }
                        fprintf(file,"\n");
                    }

                    fprintf(file,"}");
                    pre_ch2 = pre_ch;
                    pre_ch = '}';
                    //tabs--;
                }
                else
                {
                    pre_ch2 = pre_ch;
                    pre_ch = a_line[i];
                    fprintf(file,"%c",a_line[i]);
                }
            }
        }
    }
    else
    {
        while(fgets(a_line,1000000,temp_file)!=NULL)
        {
            for(int i=0; i<strlen(a_line); i++)
            {
                fprintf(file,"%c",a_line[i]);
            }
        }
    }
    fclose(file); fclose(temp_file);
}


