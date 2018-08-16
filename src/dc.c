#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void push(long double *stack, int sindex, int stacksize, long double value){
    if (sindex >= stacksize)
    {
        puts("Stack overflow!");
        exit(1);
    }
    if (sindex >= (stacksize - 1))
    {
        stacksize = stacksize * 2;
        stack = (long double *)realloc(stack,sizeof(long double) * stacksize);
    }
    sindex++;
    *(stack + sindex) = value;
}

long double pop(long double *stack, int sindex, int stacksize){
    if (sindex <= 0)
    {
        puts("Stack underflow!");
        exit(2);
    }
    long double temp;
    temp = *(stack + sindex);
    sindex--;
    return temp;
}

int main(int argc, char *argv[]){
    
    int sindex = 0;
    long double *stack;
    int stacksize = 8;
    stack = (long double *)malloc(sizeof(long double) * stacksize);

    char *line;
    size_t bufsize = 32;
    ssize_t nread = 0;
    char *pch;

    char i1;
    long double id;
    long double op1;
    long double op2;

    for (int i=0; i<stacksize; i++){
        *(stack + i) = 0;
    }
    while((nread = getline(&line, &bufsize, stdin) != EOF))
    {
        pch = strtok(line," 	");
        while (pch != NULL)
        {
            i1 = pch[0];
            switch(i1){
                case '+' :
                    op2 = pop(stack, &sindex, &stacksize);
                    op1 = pop(stack, &sindex, &stacksize);
                    push(stack, &sindex, &stacksize, op1 + op2);
                    break;
                case '-' :
                    op2 = pop(stack, &sindex, &stacksize);
                    op1 = pop(stack, &sindex, &stacksize);
                    push(stack, &sindex, &stacksize, op1 - op2);
                    break;
                case '*' :
                    op2 = pop(stack, &sindex, &stacksize);
                    op1 = pop(stack, &sindex, &stacksize);
                    push(stack, &sindex, &stacksize, op1 * op2);
                    break;
                case '/' :
                    op2 = pop(stack, &sindex, &stacksize);
                    op1 = pop(stack, &sindex, &stacksize);
                    push(stack, &sindex, &stacksize, op1 / op2);
                    break;
                case '^' :
                    op2 = pop(stack, &sindex, &stacksize);
                    op1 = pop(stack, &sindex, &stacksize);
                    push(stack, &sindex, &stacksize, pow(op1,op2));
                    break;
                case 'p' :
                    printf("%.10Le\n",pop(stack, &sindex, &stacksize));
                    break;
                case 'q' :
                    exit(0);
                default :
                    sscanf(pch, "%Lf", &id);
                    push(stack, &sindex, &stacksize, id);
            }
                pch = strtok(NULL," 	");
        }
    }
    free(stack);
    return(0);
}
