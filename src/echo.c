#include <stdio.h>

int main(int argc, char *argv[]){
    if (argc >= 2)
    {
        printf("%s",argv[1]);
    }
    if (argc >= 3)
    {
        for(int i=2; i<argc; i++)
        {
            printf(" %s",argv[i]);
        }
    }
}
