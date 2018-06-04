#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int sindex = 0;
double stack[256];

void push(double value){
    if (sindex >= 255)
    {
        puts("Stack overflow!");
        exit(1);
    }
    sindex++;
    stack[sindex] = value;
}

double pop(){
    if (sindex <= 0)
    {
        puts("Stack underflow!");
        exit(2);
    }
    double temp;
    temp = stack[sindex];
    sindex--;
    return temp;
}

int main(int argc, char *argv[]){
    char i1;
    double id;
    double op1;
    double op2;
    for (int i=0; i<256; i++){
        stack[i] = 0;
    }
    for (int i=1; i<argc; i++){
        i1 = argv[i][0];
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
                printf("%e\n",pop());
                break;
            default :
                sscanf(argv[i], "%lf", &id);
                push(id);
        }
    }
}
