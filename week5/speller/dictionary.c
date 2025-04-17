// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// variable that increment each time a word is load from dictionary into buffer
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *ptr_trav = table[hash(word)];
    if (ptr_trav == NULL)
        return false;
    do
    {
        if (strcasecmp(word, ptr_trav->word) == 0)
        {
            return true;
        }
        ptr_trav = ptr_trav->next;
    }
    while (ptr_trav != NULL);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open dictionary file
    FILE *dictionary_ptr = fopen(dictionary, "r");
    if (dictionary_ptr == NULL)
        return false;

    // read each word from source into buffer and add into hash table
    char word_tmp[LENGTH + 1];
    while (fscanf(dictionary_ptr, "%s", word_tmp) != EOF)
    {
        word_count++;
        unsigned int hash_code = hash(word_tmp);
        node *node_ptr = malloc(sizeof(node));
        if (node_ptr == NULL)
            return false;
        strcpy(node_ptr->word, word_tmp);
        node_ptr->next = NULL;
        if (table[hash_code] == NULL)
        {
            table[hash_code] = node_ptr;
        }
        else
        {
            node *ptr_tmp = node_ptr;
            node_ptr->next = table[hash_code];
            table[hash_code] = ptr_tmp;
        }
    }

    // close dictionary file
    fclose(dictionary_ptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // free every node_ptr that is called by malloc, as [N] buckets of linked list
    node *ptr_trav = NULL, *ptr_next = NULL;
    for (int i = 0; i < N; i++)
    {
        if (table[i] == NULL)
            continue;
        ptr_trav = table[i];
        while (ptr_trav != NULL)
        {
            ptr_next = ptr_trav->next;
            free(ptr_trav);
            ptr_trav = ptr_next;
        }
    }
    return true;
}
