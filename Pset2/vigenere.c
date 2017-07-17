#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

string encrypt(string phrase, string key);
int get_key(char c);
bool is_valid_key(string key);

int main(int argc, string argv[]) {
    if (argc != 2) {
        printf("Please enter the correct number of arguments (1)\n");
        return 1;
    }
    
    string key = argv[1];
    
    // Check if key is valid
    if (!is_valid_key(key)) {
        printf("Please enter a key using only alphabetical characters");
        return 1;
    }
    
    string phrase = get_string();
    string cipher = encrypt(phrase, key);
    printf("%s\n", cipher);
    return 0;
}

string encrypt(string phrase, string key) {
    int Ki = 0;     // Key index variable
    for (int i = 0, n = strlen(phrase); i < n; i++) {
        if isalpha(phrase[i]) {
            // Handle upper and lower case
            int shift = 97;
            if isupper(phrase[i]) {
                shift = 65;
            }
            // Wrap key index back to beginning
            if (Ki == strlen(key)) {
                Ki = Ki % strlen(key);
            }
            
            char c = key[Ki];
            int k = get_key(c);
            phrase[i] = ((phrase[i] - shift) + k) % 26 + shift; 
            Ki ++;
        }
    }
    return phrase;
}

int get_key(char c) {
    if isupper(c) {
        return c - 65;
    }
    return c - 97;
}

bool is_valid_key(string key) {
    for (int i = 0, n = strlen(key); i < n; i++) {
        if (!isalpha(key[i])) {
            return false;
        }
    }
    return true;
}
