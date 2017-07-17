/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "dictionary.h"

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    int index;
    node *curr = head;
    for (int i = 0, len = strlen(word); i <= len; i++)
    {
        char c = word[i];
        
        if (c == '\0')
        {
            if (curr->is_word)
            {
                return true;
            }
            return false;
        }
        
        if (c == '\'')
        {
            index = 26;   
        }
        
        else
        {
            index = tolower(c) - 'a';
        }
        
        if (curr->children[index] != NULL)
        {
            curr = curr->children[index];
        }
        else
        {
            return false;
        }
    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        return 0;
    }
    
    // Assign memory for word and head node
    char *word = malloc(LENGTH * sizeof(char)); 
    head = create_node();
    // Scan over file and add words to trie
    while(fscanf(f, "%s", word) != EOF)
    {
        add_word(word, head);
        count ++;
    }
    fclose(f);
    free(word);
    return 1;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (count > 0)
    {
        return count;
    }
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    unload_helper(head);
    return true;
}

void add_word(char *word, node *head)
{   

    node *curr = head;
    int index;
    for (int i = 0, length = strlen(word); i <= length; i++)
    {   
        char c = word[i];
        // If null terminator character, set end of word flag
        if (c == '\0')
        {
            curr->is_word = 1;
            return;
        }
        
        // Apostrophe is set to be the 27th letter of alphabet
        if (c == '\'')
        {
            index = 26;
        }
        
        // Otherwise get index of character in array
        else
        {
           index = tolower(c) - 'a';
        }
        
        // If character already exists in trie, set curr to the next array
        if (curr->children[index] != NULL)
        {
            curr = curr->children[index];
        }
        // Otherwise create a new node and set pointer to it and set curr to it
        else
        {
            node *temp = create_node();
            curr->children[index] = temp;
            curr = curr->children[index];
        }
    }
}

node* create_node(void)
{
    node *new_node = malloc(sizeof(node));
    for (int i = 0; i < 27; i++)
    {
        new_node->children[i] = NULL;
        new_node->is_word = 0;
    }
    return new_node;
}

void unload_helper(node *n)
{
    for (int i = 0; i < 27; i++)
    {
        if (n->children[i] != NULL)
        {
            unload_helper(n->children[i]);
        }
    }
    free(n);
}