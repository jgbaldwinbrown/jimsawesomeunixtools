#include <stdio.h>

int main(int argc, char *argv[]){
    FILE *f1;
    FILE *f2;
    char c1;
    char c2;
    
    f1 = fopen(argv[1],"r");
    f2 = fopen(argv[2],"r");
    
    while((c1=fgetc(f1)) != EOF)
    {
        if ((c2=fgetc(f2)) != EOF)
        {
            if (c1 != c2)
            {
                puts("File 1 and file 2 differ!");
                return(1);
            }
        } else {
            puts("File 2 is shorter than file 1!");
        }
    }
    puts("File 1 and file 2 match!");
    return(0);
}
