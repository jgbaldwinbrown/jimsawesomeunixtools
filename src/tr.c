#include <stdio.h>

char sub(char in, char test, char out){
    if (in == test)
    {
        return out;
    }
    else
    {
        return in;
    }
}

int main(int argc, char *argv[]){
    char a;
    while((a = getchar()) != EOF) {
        printf("%c",sub(a,argv[1][0],argv[2][0]));
    }
    return 0;
}
