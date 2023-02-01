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
#include <dirent.h>
#include <errno.h>

/*
to do list :



3) wildcard of find
- simple find -> ending with *
- count find ->beginning and ending with *

find function is not finished



*/

/*
some notes for using this program

- grep has a bug that end the program for this input : grep -l --str "ssfa" --files root/test.txt "root/fil e.txt"

*/

/*
nomre :
wildcard nazadam -50
copy matn boland +20
auto indent chand khati + 30
find & replace chand khati

arman ro bray har dastor momkene neveshtam

*/


void create_file(char * address);// directories exist
void create_folder(char * address);
char * read_file(char * address); // this is a valid address , return a string that shows what's in the file
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
void undo(char * address);
void backup_a_file(char * address);
int count_space(char * str);
int find2(char * address , char * pattern,int number);
char strcmp_beginning_with_star2(char * str1 , char * str2);//first string has *
char strcmp_ending_with_star2(char * str1 , char * str2);//first string has *
int convert2byword(int index ,char *str);
int * find_all(char * address , char * pattern);
char replace(char * address , char * pattern ,char * str, int number); // number = 1 for simple replace
void remove_by_pos_for_replace(char* address ,int pos ,int size , char direction );
void insert_by_pos_for_replace(char * address, int pos,char * inserting_str); // must first convert the input string
char replace_all(char * address , char * pattern ,char * str);
void cat_print(char * address); // this is a valid address


//--------------------------------------arman--------------------------------------------------
void insert_input_arman(char * address,int line_number , int start_pos,char * input_file_address); // must first convert the input string
int find2_output_arman(char * address , char * pattern,int number);// number = 1 for simple find
int find2_input_arman(char * address , char * pattern_address,int number);// number = 1 for simple find
int * find_all_output_arman(char * address , char * pattern);
int * find_all_input_arman(char * address , char * pattern_address);
char replace_input_arman(char * address , char * pattern_address ,char * str, int number); // return 1 for success and 0 for failure
char replace_all_input_arman(char * address , char * pattern_address ,char * str);
void tree_output_arman(char * path, int depth_level , int final_depth );
char tree_output_arman_komaki(char * path, int depth_level , int final_depth , FILE * file);
void simple_grep_input_arman(char * str_address ,int n ,char * addresses[n]); // n : number of files
void simple_grep_output_arman(char * str ,int n ,char * addresses[n]); // n : number of files
void l_grep_input_arman(char * str_address , int n , char * addresses[n]);
void l_grep_output_arman(char * str , int n , char * addresses[n]);
int count_grep_input_arman  (char * str_address ,int n ,char * addresses[n]);
int count_grep_output_arman  (char * str ,int n ,char * addresses[n]);
void line_compare_output_arman(char * address1 , char * address2);
//---------------------------------------------------------------
char * convert_input_address(char * str);
char check_folder_address(char * address);
char check_file_address(char* address);
char * first_str(char*str);
char * first_str2(char*str);
int count_in_str(char * str , char ch);
char check_address(char * address);




