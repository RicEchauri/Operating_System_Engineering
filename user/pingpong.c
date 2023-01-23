#include "kernel/types.h"
#include "user/user.h"

int main(int argc,char **argv)
{
    int pid;
    char buf[4];
    int fb_parent[2];
    int fb_chield[2];    
    pipe(fb_parent);   
    pipe(fb_chield);

    pid = fork();

    if(pid > 0)//Parent
    { 
        write(fb_parent[1], "ping", sizeof buf);                  
        read(fb_chield[0], buf, sizeof buf);    
        printf("pid: %d. received: %s\n", getpid, buf);

    }else if(pid==0)//Child
    { 
        read(fb_parent[0], buf, sizeof buf);      
        printf("pid: %d. received: %s\n", getpid, buf);
        write(fb_chield[1], "pong", sizeof buf);                
    }else{ //Error
        printf("Fork error\n");
    }
    exit(0);
}

