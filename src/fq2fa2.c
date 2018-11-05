#include <stdio.h>

int main() {
    char *line = NULL;
    int findex = 0;
    size_t size;
    
    while (getline(&line, &size, stdin) != -1) {
        findex++;
        if (findex%4 == 1) {
            printf(">%s", line+1);
        }
        if (findex%4 == 2) {
            printf("%s",line);
        }
    } 
    return(0);
}
