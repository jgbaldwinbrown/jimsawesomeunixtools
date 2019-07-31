#include <stdio.h>
#include <ctype.h>
#define LINEWIDTH 16

int main(){
    char a = 0;
    char buf[LINEWIDTH];
    size_t i = 0;
    while((a=getchar()) != EOF){
        buf[i%LINEWIDTH] = a;
        if (i%LINEWIDTH == 0){
            printf("%08lx: ", i);
        }
        if (i%2 == 0){
            printf("%02x", a);
        } else {
            printf("%02x ", a);
        }
        if (i%LINEWIDTH == (LINEWIDTH-1)){
            printf(" ");
            for (size_t j=0; j<LINEWIDTH; j++){
                if (isprint(buf[j])){
                    printf("%c", buf[j]);
                } else {
                    printf(".");
                }
            }
            printf("\n");
        }
        i++;
    }
    if (i%LINEWIDTH != 0) {
        for(size_t j=0; j<(2*(LINEWIDTH - (i%LINEWIDTH))); j++){
            printf(" ");
        }
        for(size_t j=0; j<((LINEWIDTH - (i%LINEWIDTH))/2); j++){
            printf(" ");
        }
        printf("  ");
        for (size_t j=0; j<((i%LINEWIDTH)); j++){
            if (isprint(buf[j])){
                printf("%c", buf[j]);
            } else {
                printf(".");
            }
        }
    }
        
    printf("\n");
    return 0;
}
