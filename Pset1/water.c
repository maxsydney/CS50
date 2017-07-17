#include <stdio.h>
#include <cs50.h>

int main(void) {
    printf("minutes: ");
    int mins = get_int();
    printf("bottles: %i\n", mins * 12);
}
