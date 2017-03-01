#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16
#define PORTION_SIZE 5000

/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */
// #define OPT 1
typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;

typedef struct __segments {
    int cap;
    int size;
    entry** seg;
} segments;

entry *findName(char lastName[], entry *pHead, segments *s, int nthread);
entry *append(char lastName[], entry *e);
segments *segments_new();
int segments_size(segments *s);
void push_back(segments *s, entry *e);

#endif