void master()
{
    char * input = (char* )malloc(100000);
    while (1)
    {
        gets(input);
        char * command = nth_word(input,1);

        // without arman

        if(strcmp(command,"createfile")==0) // createfile --file /root/dir1/dir2/file.txt
        {
            char * address = (char*)malloc(100000);
            int word_number = count_space(input) + 1 ;
            strcpy(address,nth_word(input,3));
            for(int i=4 ; i<= word_number ; i++)
            {
                strcat(address," ");
                strcat(address,nth_word(input,i));
            }
            int address_lenght = strlen(address);
            if(word_number!=3)
            {
                address++;
                address[address_lenght-1] = '\0';
            }
            address_lenght = strlen(address);
            if(address[address_lenght-1]=='"')
            {
                address[address_lenght-1] = '\0';
            }
            int flag = 0 ;
            for(int i=0; i<10 ; i++)
            {
                if(address[i]=='r')
                {
                    flag= i ;
                    break;
                }
            }
            address += flag;
            address = convert_input_address(address);
            char * temp  = (char*)malloc(strlen(address));
            flag = 0;
            for(int i=0 ; i<strlen(address); i++)
            {
                if(address[i]=='/')
                    flag = i;
                temp[i] = address[i];
            }
            temp[flag] = '\0';
            //printf("%s \n",temp);
            create_folder(temp);
            create_file(address);
            //printf("%s\n",address);
            printf("done\n");
        }
        else if(strcmp(command,"insertstr")==0) // insertstr --file /root/dir1/dir2/file.txt --str Salam –pos 2:5
        {
            char * address = (char*)malloc(100000);
            int word_number = count_space(input) + 1 ;
            strcpy(address,nth_word(input,3));
            for(int i=4 ; i<= word_number ; i++)
            {
                strcat(address," ");
                strcat(address,nth_word(input,i));
            }
            int address_lenght = strlen(address);

            address_lenght = strlen(address);
            if(address[address_lenght-1]=='"')
            {
                address[address_lenght-1] = '\0';
            }
            int flag = 0 ;
            for(int i=0; i<10 ; i++)
            {
                if(address[i]=='r')
                {
                    flag= i ;
                    break;
                }
            }
            address += flag;
            flag = strlen(address) ;
            char flag2 = 0;

            if(nth_word(input,3)[0]=='"')
            {
                flag2 = 1;
            }
            for(int i=1 ; i<strlen(address) ; i++)
            {
                if(strcmp2("str",address+i,3))

                if(address[i]=='"' && address[i-1]!='\\')
                {
                    flag = i;
                    break;
                }
            }
            address[flag] = '\0';
            if(flag2 == 0)
            {
                for(int i=0 ; i<strlen(address) ; i++)
                {
                    if(address[i]==' ')
                    {
                        flag = i;
                        break;
                    }
                }
            }
            address[flag] = '\0';
            address = convert_input_address(address);

            char * temp  = (char*)malloc(strlen(address));
            flag = 0;
            for(int i=0 ; i<strlen(address); i++)
            {
                if(address[i]=='/')
                    flag = i;
                temp[i] = address[i];
            }
            temp[flag] = '\0';
            //printf("folder : %s\n",temp);
            //printf("file   : %s\n",address);
            if(check_folder_address(temp)==0)
            {
                printf("invalid address\n");
                continue;
            }
            if(check_file_address(address)==0)
            {
                printf("invalid file name\n");
                continue;
            }
            char * str = (char *)malloc(10000000);
            flag = 0 ;
            char flag_address = 1;
            flag2 = 0;
            for(int i=1 ;i<strlen(input) ; i++)
            {
                if(input[i]=='"' && input[i-1]!='\\')
                {
                    flag2++;
                }
                if((flag2==0 && input[i]==' ') || flag2 ==2)
                {
                    //printf("8");
                    flag_address = 0;
                }
                if (strcmp2("str",input+i,3)==1  && flag_address==0 )
                {
                    flag = i;
                    break;
                }
            }
            flag+=3;
            strcpy(str,input+flag);
            if(str[0]=='"')
            {
                str++;
                flag = 0;
                for(int i=1 ; i<strlen(str) ; i++)
                {
                    if(str[i]=='"'&&str[i-1]=='\\')
                    {
                        flag = i ;
                        break;
                    }
                }
                str[flag]='\0';
            }
            else
            {
                flag = 0 ;
                for(int i=0 ; i<strlen(str); i++)
                {
                    if(str[i]!=' ')
                    {
                        flag =i;
                        break;
                    }
                }
                str += flag;
            }
            flag2 = 0;
            if(str[0]=='"')
            {
                //printf("**");
                flag2 = 1;
                str++;
                flag = strlen(str)-1;
                for(int i=1 ; i<strlen(str) ; i++)
                {
                    if(str[i]=='"' && str[i-1]!='\\')
                    {
                        flag = i;
                        break;
                    }
                }
                str[flag]= '\0';

            }
            else
            {
                flag = -1;
                for(int i=0 ; i<strlen(str) ; i++)
                {
                    if(str[i]==' ' )
                    {
                        flag = i;
                        break;
                    }
                }
                if(flag != -1)
                    str[flag]= '\0';
            }
            str = convert_input_str(str);
            int line=0 , pos=0;
            char * position = nth_word(input,count_space(input)+1);
            flag = 0 ;
            for(int i=0 ; i<strlen(position) ;i++)
            {
                if(position[i]==':')
                {
                     flag = 1;
                     continue;
                }
                else if(flag==0)
                {
                    line *= 10;
                    line += position[i]-'0';
                }
                else{
                    pos *=10;
                    pos += position[i]-'0';
                }
            }
            insert(address,line,pos,str);
            printf("done\n");




        }
        else if(strcmp(command,"cat")==0) //cat --file file.txt
        {
            char * address = (char*)malloc(100000);
            int word_number = count_space(input) + 1 ;
            strcpy(address,nth_word(input,3));
            for(int i=4 ; i<= word_number ; i++)
            {
                strcat(address," ");
                strcat(address,nth_word(input,i));
            }
            int address_lenght = strlen(address);
            if(word_number!=3)
            {
                address++;
                address[address_lenght-1] = '\0';
            }
            address_lenght = strlen(address);
            if(address[address_lenght-1]=='"')
            {
                address[address_lenght-1] = '\0';
            }
            int flag = 0 ;
            for(int i=0; i<10 ; i++)
            {
                if(address[i]=='r')
                {
                    flag= i ;
                    break;
                }
            }
            address += flag;

            char * temp  = (char*)malloc(strlen(address));
            flag = 0;
            for(int i=0 ; i<strlen(address); i++)
            {
                if(address[i]=='/')
                    flag = i;
                temp[i] = address[i];
            }
            temp[flag] = '\0';
            //printf("%s \n",temp);
            address = convert_input_address(address);
            temp = convert_input_address(temp);
            if(check_folder_address(temp)==0)
            {
                printf("invalid address\n");
                continue;
            }
            if(check_file_address(address)==0)
            {
                printf("invalid file name\n");
                continue;
            }
            cat_print(address);

            printf("done\n");
        }
        else if(strcmp(command,"removestr")==0) //  --file /root/file1.txt --pos 2:1 -size 3 -b
        {
            char * address = first_str(input);

            address = convert_input_address(address);
            int flag =0;
            for(int i=0 ;i<strlen(address) ; i++ )
            {
                if(address[i]=='r')
                {
                    flag = i;
                    break;
                }
            }
            address += flag;
            char * temp  = (char*)malloc(strlen(address));
            flag = 0;
            for(int i=0 ; i<strlen(address); i++)
            {
                if(address[i]=='/')
                    flag = i;
                temp[i] = address[i];
            }
            temp[flag] = '\0';

            if(check_folder_address(temp)==0)
            {
                printf("invalid address\n");
                continue;
            }
            if(check_file_address(address)==0)
            {
                printf("invalid file name\n");
                continue;
            }
            flag = 0;
            int char_pass = strlen(address)+2+strlen(nth_word(input,1)) + strlen(nth_word(input,2));
            for(int i =char_pass ; i<strlen(input); i++)
            {
                if(input[i]=='-')
                {
                    flag = i;
                    break;
                }
            }
            char * position = first_str(input+flag);
            int line=0, pos=0;
            flag = 0;
            for(int i=0 ; i<strlen(position) ;i++)
            {
                if(position[i]==':')
                {
                     flag = 1;
                     continue;
                }
                else if(flag==0)
                {
                    line *= 10;
                    line += position[i]-'0';
                }
                else{
                    pos *=10;
                    pos += position[i]-'0';
                }
            }
            char_pass += strlen(position)+1+strlen("pos");

            for(int i =char_pass ; i<strlen(input); i++)
            {
                if(input[i]=='-')
                {
                    flag = i;
                    break;
                }
            }
            char * size_str = first_str(input+flag);
            int size = 0;
            for(int i=0 ; i<strlen(size_str) ; i++)
            {
                size *=10;
                size += size_str[i]-'0';
            }


            for(int i =0 ; i<strlen(input); i++)
            {
                if(input[i]=='-')
                {
                    flag = i;
                }
            }
            char direction = input[flag+1];
            remove_by_index(address,line,pos,size,direction);
            printf("done\n");


        }
        else if(strcmp(command,"copystr")==0) // like remove
        {
            char * address = first_str(input);

            address = convert_input_address(address);
            int flag =0;
            for(int i=0 ;i<strlen(address) ; i++ )
            {
                if(address[i]=='r')
                {
                    flag = i;
                    break;
                }
            }
            address += flag;
            char * temp  = (char*)malloc(strlen(address));
            flag = 0;
            for(int i=0 ; i<strlen(address); i++)
            {
                if(address[i]=='/')
                    flag = i;
                temp[i] = address[i];
            }
            temp[flag] = '\0';

            if(check_folder_address(temp)==0)
            {
                printf("invalid address\n");
                continue;
            }
            if(check_file_address(address)==0)
            {
                printf("invalid file name\n");
                continue;
            }
            flag = 0;
            int char_pass = strlen(address)+2+strlen(nth_word(input,1)) + strlen(nth_word(input,2));
            for(int i =char_pass ; i<strlen(input); i++)
            {
                if(input[i]=='-')
                {
                    flag = i;
                    break;
                }
            }
            char * position = first_str(input+flag);
            int line=0, pos=0;
            flag = 0;
            for(int i=0 ; i<strlen(position) ;i++)
            {
                if(position[i]==':')
                {
                     flag = 1;
                     continue;
                }
                else if(flag==0)
                {
                    line *= 10;
                    line += position[i]-'0';
                }
                else{
                    pos *=10;
                    pos += position[i]-'0';
                }
            }
            char_pass += strlen(position)+1+strlen("pos");

            for(int i =char_pass ; i<strlen(input); i++)
            {
                if(input[i]=='-')
                {
                    flag = i;
                    break;
                }
            }
            char * size_str = first_str(input+flag);
            int size = 0;
            for(int i=0 ; i<strlen(size_str) ; i++)
            {
                size *=10;
                size += size_str[i]-'0';
            }


            for(int i =0 ; i<strlen(input); i++)
            {
                if(input[i]=='-')
                {
                    flag = i;
                }
            }
            char direction = input[flag+1];
            copy_to_clipboard(address,line,pos,size,direction);
            printf("done\n");


        }
        else if(strcmp(command,"cutstr")==0) // like remove
        {
            char * address = first_str(input);

            address = convert_input_address(address);
            int flag =0;
            for(int i=0 ;i<strlen(address) ; i++ )
            {
                if(address[i]=='r')
                {
                    flag = i;
                    break;
                }
            }
            address += flag;
            char * temp  = (char*)malloc(strlen(address));
            flag = 0;
            for(int i=0 ; i<strlen(address); i++)
            {
                if(address[i]=='/')
                    flag = i;
                temp[i] = address[i];
            }
            temp[flag] = '\0';

            if(check_folder_address(temp)==0)
            {
                printf("invalid address\n");
                continue;
            }
            if(check_file_address(address)==0)
            {
                printf("invalid file name\n");
                continue;
            }
            flag = 0;
            int char_pass = strlen(address)+2+strlen(nth_word(input,1)) + strlen(nth_word(input,2));
            for(int i =char_pass ; i<strlen(input); i++)
            {
                if(input[i]=='-')
                {
                    flag = i;
                    break;
                }
            }
            char * position = first_str(input+flag);
            int line=0, pos=0;
            flag = 0;
            for(int i=0 ; i<strlen(position) ;i++)
            {
                if(position[i]==':')
                {
                     flag = 1;
                     continue;
                }
                else if(flag==0)
                {
                    line *= 10;
                    line += position[i]-'0';
                }
                else{
                    pos *=10;
                    pos += position[i]-'0';
                }
            }
            char_pass += strlen(position)+1+strlen("pos");

            for(int i =char_pass ; i<strlen(input); i++)
            {
                if(input[i]=='-')
                {
                    flag = i;
                    break;
                }
            }
            char * size_str = first_str(input+flag);
            int size = 0;
            for(int i=0 ; i<strlen(size_str) ; i++)
            {
                size *=10;
                size += size_str[i]-'0';
            }


            for(int i =0 ; i<strlen(input); i++)
            {
                if(input[i]=='-')
                {
                    flag = i;
                }
            }
            char direction = input[flag+1];
            cut_to_clipboard(address,line,pos,size,direction);
            printf("done\n");


        }
        else if(strcmp(command,"pastestr")==0) //pastestr –file <file name> –pos <line no>:<start position>
        {
            char * address = (char*)malloc(100000);
            int word_number = count_space(input) + 1 ;
            strcpy(address,nth_word(input,3));
            for(int i=4 ; i<= word_number ; i++)
            {
                strcat(address," ");
                strcat(address,nth_word(input,i));
            }
            int address_lenght = strlen(address);

            address_lenght = strlen(address);
            if(address[address_lenght-1]=='"')
            {
                address[address_lenght-1] = '\0';
            }
            int flag = 0 ;
            for(int i=0; i<10 ; i++)
            {
                if(address[i]=='r')
                {
                    flag= i ;
                    break;
                }
            }
            address += flag;
            flag = strlen(address) ;
            char flag2 = 0;

            if(nth_word(input,3)[0]=='"')
            {
                flag2 = 1;
            }
            for(int i=1 ; i<strlen(address) ; i++)
            {
                if(strcmp2("str",address+i,3))

                if(address[i]=='"' && address[i-1]!='\\')
                {
                    flag = i;
                    break;
                }
            }
            address[flag] = '\0';
            if(flag2 == 0)
            {
                for(int i=0 ; i<strlen(address) ; i++)
                {
                    if(address[i]==' ')
                    {
                        flag = i;
                        break;
                    }
                }
            }
            address[flag] = '\0';
            address = convert_input_address(address);

            char * temp  = (char*)malloc(strlen(address));
            flag = 0;
            for(int i=0 ; i<strlen(address); i++)
            {
                if(address[i]=='/')
                    flag = i;
                temp[i] = address[i];
            }
            temp[flag] = '\0';
            //printf("folder : %s\n",temp);
            //printf("file   : %s\n",address);
            if(check_folder_address(temp)==0)
            {
                printf("invalid address\n");
                continue;
            }
            if(check_file_address(address)==0)
            {
                printf("invalid file name\n");
                continue;
            }
            char * str = (char *)malloc(10000000);
            flag = 0 ;
            char flag_address = 1;
            flag2 = 0;
            for(int i=1 ;i<strlen(input) ; i++)
            {
                if(input[i]=='"' && input[i-1]!='\\')
                {
                    flag2++;
                }
                if((flag2==0 && input[i]==' ') || flag2 ==2)
                {
                    //printf("8");
                    flag_address = 0;
                }
                if (strcmp2("str",input+i,3)==1  && flag_address==0 )
                {
                    flag = i;
                    break;
                }
            }
            flag+=3;
            strcpy(str,input+flag);
            if(str[0]=='"')
            {
                str++;
                flag = 0;
                for(int i=1 ; i<strlen(str) ; i++)
                {
                    if(str[i]=='"'&&str[i-1]=='\\')
                    {
                        flag = i ;
                        break;
                    }
                }
                str[flag]='\0';
            }
            else
            {
                flag = 0 ;
                for(int i=0 ; i<strlen(str); i++)
                {
                    if(str[i]!=' ')
                    {
                        flag =i;
                        break;
                    }
                }
                str += flag;
            }
            flag2 = 0;
            if(str[0]=='"')
            {
                //printf("**");
                flag2 = 1;
                str++;
                flag = strlen(str)-1;
                for(int i=1 ; i<strlen(str) ; i++)
                {
                    if(str[i]=='"' && str[i-1]!='\\')
                    {
                        flag = i;
                        break;
                    }
                }
                str[flag]= '\0';

            }
            else
            {
                flag = strlen(str)-1;
                for(int i=0 ; i<strlen(str) ; i++)
                {
                    if(str[i]==' ' )
                    {
                        flag = i;
                        break;
                    }
                }
                str[flag]= '\0';
            }
            str = convert_input_str(str);
            int line=0 , pos=0;
            char * position = nth_word(input,count_space(input)+1);
            flag = 0 ;
            for(int i=0 ; i<strlen(position) ;i++)
            {
                if(position[i]==':')
                {
                     flag = 1;
                     continue;
                }
                else if(flag==0)
                {
                    line *= 10;
                    line += position[i]-'0';
                }
                else{
                    pos *=10;
                    pos += position[i]-'0';
                }
            }
            insert_from_clipboard(address,line,pos);
            printf("done\n");




        }
        else if(strcmp(command,"undo")==0) // undo --file root/test.txt
        {
            char * address = (char*)malloc(100000);
            int word_number = count_space(input) + 1 ;
            strcpy(address,nth_word(input,3));
            for(int i=4 ; i<= word_number ; i++)
            {
                strcat(address," ");
                strcat(address,nth_word(input,i));
            }
            int address_lenght = strlen(address);
            if(word_number!=3)
            {
                address++;
                address[address_lenght-1] = '\0';
            }
            address_lenght = strlen(address);
            if(address[address_lenght-1]=='"')
            {
                address[address_lenght-1] = '\0';
            }
            int flag = 0 ;
            for(int i=0; i<10 ; i++)
            {
                if(address[i]=='r')
                {
                    flag= i ;
                    break;
                }
            }
            address += flag;

            char * temp  = (char*)malloc(strlen(address));
            flag = 0;
            for(int i=0 ; i<strlen(address); i++)
            {
                if(address[i]=='/')
                    flag = i;
                temp[i] = address[i];
            }
            temp[flag] = '\0';
            //printf("%s \n",temp);
            address = convert_input_address(address);
            temp = convert_input_address(temp);
            if(check_folder_address(temp)==0)
            {
                printf("invalid address\n");
                continue;
            }
            if(check_file_address(address)==0)
            {
                printf("invalid file name\n");
                continue;
            }
            undo(address);

            printf("done\n");
        }
        else if(strcmp(command,"auto-indent")==0) // auto-indent --file root/test.txt
        {
            char * address = (char*)malloc(100000);
            int word_number = count_space(input) + 1 ;
            strcpy(address,nth_word(input,3));
            for(int i=4 ; i<= word_number ; i++)
            {
                strcat(address," ");
                strcat(address,nth_word(input,i));
            }
            int address_lenght = strlen(address);
            if(word_number!=3)
            {
                address++;
                address[address_lenght-1] = '\0';
            }
            address_lenght = strlen(address);
            if(address[address_lenght-1]=='"')
            {
                address[address_lenght-1] = '\0';
            }
            int flag = 0 ;
            for(int i=0; i<10 ; i++)
            {
                if(address[i]=='r')
                {
                    flag= i ;
                    break;
                }
            }
            address += flag;

            char * temp  = (char*)malloc(strlen(address));
            flag = 0;
            for(int i=0 ; i<strlen(address); i++)
            {
                if(address[i]=='/')
                    flag = i;
                temp[i] = address[i];
            }
            temp[flag] = '\0';
            //printf("%s \n",temp);
            address = convert_input_address(address);
            temp = convert_input_address(temp);
            if(check_folder_address(temp)==0)
            {
                printf("invalid address\n");
                continue;
            }
            if(check_file_address(address)==0)
            {
                printf("invalid file name\n");
                continue;
            }
            closing_pair(address);

            printf("done\n");
        }
        else if(strcmp(command,"tree")==0) //tree 1
        {
            char * depth_str = nth_word(input,2);
            int depth = 0;
            int sign = 1;
            if (depth_str[0]=='-')
            {
                sign = -1;
                depth_str++;
            }
            for(int i=0 ; i<strlen(depth_str) ; i++)
                {
                    depth *=10;
                    depth += depth_str[i]-'0';
                }
            depth *= sign;
            if(depth<-1)
            {
                printf("invalid depth\n");
                continue;
            }
            tree("root",0,depth);
            //printf("done\n");
        }
        else if(strcmp(command,"compare")==0) // compare a.txt b.txt
        {
            char * address1 = first_str2(input+8);
            char * address2 ;
            if(input[8]=='"')
            {
                address2 = first_str2(input+8+2+strlen(address1)+1);
            }
            else
            {
                address2 = first_str2(input+8+strlen(address1)+1);
            }
            address1 = convert_input_address(address1);
            address2 = convert_input_address(address2);

            int flag = 0;
            for(int i=0 ; i<strlen(address1); i++)
            {
                if(address1[i]=='r')
                {
                    flag = i;
                    break;
                }
            }
            address1 += flag;

            for(int i=0 ; i<strlen(address2); i++)
            {
                if(address2[i]=='r')
                {
                    flag = i;
                    break;
                }
            }
            address2 += flag;

            char * temp1  = (char*)malloc(strlen(address1));
            flag = 0;
            for(int i=0 ; i<strlen(address1); i++)
            {
                if(address1[i]=='/')
                    flag = i;
                temp1[i] = address1[i];
            }
            temp1[flag] = '\0';
            //printf("%s \n",temp);
            if(check_folder_address(temp1)==0)
            {
                printf("first file : invalid address\n");
                continue;
            }
            if(check_file_address(address1)==0)
            {
                printf("first file : invalid file name\n");
                continue;
            }

            char * temp2  = (char*)malloc(strlen(address2));
            flag = 0;
            for(int i=0 ; i<strlen(address2); i++)
            {
                if(address2[i]=='/')
                    flag = i;
                temp2[i] = address2[i];
            }
            temp2[flag] = '\0';
            //printf("%s \n",temp);
            if(check_folder_address(temp2)==0)
            {
                printf("second file : invalid address\n");
                continue;
            }
            if(check_file_address(address2)==0)
            {
                printf("second file : invalid file name\n");
                continue;
            }

            line_compare(address1,address2);

        }
        else if(strcmp(command,"find")==0)// find --file root/file1.txt --str "sa" -count -byword -at 2 -all
        {
            char * address = (char*)malloc(100000);
            int word_number = count_space(input) + 1 ;
            strcpy(address,nth_word(input,3));
            for(int i=4 ; i<= word_number ; i++)
            {
                strcat(address," ");
                strcat(address,nth_word(input,i));
            }
            int address_lenght = strlen(address);

            address_lenght = strlen(address);
            if(address[address_lenght-1]=='"')
            {
                address[address_lenght-1] = '\0';
            }
            int flag = 0 ;
            for(int i=0; i<10 ; i++)
            {
                if(address[i]=='r')
                {
                    flag= i ;
                    break;
                }
            }
            address += flag;
            flag = strlen(address) ;
            char flag2 = 0;

            if(nth_word(input,3)[0]=='"')
            {
                flag2 = 1;
            }
            for(int i=1 ; i<strlen(address) ; i++)
            {
                if(strcmp2("str",address+i,3))

                if(address[i]=='"' && address[i-1]!='\\')
                {
                    flag = i;
                    break;
                }
            }
            address[flag] = '\0';
            if(flag2 == 0)
            {
                for(int i=0 ; i<strlen(address) ; i++)
                {
                    if(address[i]==' ')
                    {
                        flag = i;
                        break;
                    }
                }
            }
            address[flag] = '\0';
            address = convert_input_address(address);

            char * temp  = (char*)malloc(strlen(address));
            flag = 0;
            for(int i=0 ; i<strlen(address); i++)
            {
                if(address[i]=='/')
                    flag = i;
                temp[i] = address[i];
            }
            temp[flag] = '\0';
            //printf("folder : %s\n",temp);
            //printf("file   : %s\n",address);
            if(check_folder_address(temp)==0)
            {
                printf("invalid address\n");
                continue;
            }
            if(check_file_address(address)==0)
            {
                printf("invalid file name\n");
                continue;
            }
            char * str = (char *)malloc(10000000);
            flag = 0 ;
            char flag_address = 1;
            flag2 = 0;
            for(int i=1 ;i<strlen(input) ; i++)
            {
                if(input[i]=='"' && input[i-1]!='\\')
                {
                    flag2++;
                }
                if((flag2==0 && input[i]==' ') || flag2 ==2)
                {
                    //printf("8");
                    flag_address = 0;
                }
                if (strcmp2("str",input+i,3)==1  && flag_address==0 )
                {
                    flag = i;
                    break;
                }
            }
            flag+=3;
            strcpy(str,input+flag);
            if(str[0]=='"')
            {
                str++;
                flag = 0;
                for(int i=1 ; i<strlen(str) ; i++)
                {
                    if(str[i]=='"'&&str[i-1]=='\\')
                    {
                        flag = i ;
                        break;
                    }
                }
                str[flag]='\0';
            }
            else
            {
                flag = 0 ;
                for(int i=0 ; i<strlen(str); i++)
                {
                    if(str[i]!=' ')
                    {
                        flag =i;
                        break;
                    }
                }
                str += flag;
            }
            flag2 = 0;
            if(str[0]=='"')
            {
                //printf("**");
                flag2 = 1;
                str++;
                flag = strlen(str)-1;
                for(int i=1 ; i<strlen(str) ; i++)
                {
                    if(str[i]=='"' && str[i-1]!='\\')
                    {
                        flag = i;
                        break;
                    }
                }
                str[flag]= '\0';

            }
            else
            {
                flag = -1;
                for(int i=0 ; i<strlen(str) ; i++)
                {
                    if(str[i]==' ' )
                    {
                        flag = i;
                        break;
                    }
                }
                if (flag!=-1)
                    str[flag]= '\0';
            }
           // printf("address : %s\nstr : %s",address,str);
            str = convert_input_str(str);
            int number = count_in_str(input,'-') - count_in_str(address,'-') - count_in_str(str,'-');
            int at = -1 ;
            char count = 0 , all=0 , byword = 0;

            if(number==4)
            {
               printf("%d\n",find2(address,str,1));
               continue;
            }
            else if(number==5)
            {
                flag = 0;
                for(int i=0 ;i<strlen(input) ;i++)
                {
                    if(input[i]=='-')
                    {
                        flag = i;
                    }
                }
                char * attribute = nth_word(input+flag+1,1);
                if(strcmp(attribute,"byword")==0)
                {
                    printf("%d\n",convert2byword(find2(address,str,1),address));
                    continue;
                }
                else if(strcmp(attribute,"count")==0)
                {
                    printf("%d\n",find_counter(address,str));
                    continue;
                }
                else if(strcmp(attribute,"all")==0)
                {
                    int * out = find_all(address,str);
                    int j =0 ;
                    while (out[j]!=-1)
                    {
                        printf("%d ",out[j]);
                        j++;
                    }
                    if(j==0)
                    {
                        printf("-1");
                    }
                    printf("\n");
                }
                else if(strcmp(attribute,"at")==0)
                {
                    char * at_str = nth_word(input+flag+1+3,1);
                    at = 0;
                    for(int i=0; i<strlen(at_str); i++)
                    {
                        at *=10 ;
                        at += at_str[i]-'0';
                    }
                    printf("%d\n",find2(address,str,at));
                }
                else
                {
                    printf("invalid attribute");
                    continue;
                }
                continue;


           }
            else if(number==6)
            {
                flag = 0;
                for(int i=0 ;i<strlen(input) ;i++)
                {
                    if(input[i]=='-')
                    {
                        flag = i;
                    }
                }
                char * attribute = nth_word(input+flag+1,1);
                if(strcmp(attribute,"byword")==0)
                {
                    byword = 1;
                }
                else if(strcmp(attribute,"count")==0)
                {
                    count =1 ;
                }
                else if(strcmp(attribute,"all")==0)
                {
                    all = 1;
                }
                else if(strcmp(attribute,"at")==0)
                {
                    char * at_str = nth_word(input+flag+1+3,1);
                    at = 0;
                    for(int i=0; i<strlen(at_str); i++)
                    {
                        at *=10 ;
                        at += at_str[i]-'0';
                    }
                }
                else
                {
                        printf("invalid attribute");
                    continue;
                }
                int all_ = count_in_str(input,'-');
                flag2 = 0;
                flag = 0;
                for(int i=0 ;i<strlen(input) ;i++)
                {
                    if(input[i]=='-')
                    {
                        flag = i;
                        flag2 ++;
                    }
                    if(flag2 == all_ -1)
                    {
                        break;
                    }
                }
                attribute = nth_word(input+flag+1,1);
                if(strcmp(attribute,"byword")==0)
                {
                    byword = 1;
                }
                else if(strcmp(attribute,"count")==0)
                {
                    count =1 ;
                }
                else if(strcmp(attribute,"all")==0)
                {
                    all = 1;
                }
                else if(strcmp(attribute,"at")==0)
                {
                    char * at_str = nth_word(input+flag+1+3,1);
                    at = 0;
                    for(int i=0; i<strlen(at_str); i++)
                    {
                        at *=10 ;
                        at += at_str[i]-'0';
                    }
                }
                else
                {
                    printf("invalid attribute\n");
                    continue;
                }

                if(count == 1 || (at!=-1 && all==1) || byword == 0)
                {
                    printf("invalid attribute\n");
                    continue;
                }
                else
                {
                    if(at != -1)
                    {
                        printf("%d\n",convert2byword(find2(address,str,at),address));
                        continue;
                    }
                    else if(all==1 )
                    {
                        int * out = find_all(address,str);
                        int j =0 ;
                        while (out[j]!=-1)
                        {
                            printf("%d ",convert2byword(out[j],address));
                            j++;
                        }
                        if(j==0)
                        {
                            printf("-1");
                        }
                        printf("\n");
                        continue;
                    }
                    else
                    {
                        printf("invalid attribute\n");
                        continue;
                    }
                }

            }
            else
            {
                 printf("invalid attribute");
                continue;
            }

        }
        else if(strcmp(command,"replace")==0)// replace --file root/test.txt --str1 "s\*" --str2 "sa"  [-at <num> | -all]
        {
            char * address = (char*)malloc(100000);
            int word_number = count_space(input) + 1 ;
            strcpy(address,nth_word(input,3));
            for(int i=4 ; i<= word_number ; i++)
            {
                strcat(address," ");
                strcat(address,nth_word(input,i));
            }
            int address_lenght = strlen(address);

            address_lenght = strlen(address);
            if(address[address_lenght-1]=='"')
            {
                address[address_lenght-1] = '\0';
            }
            int flag = 0 ;
            for(int i=0; i<10 ; i++)
            {
                if(address[i]=='r')
                {
                    flag= i ;
                    break;
                }
            }
            address += flag;
            flag = strlen(address) ;
            char flag2 = 0;

            if(nth_word(input,3)[0]=='"')
            {
                flag2 = 1;
            }
            for(int i=1 ; i<strlen(address) ; i++)
            {

                if(address[i]=='"' && address[i-1]!='\\')
                {
                    flag = i;
                    break;
                }
            }
            address[flag] = '\0';
            if(flag2 == 0)
            {
                for(int i=0 ; i<strlen(address) ; i++)
                {
                    if(address[i]==' ')
                    {
                        flag = i;
                        break;
                    }
                }
            }
            address[flag] = '\0';
            address = convert_input_address(address);

            char * temp  = (char*)malloc(strlen(address));
            flag = 0;
            for(int i=0 ; i<strlen(address); i++)
            {
                if(address[i]=='/')
                    flag = i;
                temp[i] = address[i];
            }
            temp[flag] = '\0';
            //printf("folder : %s\n",temp);
            //printf("file   : %s\n",address);
            if(check_folder_address(temp)==0)
            {
                printf("invalid address\n");
                continue;
            }
            if(check_file_address(address)==0)
            {
                printf("invalid file name\n");
                continue;
            }
            char * str = (char *)malloc(10000000);
            flag = 0 ;
            char flag_address = 1;
            flag2 = 0;
            for(int i=1 ;i<strlen(input) ; i++)
            {
                if(input[i]=='"' && input[i-1]!='\\')
                {
                    flag2++;
                }
                if((flag2==0 && input[i]==' ') || flag2 ==2)
                {
                    //printf("8");
                    flag_address = 0;
                }
                if (strcmp2("str1",input+i,4)==1  && flag_address==0 )
                {
                    flag = i;
                    break;
                }
            }
            flag+=4;
            strcpy(str,input+flag);
            if(str[0]=='"')
            {
                str++;
                flag = 0;
                for(int i=1 ; i<strlen(str) ; i++)
                {
                    if(str[i]=='"'&&str[i-1]=='\\')
                    {
                        flag = i ;
                        break;
                    }
                }
                str[flag]='\0';
            }
            else
            {
                flag = 0 ;
                for(int i=0 ; i<strlen(str); i++)
                {
                    if(str[i]!=' ')
                    {
                        flag =i;
                        break;
                    }
                }
                str += flag;
            }
            flag2 = 0;
            if(str[0]=='"')
            {
                //printf("**");
                flag2 = 1;
                str++;
                flag = strlen(str)-1;
                for(int i=1 ; i<strlen(str) ; i++)
                {
                    if(str[i]=='"' && str[i-1]!='\\')
                    {
                        flag = i;
                        break;
                    }
                }
                str[flag]= '\0';

            }
            else
            {
                flag = -1;
                for(int i=0 ; i<strlen(str) ; i++)
                {
                    if(str[i]==' ' )
                    {
                        flag = i;
                        break;
                    }
                }
                if (flag!=-1)
                    str[flag]= '\0';
            }
           // printf("address : %s\nstr : %s",address,str);
            str = convert_input_str(str);
            int temp_number = strlen("replace --str1 ") + strlen(str) + strlen(" --file ") + strlen(address);
            flag = 0;
            for(int i = temp_number ; i<strlen(input) ; i++)
            {
                if(strcmp2(input+i,"--str2",strlen("--str2")))
                {
                    flag = i;
                    break;
                }
            }
            char * str2 = first_str2(input+flag+strlen("--str2 "));
            str2 = convert_input_str(str2);
            int number = count_in_str(input,'-') - count_in_str(address,'-') - count_in_str(str,'-') - count_in_str(str2,'-');
            int at = -1 ;

            if(number==6)
            {
                if(1==replace(address,str,str2,1))
                    printf("done\n");
                else
                    printf("-1\n");
                continue;
            }
            else if(number==7)
            {
                flag = 0;
                for(int i=0 ;i<strlen(input) ;i++)
                {
                    if(input[i]=='-')
                    {
                        flag = i;
                    }
                }
                char * attribute = nth_word(input+flag+1,1);

                if(strcmp(attribute,"all")==0)
                {
                    if(1==replace_all(address,str,str2))
                        printf("done\n");
                    else
                        printf("-1\n");
                    continue;
                }

                else if(strcmp(attribute,"at")==0)
                {
                    char * at_str = nth_word(input+flag+1+3,1);
                    at = 0;
                    for(int i=0; i<strlen(at_str); i++)
                    {
                        at *=10 ;
                        at += at_str[i]-'0';
                    }
                    if(1==replace(address,str,str2,at))
                        printf("done\n");
                    else
                        printf("-1\n");
                    continue;
                }
                else
                {
                    printf("invalid attribute");
                    continue;
                }
                continue;


           }
            else
            {
                printf("invalid input\n");
            }



        }
        else if(strcmp(command,"grep")==0) // grep [-c || -l]--str "sa" --files root/test.txt "root/fil e.txt"
        {
            int flag = 0;
            char attribute = 0;
            char * temp_attribute = nth_word(input,2);
            if(strcmp(temp_attribute,"-c")==0)
            {
                attribute = 'c';
                //printf("%c\n",attribute);
            }
            else if(strcmp(temp_attribute,"-l")==0)
            {
                attribute = 'l';
            }
            if(attribute!=0)
            {
                for(int i=5 ; i<strlen(input) ; i++)
                {
                    input[i] = input[i+3];
                }
            }
            char * str = first_str(input);
            //printf("%s\n",str);
            str =convert_input_str(str);
            int number = strlen("grep --str ") + strlen(str)+1;
            if(nth_word(input,3)[0]=='"')
            {
                number+=2;
            }
            char  * addresses[10000];

            int number_of_addresses = 0;
            /*
            for(int i= number ; i<strlen(input) ; i++)
            {
                if(strcmp2(input+i,"--files",strlen("--files"))==1)
                {
                    flag = i;
                    break;
                }
            }*/
            flag = number;
            addresses[0] = (first_str2(input+flag+strlen("--files ")));
            int flag3 = 0;
            if (addresses[0][0]=='/')
            {
                flag3 = 1;
            }
            addresses[0] += flag3;
            if(check_address(addresses[0])==0)
            {
                continue;
            }
            number = 0;
            if(input[flag+strlen("--files ")]=='"')
            {
                number +=2;
            }
            number += 1+ strlen(addresses[0])+flag + strlen("--files ")+flag3;
            //printf("%s\n",addresses[0]);
            number_of_addresses ++;
            int flag_continue = 0;
            while(number<strlen(input) && flag_continue==0)
            {
                addresses[number_of_addresses] = first_str2(input+number);
                flag3 = 0 ;
                if(addresses[number_of_addresses][0]=='/')
                {
                    flag3 =1;
                }

                addresses[number_of_addresses] += flag3;
                if(check_address(addresses[number_of_addresses])==0)
                {
                    flag_continue = 1;
                    break;
                }
                if(input[number]=='"')
                {
                    //printf("**");
                    number +=2;
                }
                number += 1+strlen(addresses[number_of_addresses])+flag3;
                //printf("%s\n",addresses[number_of_addresses]);
                number_of_addresses++;
            }
            if(flag_continue==1)
            {
                continue;
            }

            if(attribute==0)
            {
                simple_grep(str,number_of_addresses,addresses);
                continue;
            }
            else if(attribute=='c')
            {
                //printf("attribute c\n");
                printf("%d\n",count_grep(str,number_of_addresses,addresses));
                continue;
            }
            else if(attribute == 'l')
            {
                l_grep(str,number_of_addresses,addresses);
                continue;
            }

        }

        else
        {
            printf("invalid command\n");
        }
    }


}






