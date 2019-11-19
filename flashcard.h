#ifndef _FLASHCARD_H_
#define _FLASHCARD_H_

#include "common.h"

#define TITLE ">> 영어 단어 암기 프로그램 : 플래쉬카드 <<\n\n\n\n\n"
#define kWhiteSpace "                         "
#define SYSTEM_SLEEP_SPEED 2
#define MAX_LEN_OF_INPUT 1*15 + 3*30*2 + 5
#define MAX_FILE_NAME sizeof(int) + 1
#define MAX_SHUFFLE_VALUE 1000

typedef struct f_Word
{
		char *eng;
		char *kor;
		struct f_Word *next;
} f_Word;

void SplitLine(char *line, char *output[]);
void InsertWord(f_Word **head, f_Word *new_Word);
int InsertWords(f_Word **head, FILE *fp);
void PrintWords(f_Word **head, int speed);
void FreeWords(f_Word **head);
int Compare(const void *p, const void *q);
void swap_word(f_Word **p1, f_Word **q1);
void shuffle(f_Word **arr, int num_of_nodes);
void SortWords(f_Word **head, int num_of_nodes);
void Flashcard();

#endif