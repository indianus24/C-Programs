#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main ()
{
   pid_t pid;
   int status;
   pid=fork();
   FILE *file_pointer;

   char ch;
   char str[100];
   char res_str[100];
   file_pointer=fopen("file.csv","r");
   if(file_pointer==NULL)
   {
      fprintf(stderr,"File cannot be open");
      return 0;
   }
   if(pid<0)
   {
      fprintf(stderr,"Fork Failed");
      return 1;
   }
   else if (pid==0)
   {  
      printf("Child process \n");
      while (1)
      {
        ch=fgetc(file_pointer);
        strncat(str,&ch,1);
        if (ch==EOF)
            break;
        else
         {
            strncat(str,&ch,1);
            while (ch!='\n')
            {
               ch=fgetc(file_pointer);
               if (ch==EOF)
                    break;
               if(ch !='\n')
                  strncat(str,&ch,1);
            }
            int a_as=0;
            strcpy(res_str,str);
            char * token = strtok(str, ",");
            int counter=0;
            while( token != NULL ) {
               if(counter==1)
               {
                  if(strcmp(token,"A"))
                     break;
               }
               if(counter!=0 && counter!=1)
                  a_as+=atoi(token);
               token = strtok(NULL, ",");
               counter+=1;
            }
            float ans=a_as/(float)4;
            if (ans!=0)
            {
               printf("Average: %f \n",ans);
               printf("%s \n",res_str);
            }
            strcpy(str,""); 
         } 
      }   
      printf("Child process ended \n");   
      exit(EXIT_SUCCESS);
   }
   else
   {
      fseek(file_pointer, 0, SEEK_SET);
      waitpid(pid,&status,0);
      printf("\n \n");
      while (1)
      {
        ch=fgetc(file_pointer);
        strncat(str,&ch,1);
        if (ch==EOF)
            break;
        else
         {
            strncat(str,&ch,1);
            while (ch!='\n')
            {
               ch=fgetc(file_pointer);
               if (ch==EOF)
                    break;
               if(ch !='\n')
                  strncat(str,&ch,1);
            }
            int b_as=0;
            strcpy(res_str,str);
            char * token = strtok(str, ",");
            int counter=0;
            while( token != NULL ) {
               if(counter==1)
               {
                  if(strcmp(token,"B"))
                     break;
               }
               if(counter!=0 && counter!=1)
                  b_as+=atoi(token);
               token = strtok(NULL, ",");
               counter+=1;
            }
            float ans=b_as/(float)4;
            if (ans!=0)
            {
               printf("Average: %f \n",ans);
               printf("%s \n",res_str);
            }
            strcpy(str,""); 
         } 
      }
      printf("Parent Process Over \n");
   }
   fclose(file_pointer);
   return 0;
}