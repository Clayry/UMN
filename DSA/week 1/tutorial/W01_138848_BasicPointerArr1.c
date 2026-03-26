#include  <stdio.h>

int main(){
    int randomNumber[] = {10, 24, 234, 345, 234};

    printf("randomNumber = %p \n", randomNumber);
    printf("&randomNumber = %p \n", &randomNumber);
    printf("&randomNumber = %p \n\n", &randomNumber[0]);
    
    printf("randomNumber = %d \n", randomNumber[0]);
    printf("*randomNumber = %d \n\n", *randomNumber);

    printf("randomNumber[2] = %d \n", randomNumber[2]);
    printf("*(randomNumber+2) = %d \n\n", *(randomNumber+2));

    printf("&randomNumber[2] = %p\n", &randomNumber[2]);

    return 0;
}