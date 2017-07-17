#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b);

int main(void)
{
    int a = 1;
    int b = 2;
    printf("a is: %i \n", a);
    printf("b is: %i \n", b);
    printf("Swapping...\n");
    swap(&a, &b);
    printf("a is: %i \n", a);
    printf("b is: %i \n", b);
}

void swap(int *a, int *b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
}