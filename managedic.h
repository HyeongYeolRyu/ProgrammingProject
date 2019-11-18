#ifndef _MANAGEDIC_H_
#define _MANAGEDIC_H_

#include "common.h"

typedef struct m_Word{
    char spell[15];
    char mean1[30];
    char mean2[30];
    char mean3[30];
    struct m_Word *next;
}m_Word;

typedef struct list{
    m_Word *head;
    m_Word *tail;
    m_Word *now;
}List;

void managedic();
void file_add();
void Word_add();
void Words_see();
void Word_file_list();

#endif
