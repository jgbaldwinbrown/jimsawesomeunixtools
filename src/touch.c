#include <stdio.h>

int main(int argc, char *argv[]){
    FILE *fp;
    fp = fopen(argv[1],"r+");
    fclose(fp);
    return 0;
}
