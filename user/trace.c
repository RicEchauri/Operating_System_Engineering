
#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char **argv) {
    char *nargv[MAXARG];

    trace(atoi(argv[1]));
    
    for(int idx = 2; idx < argc && idx < MAXARG; idx++){    
    	nargv[idx-2] = argv[idx];
    }
    exec(nargv[0], nargv);
    exit(0);
}