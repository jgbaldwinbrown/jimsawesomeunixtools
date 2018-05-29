#include <stdio.h>

int main(int argc, char *argv[]){
    int nr = 0;
    char *line;
    size_t bufsize = 32;
    ssize_t nread = 0;
    int headnum = atoi(argv[1]);
    line = (char *)malloc(bufsize * sizeof(char));
    while ((nread = getline(&line, &bufsize, stdin)) != -1)
    {
        if (nr <= headnum - 1)
        {
            printf("%s",line);
        }
        nr++;
    }
    free(line);
    return 0;
}
