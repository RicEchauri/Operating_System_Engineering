#include "kernel/types.h"
#include "user/user.h"

#define MAX_NUMBER 35
#define READ 0
#define WRITE 1
#define STANDAR_OUTPUT_DEVICE 1

void prime_process(int fb_left[2]);

int main(int argc,char **argv)
{
    int number;
    int pid;   
    int fb_primes[2];

    number=2;
    pipe(fb_primes);
    pid=fork();

    if (pid > 0)
    {
        close(fb_primes[READ]);
        for (;number<=MAX_NUMBER;number++)
        {
            write(fb_primes[WRITE],&number,sizeof(int));
        }
        close(fb_primes[WRITE]);
        wait(0);
    }else
    {
        prime_process(fb_primes);
    }
    exit(0);
}

void prime_process(int fb_left[2])
{
    close(fb_left[WRITE]);
    int fb_rigth[2];
    int pid;
    int new_prime;
    int number_passed_filter;

    if (read(fb_left[READ], &new_prime, sizeof(int)) == 0) 
    {
        printf("didnt receive any numbers\n");
        close(fb_left[READ]);
        exit(0);
    }
    fprintf(STANDAR_OUTPUT_DEVICE, "prime %d\n", new_prime);
    pipe(fb_rigth);
    pid=fork();

    if (pid>0)
    {
         while (read(fb_left[READ], &number_passed_filter, sizeof(int)) != 0) 
        {
            if(number_passed_filter % new_prime != 0)// non-divisible by current number, prime suspicious
            {
                write(fb_rigth[WRITE], &number_passed_filter, sizeof(int));
            }
        }
        // close filedescriptors and wait for child (right processes) to finish
        close(fb_left[READ]);
        close(fb_rigth[WRITE]);
        wait(0); 
    }else {
        prime_process(fb_rigth);
    }
    exit(0);
}