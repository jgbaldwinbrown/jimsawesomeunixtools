#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int new_index(int index, int size){
    return (index + 1) % size;
}

int main(int argc, char *argv[]){
    char *line;
    size_t bufsize = 32;
    ssize_t nread = 0;
    int tailnum = atoi(argv[1]);
    char *lines[tailnum];
    int queueindex = 0;
    for (int i=0; i<tailnum; i++)
    {
        lines[i] = (char *)malloc(strlen("")+1);
        strcpy(lines[i],"");
    }
    line = (char *)malloc(bufsize * sizeof(char));
    while ((nread = getline(&line, &bufsize, stdin)) != -1)
    {
        if (strlen(lines[queueindex]) < strlen(line))
        {
            lines[queueindex] = (char*)realloc(lines[queueindex],strlen(line));
        }
        strcpy(lines[queueindex],line);
        queueindex = new_index(queueindex,tailnum);
    }
    free(line);
    for (int i=0; i<tailnum; i++)
    {
        printf("%s",lines[queueindex]);
        queueindex = new_index(queueindex,tailnum);
    }
    return 0;
}
