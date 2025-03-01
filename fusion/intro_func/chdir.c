#include <unistd.h>
#include <stdio.h>

int main(void)
{
    char *pwd;
    
    pwd = getcwd(NULL, 0);
    printf("pwd before chdir: %s\n", pwd);
    chdir("/home/tat-nguy/42rendu");
    pwd = getcwd(NULL, 0);
    printf("pwd after chdir: %s\n", pwd);
    return (0);
}
