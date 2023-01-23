#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char *path) //function that recive and return a string 
{
    //DIRSIZ = 14
  static char buf[DIRSIZ+1]; //string with size of 14+1 
  char *p; //pointer 

  // Find first character after last slash.
  //strlen()=return the size of a string 
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
    //memmove(destination,source,): copy a block of memory of a ubication to another
  memmove(buf, p, strlen(p));
  //memset()= set a whole block of memory to a particular value
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));//set a value of ' ' on all the sapaces of buf that have not a value
  return buf;
}

void
ls(char *path)
{
  char buf[512], *p;
  int fd;   //file descriptor: int value that will return open 
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){  // if fd return a -1 value it's because fd could open the file
    //file descriptor= 2 =stderr standar error, 
    //fprintf(file descriptor,"%s %d\n", nombre, numero) = write a character on the file descriptor 
    fprintf(2, "ls: cannot open %s\n", path); //rewrite de standar error to what i want
    return;
  }
    //stat gives you a status information about a file 
    //fstat works like stat but instead of use filename use a file descriptor
  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }
    //switc=selector whit a conditional int or char 
  switch(st.type){ //swict depending the type of file of st 

  case T_FILE: //T_FILE = 2
    
    printf("%s %d %d %l\n", fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR: //T_DIR = 1
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;                                                                                                                                                                                                                                                                                    
    }
    strcpy(buf, path); //copia el contenido de path al buff
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){ //read(); return the number of characters readed 
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      printf("%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  int i;

  if(argc < 2){
    ls(".");
    exit(0);
  }
  for(i=1; i<argc; i++)
    ls(argv[i]);
  exit(0);
}
