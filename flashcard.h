#ifndef _FLASHCARD_H_
#define _FLASHCARD_H_

#include "common.h"

#define TITLE ">> 영어 단어 암기 프로그램 : 플래쉬카드 <<\n\n\n\n\n"
#define kWhiteSpace "                         "
#define SYSTEM_SLEEP_SPEED 2
#define MAX_LEN_OF_INPUT 1*15 + 3*30*2 + 5
#define MAX_FILE_NAME sizeof(int) + 1

typedef struct Word
{
		char *eng;
		char *kor;
		struct Word *next;
} Word;

void SplitLine(char *line, char *output[]);
void InsertWord(Word **head, Word *new_Word);
void InsertWords(Word **head, FILE *fp);
void PrintWords(Word **head, int speed);
void FreeWords(Word **head);
int Compare(const void *p, const void *q);
void SortWords(Word **head);
void Flashcard();

#endif