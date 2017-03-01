#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <omp.h>
#include "phonebook_opt.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */

entry *__findName(char lastName[], entry *pHead)
{
    int count = 0;
    while (pHead != NULL && count < PORTION_SIZE) {
        if (strcasecmp(lastName, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
        count++;
    }
    return NULL;
}

entry *findName(char lastName[], entry *pHead, segments *s, int nthread)
{
    int num = s->size;
    entry **res = calloc(sizeof(entry*), num);

    omp_set_num_threads(nthread);
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        for(int i = id; i < num; i+=nthread) {
            res[i] = __findName(lastName, s->seg[i]);
        }
    }

    for(int i = 0; i < num; i++) {
        if(res[i]) {
            entry *rev = res[i];
            free(res);
            return rev;
        }
    }
    free(res);
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    /* allocate memory for the new entry and put lastName */
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;

    return e;
}



segments *segments_new()
{
    segments *s;
    s = (segments*)malloc(sizeof(segments));
    s->cap = 1;
    s->size = 0;
    s->seg = malloc(sizeof(entry*));
    return s;
}

void push_back(segments *s, entry* e)
{
    if((s->size) + 1 >= s->cap) {
        (s->cap) *= 2;
        s->seg = realloc(s->seg, sizeof(entry*)*s->cap);
        s->seg[(s->size)++] = e;
    } else {
        s->seg[(s->size)++] = e;
    }
}

int segments_size(segments *s)
{
    return s->size;
}
