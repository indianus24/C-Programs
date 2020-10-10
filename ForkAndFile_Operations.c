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
      printf("Parent Process Over \n");
   }
   fclose(file_pointer);
   return 0;
}
