#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void push(long double *stack, unsigned long *sindex_p, unsigned long *stacksize_p, long double value){
    if (*sindex_p >= *stacksize_p)
    {
        puts("Stack overflow!");
        exit(1);
    }
    if (*sindex_p >= ((*stacksize_p) - 1))
    {
        *stacksize_p = (*stacksize_p) * 2;
        stack = (long double *)realloc(stack,sizeof(long double) * (*stacksize_p));
    }
    (*sindex_p)++;
    stack[*sindex_p] = value;
}

long double pop(long double *stack, unsigned long *sindex, unsigned long *stacksize){
    if (*sindex <= 0)
    {
        puts("Stack underflow!");
        exit(2);
    }
    long double temp;
    temp = stack[*sindex];
    (*sindex)--;
    return temp;
}

int main(int argc, char *argv[]){
    
    unsigned long sindex = 0;
    unsigned long stacksize = 8;
    unsigned long *sindex_p = &sindex;
    unsigned long *stacksize_p = &stacksize;
    long double *stack;
    stack = (long double *)malloc((sizeof(long double) * stacksize));

    char *line;
    size_t bufsize = 32;
    ssize_t nread = 0;
    char *pch;

    char i1;
    long double id;
    long double op1;
    long double op2;

    for (unsigned long i=0; i<stacksize; i++){
        stack[i] = 0;
    }

    push(stack, sindex_p, stacksize_p, 3.0);
    push(stack, sindex_p, stacksize_p, 4.0);
    op2 = pop(stack, sindex_p, stacksize_p);
    op1 = pop(stack, sindex_p, stacksize_p);
    push(stack, sindex_p, stacksize_p, pow(op1,op2));
    printf("%.10Le\n",pop(stack, sindex_p, stacksize_p));
    

    while((nread = getline(&line, &bufsize, stdin)) != -1)
    {
        pch = strtok(line," 	");
        while (pch != NULL)
        {
            i1 = pch[0];
            switch(i1){
                case '+' :
                    op2 = pop(stack, sindex_p, stacksize_p);
                    op1 = pop(stack, sindex_p, stacksize_p);
                    push(stack, sindex_p, stacksize_p, op1 + op2);
                    break;
                case '-' :
                    op2 = pop(stack, sindex_p, stacksize_p);
                    op1 = pop(stack, sindex_p, stacksize_p);
                    push(stack, sindex_p, stacksize_p, op1 - op2);
                    break;
                case '*' :
                    op2 = pop(stack, sindex_p, stacksize_p);
                    op1 = pop(stack, sindex_p, stacksize_p);
                    push(stack, sindex_p, stacksize_p, op1 * op2);
                    break;
                case '/' :
                    op2 = pop(stack, sindex_p, stacksize_p);
                    op1 = pop(stack, sindex_p, stacksize_p);
                    push(stack, sindex_p, stacksize_p, op1 / op2);
                    break;
                case '^' :
                    op2 = pop(stack, sindex_p, stacksize_p);
                    op1 = pop(stack, sindex_p, stacksize_p);
                    push(stack, sindex_p, stacksize_p, pow(op1,op2));
                    break;
                case 'p' :
                    printf("%.10Le\n",pop(stack, sindex_p, stacksize_p));
                    break;
                case 'q' :
                    exit(0);
                default :
                    sscanf(pch, "%Lf", &id);
                    push(stack, sindex_p, stacksize_p, id);
            }
                pch = strtok(NULL," 	");
        }
    }
    free(stack);
    return(0);
}
