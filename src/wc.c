#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main(int argc, char *argv[]){
    int nc = 0;
    int nf = 0;
    int nr = 0;
    char *line;
    size_t bufsize = 32;
    ssize_t nread = 0;
    line = (char *)malloc(bufsize * sizeof(char));
    while ((nread = getline(&line, &bufsize, stdin)) != -1)
    {
        nc += strlen(line);
        char *token = strtok(line, " ");
        while (token != NULL)
        {
            nf++;
            token = strtok(NULL, " ");
        }
        nr++;
    }
    free(line);
    printf("%d\t%d\t%d", nr, nf, nc);
    return 0;
}

/*
int main()
{
    char str[] = "Geeks-for-Geeks";
 
    // Returns first token 
    char *token = strtok(str, "-");
   
    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (token != NULL)
    {
        printf("%s\n", token);
        token = strtok(NULL, "-");
    }
 
    return 0;
}
*/
