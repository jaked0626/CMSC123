#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>

struct htbl {
    unsigned int size, occupied;
    char** entries; /* an array of strings */
    pthread_mutex_t m;
    pthread_cond_t wait;
};

typedef struct htbl htbl;


htbl* new_htbl(unsigned int size) {
    /* assumptions: allocations succeed */
    
    htbl* res = (htbl*)malloc(sizeof(htbl));
    
    res->size = size;
    res->occupied = 0;
    
    res->entries = (char**)malloc(sizeof(char*) * size);

    pthread_mutex_init(&res->m, NULL);
    pthread_cond_init(&res->wait, NULL);
    
    /* each entry starts off empty */
    unsigned int i;
    for (i = 0; i < size; i++) {
        res->entries[i] = NULL;
    }
    
    return res;
}


unsigned int hash(char* str, unsigned int size) {
    /* assumptions: size is not zero */
    
    unsigned int i = 0, res = 0;
    
    while (str[i]) {
        res = res * 37 + str[i];
        res = res % size;
        i++;
    }
    
    return res;
}


bool empty_string(char* str) {
    return str[0] == '\0';
}


void insert(htbl* ht, char* str) {
    /* assumptions: string is not already in table */
    
    unsigned int i = hash(str, ht->size);

    pthread_mutex_lock(&ht->m);
    while (ht->occupied + 1 >= ht->size) { //changed to while so no race condition
        pthread_cond_wait(&ht->wait, &ht->m);
        // exit(1);
    }

    /* will use the first empty or empty-from-removal spot found */
    while (ht->entries[i] != NULL && !empty_string(ht->entries[i])) {
        i = (i + 1) % ht->size;
    }
    
    ht->entries[i] = str;
    ht->occupied++;
    pthread_mutex_unlock(&ht->m);
}


void htbl_remove(htbl* ht, char* str) {
    /* assumptions: string is actually in table */
    
    unsigned int i = hash(str, ht->size);
    
    pthread_mutex_lock(&ht->m);
    /* note: strcmp returns zero when two strings match */
    while (strcmp(ht->entries[i], str) != 0) {
        i = (i + 1) % ht->size;
    }
    
    ht->entries[i] = ""; /* empty-from-removal denoted by empty string */
    ht->occupied--;
    pthread_mutex_unlock(&ht->m);
    pthread_cond_signal(&ht->wait);
}


bool member(htbl* ht, char* str) {
    unsigned int i = hash(str, ht->size);
    unsigned int start = i; /* first spot searched, to avoid cycling forever */
    bool res = false;
    
    /* note: strcmp returns zero when two strings match */
    pthread_mutex_lock(&ht->m);
    while (ht->entries[i] != NULL && strcmp(ht->entries[i], str) != 0) {
        i = (i + 1) % ht->size;
        
        /* if have looked at every spot and returned to beginning
         * without encountering string or NULL, cannot be in table;
         * avoid infinite loop */
        if (i == start) {
            pthread_mutex_unlock(&ht->m);
            return false;
        }
    }

    /* did loop halt due to empty spot or string match? */
    /* string matched if not empty spot */
    // added conditional to ensure value of ith entry does not change before return
    if (ht->entries[i] != NULL) {
        res = true;
    }
    pthread_mutex_unlock(&ht->m); 

    return res;
}
