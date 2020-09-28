#include <stdio.h>
#include "stacksADT.h"

int main(){
    unsigned int num;
    int* digit;
    STACK* stack;

    stack=createStack();

    printf("Enter an integer:");
    scanf("%d", &num);

    while(num>0){
        digit=(int*)malloc(sizeof(int));
        *digit=num%2;
        pushStack (stack, digit);
        num=num/2;
    }

    printf("The binary number is:");
    while(!emptyStack(stack)){
        digit=(int*)popStack (stack);
        printf("%ld", *digit);
    }
    printf("\n");

    destroyStack(stack);
    return 0;

}