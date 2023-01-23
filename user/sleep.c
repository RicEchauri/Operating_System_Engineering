#include "kernel/types.h"
#include "user/user.h"

int 
main(int argc,char **argv)
{
    if (argc > 1){
        int ticks;
        ticks=atoi(argv[1]);
        sleep(ticks);
        exit(0);
    }else{
        printf("Please enter a number of ticks that you want to sleep\n");
        exit(0);
    }
    
}