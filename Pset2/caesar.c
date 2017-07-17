#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

string encrypt(string phrase, int k);

int main(int argc, string argv[]) {
    if (argc != 2) {
        printf("Please enter the correct number of arguments (1)\n");
        return 1;
    }
    
    int k = atoi(argv[1]);
    string phrase = get_string();
    string cipher = encrypt(phrase, k);
    printf("%s\n", cipher);
    return 0;
}

string encrypt(string phrase, int k) {
    for (int i = 0, n = strlen(phrase); i < n; i++) {
        if isalpha(phrase[i]) {
            int shift = 97;
            if isupper(phrase[i]) {
                shift = 65;
            }
            phrase[i] = ((phrase[i] - shift) + k) % 26 + shift; 
        }
    }
    return phrase;
}