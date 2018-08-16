#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int sindex = 0;
long double *stack;
int stacksize = 8;

void push(long double value){
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

long double pop(){
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
                    op2 = pop();
                    op1 = pop();
                    push(op1 + op2);
                    break;
                case '-' :
                    op2 = pop();
                    op1 = pop();
                    push(op1 - op2);
                    break;
                case '*' :
                    op2 = pop();
                    op1 = pop();
                    push(op1 * op2);
                    break;
                case '/' :
                    op2 = pop();
                    op1 = pop();
                    push(op1 / op2);
                    break;
                case '^' :
                    op2 = pop();
                    op1 = pop();
                    push(pow(op1,op2));
                    break;
                case 'p' :
                    printf("%.10Le\n",pop());
                    break;
                case 'q' :
                    exit(0);
                default :
                    sscanf(pch, "%Lf", &id);
                    push(id);
            }
                pch = strtok(NULL," 	");
        }
    }
    free(stack);
}
