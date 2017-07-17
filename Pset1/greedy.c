#include <stdio.h>
#include <cs50.h>
#include <math.h>

int get_change_in_cents(void);
int run_greedy(int cents, int count);

int main(void) {
    int cents = get_change_in_cents();
    int count = run_greedy(cents, 0);
    printf("%i\n", count);
}

int get_change_in_cents(void)
{
    float change;
    do
    {
        printf("How much change is owed: ");
        change = get_float();
    }
    while (change <= 0);
    int cents = (int)round(change*100);
    return cents;
}

int run_greedy(int cents, int count)
{
    if (cents == 0)
    {
        return count;
    }
    else if (cents >= 25)
    {
        return run_greedy(cents-25, count+1);
    }
    else if (cents >= 10)
    {
        return run_greedy(cents-10, count+1);
    }
    else if (cents >= 5)
    {
        return run_greedy(cents-5, count+1);
    }
    else 
    {
        return run_greedy(cents-1, count+1);
    }
}