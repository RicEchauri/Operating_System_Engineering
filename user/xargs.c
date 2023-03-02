#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
#define TRUE 1

int main(int argc,char **argv)
{
  char *arg_array[MAXARG];
  char current_char=0;
  char buf[MAXARG];
  int arg_count=0;
  int num_byts_readed=1;
  
  for (int idx=1; idx<argc; idx++)
  {
    arg_array[arg_count++]=argv[idx];
  }
  while (num_byts_readed)
  {
    int pos=0;
    int pos_1=0;
    while(TRUE)
    {
      num_byts_readed=read(0, &current_char, 1);
      if(num_byts_readed==0)
      {
        exit(0);
      }
      if(current_char==' ')
      {
        buf[pos++]=0;
        arg_array[arg_count++] = &buf[pos_1];
        pos_1=pos;
      }else if(current_char=='\n')
      {
        arg_array[arg_count++] = &buf[pos_1];
        pos_1=pos; 
      }else
      {
        buf[pos++]=current_char;
        break;
      }
      
    }
     if(fork()==0)
     {
       exec(arg_array[0],arg_array);
     }else
     {
       wait(0);
     }
  }
  exit(0);
}
