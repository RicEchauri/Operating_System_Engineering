  
int main(int argc, char **argv)
{
    char *p; //pointer 
    char *path;
    path="ho/la";

    for(p=path+strlen(path); p >= path && *p != '/'; p--)
    {
        printf("%s\n",p); 
    }
    
    p++;
    printf("%s\n",p);
    return 0;
}