int main()
{
    initialize();
    master();

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
char * read_file(char * address) // this is a valid address , return a string that shows what's in the file
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
    backup_a_file(address);
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
    backup_a_file(address);
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
    create_folder("./pre");
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
    backup_a_file(address);
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
    backup_a_file(address);
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
        if(str[i]=='\\' && str[i+1]=='"')
        {
            result[counter] = '"';
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
    else
    {
        return -1;
    }
}
char * nth_word(char * str,int n)
{
    char * result = (char *)malloc(strlen(str)*sizeof(char));
    int word_counter = 1;
    int counter=0;

    for (int i=0 ; i<strlen(str)+1 ; i++)
    {
        if(str[i] == ' '  || str[i]=='\0' || str[i]==EOF )
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
   // printf("*");
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
    char flag2 = 0;
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
                    flag2 = 1;
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
    if(flag2 == 0)
    {
        printf("-1\n");
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
    backup_a_file(address);
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
                        /*
                        for(int j=0 ; j<tabs+1 ;j++)
                        {
                            fprintf(file,"    ");
                        }
                        fprintf(file,"\n");
                        */
                    }

                    fprintf(file,"}");
                    pre_ch2 = pre_ch;
                    pre_ch = '}';
                }
                else
                {
                    if(i==0)
                    {
                        while(a_line[i]==' ')   {i++;}
                    }
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
void backup_a_file(char * address)
{
    int i = 0 ;
    while(strcmp2("root",address+i,4)==0)
    {
        i++;
    }
    i+=4;
    char * path = (char*)malloc(1000000);
    strcpy(path,"./pre");
    strcat(path,address+i);
    //printf("%s\n",path);

    char * temp  = (char*)malloc(strlen(path));
    int flag = 0;
    for(int i=0 ; i<strlen(path); i++)
    {
        if(path[i]=='/')
            flag = i;
        temp[i] = path[i];
    }
    temp[flag] = '\0';
    //printf("%s \n",temp);
    create_folder(temp);
    free(temp);

    FILE * pre = fopen(path,"w");
    FILE * file = fopen(address,"r");
    char ch = fgetc(file);
    while (ch!=EOF)
    {
        fprintf(pre,"%c",ch);
        ch = fgetc(file);
    }

    fclose(file);    fclose(pre);
}
void undo(char * address)
{
    int i = 0 ;
    while(strcmp2("root",address+i,4)==0)
    {
        i++;
    }
    i+=4;
    char * path = (char*)malloc(1000000);
    strcpy(path,"./pre");
    strcat(path,address+i);
    //printf("%s\n",path);

    FILE * temp = fopen("./temp/undo_temp.txt","w");
    FILE * file = fopen(address,"r");

    char ch = fgetc(file);
    while (ch!=EOF)
    {
        fprintf(temp,"%c",ch);
        ch = fgetc(file);
    }
    fclose(temp);    fclose(file);


    FILE * pre = fopen(path,"r");
    file = fopen(address,"w");
    ch = fgetc(pre);
    while (ch!=EOF)
    {
        fprintf(file,"%c",ch);
        ch = fgetc(pre);
    }
    fclose(pre);    fclose(file);


    pre = fopen(path,"w");
    temp = fopen("./temp/undo_temp.txt","r");
    ch = fgetc(temp);
    while (ch!=EOF)
    {
        fprintf(pre,"%c",ch);
        ch = fgetc(temp);
    }

    fclose(temp);    fclose(pre);

}
int find2(char * address , char * pattern,int number)// number = 1 for simple find
{
    char * strcopy = (char *)malloc(strlen(pattern));
    int j =0 ;
    int star_pos = -1;
    for(int i=0 ; i<strlen(pattern)+1 ; i++)
    {
        if(pattern[i]=='\\' && pattern[i+1]=='*')
        {
            strcopy[j]  = '*';
            i++;
        }
        else if(pattern[i]=='*' &&( i==1 || pattern[i-1]!='\\') )
        {
            strcopy[j] = '*';
            star_pos = j;

        }
        else
        {
            strcopy[j] = pattern[i];
        }
        j++;
    }


    if(star_pos==-1)
    {
        char * str = strcopy;
        int str_lenght = strlen(str);
        FILE * file = fopen(address,"r");
        char * a_line = (char*)malloc(1000000*sizeof(char));

        int char_before = 0;
        int main_result = -1;
        int counter = 0;
        while(fgets(a_line,1000000,file) != NULL)
        {
            int line_lenght = strlen(a_line);
            int result = -1;
            int flag = 0;

            for(int i= 0 ; i<line_lenght ; i++)
            {
                if(flag+counter == number)
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

            counter += flag;
            if(counter==number)
            {
                main_result = char_before + result;
                break;
            }

            char_before +=line_lenght;
        }

        fclose(file);

        return main_result;
    }

    else
    {
        /*
        char * str = strcopy;
        int str_lenght = strlen(str);
        FILE * file = fopen(address,"r");
        char * a_line = (char*)malloc(1000000*sizeof(char));
        int word_number = 1 + count_space(str);

       // printf("%d ",word_number);

        int char_before = 0;
        int main_result = -1;
        int counter = 0;
        while(fgets(a_line,1000000,file) != NULL)
        {
            int line_lenght = strlen(a_line);
           // printf("line_lenght %d ",line_lenght);
            int result = -1;
            int flag = 0;
            //printf("%d",count_space(a_line)+1);

            for(int k= 0 ; k<line_lenght ; k++)
            {

                //printf("k : %d , flag : %d \n",k,flag);
                if (flag+counter == number )
                {

                    //else{
                        break;
                   // }
                }

                int line_word_number = 1+ count_space(a_line+k);
                if(line_word_number < word_number)
                {
                    break;
                }

                int index = 0;
                char flag2 = 1;
                for(int i=1 ; i<= word_number; i++)
                {
                    if(flag2 == 0)
                    {
                        break;
                    }
                    char * pattern_word ;
                    pattern_word = nth_word(str,i);
                    char * line_word = nth_word(a_line+k,i);
                    line_word = nth_word(a_line+k,i);

                    //printf("%s  %s\n",pattern_word,line_word);


                    if( index == star_pos)
                    {
                        if(strcmp_beginning_with_star2(pattern_word,line_word)==0)
                        {
                            flag2 = 0;
                        }
                    }
                    else if(index + strlen(pattern_word)-1 == star_pos)
                    {
                        //bstar = 1;
                            //printf("k: %d i: %d flag2 : %d a_line : %s\n",k,i,flag2,a_line+k);
                        if(strcmp_ending_with_star2(pattern_word,line_word)==0)
                        {
                            flag2 = 0;
                        }

                    }
                    else
                    {
                        if(strcmp2(pattern_word,line_word,strlen(pattern_word))!=1)
                        {
                            flag2 = 0;
                        }
                        if(strlen(pattern_word)==0 && strlen(line_word)==0)
                        {
                            flag2 = 1;
                        }

                    }
                    index += strlen(pattern_word)+1;
                }
                //printf("%s %d\n",a_line+k,k);
                if (flag2 == 1)
                {
                    flag++;
                    result = k;
                }
            }
            counter += flag;
            if(counter == number)
            {
                main_result = char_before + result;
                break;
            }

            char_before += line_lenght;


        fclose(file);

        return main_result;
        */
        return -1;
    }
}
int count_space(char * str) // word number == space +1 ; " " -> "" , "";
{
    int counter =0 ;
    for(int i=0 ; str[i]!='\0' ; i++)
    {
        if (str[i]==' ')
        {
            counter++;
        }
    }
    return counter;
}
char strcmp_beginning_with_star2(char * str1 , char * str2)//first string has *
{
    str1++;
    int pattern_size = strlen(str1);
    int str2_size    = strlen(str2);
    if(strcmp2(str2,str1,pattern_size)==1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
char strcmp_ending_with_star2(char * str1 , char * str2)//first string has *
{
    int size = strlen(str1) -1;
    if(strcmp2(str1,str2,size) == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int convert2byword(int index ,char *address)
{
    if(index < 0)
    {
        return -1;
    }
    FILE * file = fopen(address,"r");
    int result = 0;
    char ch;
    for(int i=0 ; i<index ; i++)
    {
        ch = fgetc(file);
        if(ch == '\0')
        {
            break;
        }
        if (ch==' ' )
        {
            result++;
        }
    }
    fclose(file);
    return result+1;

}
int * find_all(char * address , char * pattern)
{
    int * result = (int*)malloc(1000000);
    int a;
    int i = 0;
    do
    {
        a = find2(address,pattern,i+1);
        //printf("(%d,%d)",a,i);
        result[i] = a;
        i++;
    }
    while (a!=-1);
    return result;


/*
    char * ch = (char*)malloc(100000);
    gets(ch);
    ch = convert_input_str(ch);

    int * result = find_all("root/test.txt",ch);
    int i = 0;
    while(result[i]!=-1)
    {
        printf("%d ",result[i]);
        i++;
    }
*/
}
char replace(char * address , char * pattern ,char * str, int number) // return 1 for success and 0 for failure
{
    backup_a_file(address);
    int a = find2(address,pattern,number);
    if (a==-1)
    {
        return 0;
    }
    else
    {
        int lenght = strlen(pattern);
        remove_by_pos_for_replace(address,a,lenght,'f');
        insert_by_pos_for_replace(address,a,str);
        return 1;
    }


}
void remove_by_pos_for_replace(char* address ,int pos ,int size , char direction )
{
    //backup_a_file(address);
    FILE * file1 = fopen(address,"r");
    FILE * file2 = fopen("./temp/temp_remove.txt","w");
    int char_before_removing = pos;
    char ch;
    while((ch=fgetc(file1))!=EOF)
    {
        fprintf(file2,"%c",ch);
    }
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
void insert_by_pos_for_replace(char * address, int pos,char * inserting_str) // must first convert the input string
{
    //backup_a_file(address);
    FILE * file1 = fopen(address,"r");
    FILE * file2 = fopen("./temp/temp_insert.txt","w");
    //char * inserting_str = convert_input_str(inserting_str0);
    char ch;
    int line=1 ;
    int i =0 ;
    int is_inserted = 0;
    while ((ch=fgetc(file1)) != EOF)
    {
        if(i == pos && is_inserted == 0)
        {
            fprintf(file2,"%s",inserting_str);
            is_inserted =1 ;
        }
        if(ch=='\n')
        {
            line++;
        }
        i++;
        fprintf(file2,"%c",ch);
    }
    if(is_inserted == 0)
    {


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
char replace_all(char * address , char * pattern ,char * str)
{
    backup_a_file(address);
    int i=0;
    while(1){
        int a = find2(address,pattern,1);
        if (a==-1)
        {
            return (i!=0);
        }
        else
        {
            int lenght = strlen(pattern);
            remove_by_pos_for_replace(address,a,lenght,'f');
            insert_by_pos_for_replace(address,a,str);
            //return 1;
        }
        i++;
    }


}
void cat_print(char * address) // this is a valid address
{
    char ch;
    FILE * file = fopen(address,"r");
    do {
        ch = fgetc(file);
        printf("%c",ch);
    } while (ch != EOF);
    fclose(file);

}

//---------------------------------------arman-------------------------------------------------------------------------------------------------
void insert_input_arman(char * address,int line_number , int start_pos,char * input_file_address) // must first convert the input string
{
    backup_a_file(address);
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
            FILE * file3 = fopen(input_file_address,"r");
            char ch1=fgetc(file3) ;
            while(ch1!=EOF)
            {
                fprintf(file2,"%c",ch1);
                ch1=fgetc(file3);
            }
            fclose(file3);
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
            FILE * file3 = fopen(input_file_address,"r");
            char ch1=fgetc(file3) ;
            while(ch1!=EOF)
            {
                fprintf(file2,"%c",ch1);
                ch1=fgetc(file3);
            }
            fclose(file3);
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
int find2_output_arman(char * address , char * pattern,int number)// number = 1 for simple find
{
    char * strcopy = (char *)malloc(strlen(pattern));
    int j =0 ;
    int star_pos = -1;
    for(int i=0 ; i<strlen(pattern)+1 ; i++)
    {
        if(pattern[i]=='\\' && pattern[i+1]=='*')
        {
            strcopy[j]  = '*';
            i++;
        }
        else if(pattern[i]=='*' &&( i==1 || pattern[i-1]!='\\') )
        {
            strcopy[j] = '*';
            star_pos = j;

        }
        else
        {
            strcopy[j] = pattern[i];
        }
        j++;
    }


    if(star_pos==-1)
    {
        char * str = strcopy;
        int str_lenght = strlen(str);
        FILE * file = fopen(address,"r");
        char * a_line = (char*)malloc(1000000*sizeof(char));

        int char_before = 0;
        int main_result = -1;
        int counter = 0;
        while(fgets(a_line,1000000,file) != NULL)
        {
            int line_lenght = strlen(a_line);
            int result = -1;
            int flag = 0;

            for(int i= 0 ; i<line_lenght ; i++)
            {
                if(flag+counter == number)
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

            counter += flag;
            if(counter==number)
            {
                main_result = char_before + result;
                break;
            }

            char_before +=line_lenght;
        }

        fclose(file);

        FILE * file22 = fopen("./temp/temp_arman.txt","w");
        fprintf(file22,"%d",main_result);
        fclose(file22);
        return main_result;
    }

    else
    {
        /*
        char * str = strcopy;
        int str_lenght = strlen(str);
        FILE * file = fopen(address,"r");
        char * a_line = (char*)malloc(1000000*sizeof(char));
        int word_number = 1 + count_space(str);

       // printf("%d ",word_number);

        int char_before = 0;
        int main_result = -1;
        int counter = 0;
        while(fgets(a_line,1000000,file) != NULL)
        {
            int line_lenght = strlen(a_line);
           // printf("line_lenght %d ",line_lenght);
            int result = -1;
            int flag = 0;
            //printf("%d",count_space(a_line)+1);

            for(int k= 0 ; k<line_lenght ; k++)
            {

                //printf("k : %d , flag : %d \n",k,flag);
                if (flag+counter == number )
                {

                    //else{
                        break;
                   // }
                }

                int line_word_number = 1+ count_space(a_line+k);
                if(line_word_number < word_number)
                {
                    break;
                }

                int index = 0;
                char flag2 = 1;
                for(int i=1 ; i<= word_number; i++)
                {
                    if(flag2 == 0)
                    {
                        break;
                    }
                    char * pattern_word ;
                    pattern_word = nth_word(str,i);
                    char * line_word = nth_word(a_line+k,i);
                    line_word = nth_word(a_line+k,i);

                    //printf("%s  %s\n",pattern_word,line_word);


                    if( index == star_pos)
                    {
                        if(strcmp_beginning_with_star2(pattern_word,line_word)==0)
                        {
                            flag2 = 0;
                        }
                    }
                    else if(index + strlen(pattern_word)-1 == star_pos)
                    {
                        //bstar = 1;
                            //printf("k: %d i: %d flag2 : %d a_line : %s\n",k,i,flag2,a_line+k);
                        if(strcmp_ending_with_star2(pattern_word,line_word)==0)
                        {
                            flag2 = 0;
                        }

                    }
                    else
                    {
                        if(strcmp2(pattern_word,line_word,strlen(pattern_word))!=1)
                        {
                            flag2 = 0;
                        }
                        if(strlen(pattern_word)==0 && strlen(line_word)==0)
                        {
                            flag2 = 1;
                        }

                    }
                    index += strlen(pattern_word)+1;
                }
                //printf("%s %d\n",a_line+k,k);
                if (flag2 == 1)
                {
                    flag++;
                    result = k;
                }
            }
            counter += flag;
            if(counter == number)
            {
                main_result = char_before + result;
                break;
            }

            char_before += line_lenght;


        fclose(file);

        return main_result;
        */
        return -1;
    }
}
int find2_input_arman(char * address , char * pattern_address,int number)// number = 1 for simple find
{
    FILE * file_temp = fopen(pattern_address,"r");
    char * pattern = (char *)malloc(1000000);
    int i_temp = 0;
    int n_temp = 1;
    char ch_temp = fgetc(file_temp);
    while(ch_temp!=EOF)
    {
        if(i_temp%1000000==0 && i_temp!=0)
        {
            pattern = (char *)realloc((void*)pattern,n_temp*1000000);
            n_temp++;
        }
        pattern[i_temp] = ch_temp;
        i_temp++;
        ch_temp = fgetc(file_temp);
    }
    pattern[i_temp] = '\0';
    fclose(file_temp);

    char * strcopy = (char *)malloc(strlen(pattern));
    int j =0 ;
    int star_pos = -1;
    for(int i=0 ; i<strlen(pattern)+1 ; i++)
    {
        if(pattern[i]=='\\' && pattern[i+1]=='*')
        {
            strcopy[j]  = '*';
            i++;
        }
        else if(pattern[i]=='*' &&( i==1 || pattern[i-1]!='\\') )
        {
            strcopy[j] = '*';
            star_pos = j;

        }
        else
        {
            strcopy[j] = pattern[i];
        }
        j++;
    }


    if(star_pos==-1)
    {
        char * str = strcopy;
        int str_lenght = strlen(str);
        FILE * file = fopen(address,"r");
        char * a_line = (char*)malloc(1000000*sizeof(char));

        int char_before = 0;
        int main_result = -1;
        int counter = 0;
        while(fgets(a_line,1000000,file) != NULL)
        {
            int line_lenght = strlen(a_line);
            int result = -1;
            int flag = 0;

            for(int i= 0 ; i<line_lenght ; i++)
            {
                if(flag+counter == number)
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

            counter += flag;
            if(counter==number)
            {
                main_result = char_before + result;
                break;
            }

            char_before +=line_lenght;
        }

        fclose(file);

        return main_result;
    }

    else
    {
        /*
        char * str = strcopy;
        int str_lenght = strlen(str);
        FILE * file = fopen(address,"r");
        char * a_line = (char*)malloc(1000000*sizeof(char));
        int word_number = 1 + count_space(str);

       // printf("%d ",word_number);

        int char_before = 0;
        int main_result = -1;
        int counter = 0;
        while(fgets(a_line,1000000,file) != NULL)
        {
            int line_lenght = strlen(a_line);
           // printf("line_lenght %d ",line_lenght);
            int result = -1;
            int flag = 0;
            //printf("%d",count_space(a_line)+1);

            for(int k= 0 ; k<line_lenght ; k++)
            {

                //printf("k : %d , flag : %d \n",k,flag);
                if (flag+counter == number )
                {

                    //else{
                        break;
                   // }
                }

                int line_word_number = 1+ count_space(a_line+k);
                if(line_word_number < word_number)
                {
                    break;
                }

                int index = 0;
                char flag2 = 1;
                for(int i=1 ; i<= word_number; i++)
                {
                    if(flag2 == 0)
                    {
                        break;
                    }
                    char * pattern_word ;
                    pattern_word = nth_word(str,i);
                    char * line_word = nth_word(a_line+k,i);
                    line_word = nth_word(a_line+k,i);

                    //printf("%s  %s\n",pattern_word,line_word);


                    if( index == star_pos)
                    {
                        if(strcmp_beginning_with_star2(pattern_word,line_word)==0)
                        {
                            flag2 = 0;
                        }
                    }
                    else if(index + strlen(pattern_word)-1 == star_pos)
                    {
                        //bstar = 1;
                            //printf("k: %d i: %d flag2 : %d a_line : %s\n",k,i,flag2,a_line+k);
                        if(strcmp_ending_with_star2(pattern_word,line_word)==0)
                        {
                            flag2 = 0;
                        }

                    }
                    else
                    {
                        if(strcmp2(pattern_word,line_word,strlen(pattern_word))!=1)
                        {
                            flag2 = 0;
                        }
                        if(strlen(pattern_word)==0 && strlen(line_word)==0)
                        {
                            flag2 = 1;
                        }

                    }
                    index += strlen(pattern_word)+1;
                }
                //printf("%s %d\n",a_line+k,k);
                if (flag2 == 1)
                {
                    flag++;
                    result = k;
                }
            }
            counter += flag;
            if(counter == number)
            {
                main_result = char_before + result;
                break;
            }

            char_before += line_lenght;


        fclose(file);

        return main_result;
        */
        return -1;
    }
}
int * find_all_output_arman(char * address , char * pattern)
{
    int * result = (int*)malloc(1000000);
    int a;
    int i = 0;
    do
    {
        a = find2(address,pattern,i+1);
       // printf("(%d,%d)",a,i);
        result[i] = a;
        i++;
    }
    while (a!=-1);

    FILE * file_temp = fopen("./temp/temp_arman.txt","w");
    i = 0;
    while(result[i]!=-1)
    {
        fprintf(file_temp,"%d ",result[i]);
        i++;
    }
    fclose(file_temp);

    return result;


}
int * find_all_input_arman(char * address , char * pattern_address)
{
    int * result = (int*)malloc(1000000);
    int a;
    int i = 0;
    do
    {
        a = find2_input_arman(address,pattern_address,i+1);
       // printf("(%d,%d)",a,i);
        result[i] = a;
        i++;
    }
    while (a!=-1);
    return result;


/*
    char * ch = (char*)malloc(100000);
    gets(ch);
    ch = convert_input_str(ch);

    int * result = find_all("root/test.txt",ch);
    int i = 0;
    while(result[i]!=-1)
    {
        printf("%d ",result[i]);
        i++;
    }
*/
}
char replace_input_arman(char * address , char * pattern_address ,char * str, int number) // return 1 for success and 0 for failure
{
    FILE * file_temp = fopen(pattern_address,"r");
    char * pattern = (char *)malloc(1000000);
    int i_temp = 0;
    int n_temp = 1;
    char ch_temp = fgetc(file_temp);
    while(ch_temp!=EOF)
    {
        if(i_temp%1000000==0 && i_temp!=0)
        {
            pattern = (char *)realloc((void*)pattern,n_temp*1000000);
            n_temp++;
        }
        pattern[i_temp] = ch_temp;
        i_temp++;
        ch_temp = fgetc(file_temp);
    }
    pattern[i_temp] = '\0';
    fclose(file_temp);

    backup_a_file(address);
    int a = find2(address,pattern,number);
    if (a==-1)
    {
        return 0;
    }
    else
    {
        int lenght = strlen(pattern);
        remove_by_pos_for_replace(address,a,lenght,'f');
        insert_by_pos_for_replace(address,a,str);
        return 1;
    }


}
char replace_all_input_arman(char * address , char * pattern_address ,char * str)
{
    FILE * file_temp = fopen(pattern_address,"r");
    char * pattern = (char *)malloc(1000000);
    int i_temp = 0;
    int n_temp = 1;
    char ch_temp = fgetc(file_temp);
    while(ch_temp!=EOF)
    {
        if(i_temp%1000000==0 && i_temp!=0)
        {
            pattern = (char *)realloc((void*)pattern,n_temp*1000000);
            n_temp++;
        }
        pattern[i_temp] = ch_temp;
        i_temp++;
        ch_temp = fgetc(file_temp);
    }
    pattern[i_temp] = '\0';
    fclose(file_temp);

    backup_a_file(address);
    int i=0;
    while(1){
        int a = find2(address,pattern,1);
        if (a==-1)
        {
            return (i!=0);
        }
        else
        {
            int lenght = strlen(pattern);
            remove_by_pos_for_replace(address,a,lenght,'f');
            insert_by_pos_for_replace(address,a,str);
            //return 1;
        }
        i++;
    }
}
void simple_grep_input_arman(char * str_address ,int n ,char * addresses[n]) // n : number of files
{
    FILE * file_temp = fopen(str_address,"r");
    char * str = (char *)malloc(1000000);
    int i_temp = 0;
    int n_temp = 1;
    char ch_temp = fgetc(file_temp);
    while(ch_temp!=EOF)
    {
        if(i_temp%1000000==0 && i_temp!=0)
        {
            str = (char *)realloc((void*)str,n_temp*1000000);
            n_temp++;
        }
        str[i_temp] = ch_temp;
        i_temp++;
        ch_temp = fgetc(file_temp);
    }
    str[i_temp] = '\0';
    fclose(file_temp);


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
void simple_grep_output_arman(char * str ,int n ,char * addresses[n]) // n : number of files
{
    FILE * file_temp = fopen("./temp/temp_arman.txt","w");
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
                    fprintf(file_temp,"%s: %s",addresses[j],a_line);
                    if(a_line[line_lenght-1]!='\n')
                    {
                        fprintf(file_temp,"\n");
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
        fprintf(file_temp,"-1\n");
    }
    fclose(file_temp);
}
void l_grep_input_arman(char * str_address , int n , char * addresses[n])
{
    FILE * file_temp = fopen(str_address,"r");
    char * str = (char *)malloc(1000000);
    int i_temp = 0;
    int n_temp = 1;
    char ch_temp = fgetc(file_temp);
    while(ch_temp!=EOF)
    {
        if(i_temp%1000000==0 && i_temp!=0)
        {
            str = (char *)realloc((void*)str,n_temp*1000000);
            n_temp++;
        }
        str[i_temp] = ch_temp;
        i_temp++;
        ch_temp = fgetc(file_temp);
    }
    str[i_temp] = '\0';
    fclose(file_temp);

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
void l_grep_output_arman(char * str , int n , char * addresses[n])
{
    FILE * file_temp = fopen("./temp/temp_arman.txt","w");
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
                    fprintf(file_temp,"%s\n",addresses[j]);
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
        fclose(file_temp);
    }
}
int count_grep_input_arman  (char * str_address ,int n ,char * addresses[n])
{
    FILE * file_temp = fopen(str_address,"r");
    char * str = (char *)malloc(1000000);
    int i_temp = 0;
    int n_temp = 1;
    char ch_temp = fgetc(file_temp);
    while(ch_temp!=EOF)
    {
        if(i_temp%1000000==0 && i_temp!=0)
        {
            str = (char *)realloc((void*)str,n_temp*1000000);
            n_temp++;
        }
        str[i_temp] = ch_temp;
        i_temp++;
        ch_temp = fgetc(file_temp);
    }
    str[i_temp] = '\0';
    fclose(file_temp);


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
int count_grep_output_arman  (char * str ,int n ,char * addresses[n])
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
    FILE * file_temp=fopen("temp/temp_arman.txt","w");
    fprintf(file_temp,"%d",counter);
    fclose(file_temp);
    return counter;

}
char tree_output_arman_komaki(char * path, int depth_level , int final_depth , FILE * file_temp)
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
            fprintf(file_temp,"|  ");
        }
        fprintf(file_temp,"|__%s\n",file->d_name);

        char * file_path = (char *)malloc(1000000);
        strcpy(file_path,path);
        if(file_path[strlen(path)-1]!='/')
        {
            strcat(file_path,"/");
        }
        strcat(file_path,file->d_name);
        tree_output_arman_komaki(file_path,depth_level+1,final_depth,file_temp);

    }

return 1;
}//tree("./root/",0,2);
void tree_output_arman(char * path, int depth_level , int final_depth )
{
    FILE * file = fopen("./temp/temp_arman.txt","w");
    tree_output_arman_komaki(path,depth_level,final_depth,file);
    fclose(file);
}
void line_compare_output_arman(char * address1 , char * address2)
{

    FILE * file_temp = fopen("./temp/temp_arman.txt","w");

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
            fprintf(file_temp,"============ #%d ============\n",line);
            fprintf(file_temp,"%s",str1);
            fprintf(file_temp,"%s",str2);

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
        fprintf(file_temp,"<<<<<<<<<<<< #%d - #%d<<<<<<<<<<<<\n",start_line,finish_line);

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
            fprintf(file_temp,"%s",str1);
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
        fprintf(file_temp,">>>>>>>>>>>> #%d - #%d>>>>>>>>>>>>\n",start_line,finish_line);

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
            fprintf(file_temp,"%s",str2);
        }
        fclose(file2);
        return;
    }


    fclose(file1);  fclose(file2);
    fclose(file_temp);
}//line_compare("./root/test2.txt","./root/test.txt");
char * convert_input_address(char * str)
{
    char * result = (char *)malloc((strlen(str)+1)*sizeof(char));
    int i=0;
    int counter = 0;
    while(i<strlen(str)+1 && str[i-1] != '\0')
    {
        if(str[i]=='\\' && str[i+1]=='"')
        {
            result[counter] = '"';
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
//---------------------------------------
char check_folder_address(char * address)
{
    DIR* dir = opendir(address);
    if (dir) {
        closedir(dir);
        return 1;
    }
    else if (ENOENT == errno) {
        return 0;
    }
}
char check_file_address(char* address)
{
    FILE *file;
    if ((file = fopen(address, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}
char * first_str(char*str)
{
    char * result = (char * )calloc(strlen(str),1);
    strcpy(result,str);
    //printf("%s\n",result);
    int flagg = -1;
    for(int i=0 ; i<strlen(str) ; i++)
    {
        if(str[i]=='-')
        {
            flagg = i;
            break;
        }
    }
    result += flagg;
    //printf("*");
    result += strlen(nth_word(result,1))+1;

    if(result[0]=='"')
    {
        result++;
        for(int i=1 ; i<strlen(result) ; i++)
        {
            if(result[i]=='"' && result[i-1]!='\\')
            {
                flagg = i;
                break;
            }
        }
        result[flagg]='\0';
    }
    else
    {
        for(int i=1 ; i<strlen(result) ; i++)
        {
            if(result[i]==' ')
            {
                flagg = i;
                break;
            }
        }
        result[flagg]='\0';

    }
    return result;
}
char * first_str2(char*str)
{
    char * result = (char * )malloc(strlen(str));
    strcpy(result,str);
    int flag = -1;

    if(result[0]=='"')
    {
        result++;
        for(int i=1 ; i<strlen(result) ; i++)
        {
            if(result[i]=='"' && result[i-1]!='\\')
            {
                flag = i;
                break;
            }
        }
        result[flag]='\0';
    }
    else
    {
        for(int i=1 ; i<strlen(result) ; i++)
        {
            if(result[i]==' ')
            {
                flag = i;
                break;
            }
        }
        result[flag]='\0';

    }
    return result;
}
int count_in_str(char * str , char ch)
{
    int a = 0;
    for(int i=0; i<strlen(str) ; i++)
    {
        if(str[i]==ch)
        {
            a++;
        }
    }
    return a;
}
char check_address(char * address)
{
    char * temp  = (char*)malloc(strlen(address));
    int flag = 0;
    for(int i=0 ; i<strlen(address); i++)
    {
        if(address[i]=='/')
            flag = i;
        temp[i] = address[i];
    }
    temp[flag] = '\0';
    //printf("folder : %s\n",temp);
    //printf("file   : %s\n",address);
    if(check_folder_address(temp)==0)
    {
        printf("invalid address\n");
        return 0;
    }
    if(check_file_address(address)==0)
    {
        printf("invalid file name\n");
        return 0;
    }
    return 1;
}

