#ifndef _FLASHCARD_H_
#define _FLASHCARD_H_

#include "common.h"

#define TITLE ">> 영어 단어 암기 프로그램 : 플래쉬카드 <<\n\n\n\n\n"
#define kWhiteSpace "                         "
#define SYSTEM_SLEEP_SPEED 2
#define MAX_LEN_OF_INPUT 1*15 + 3*30*2 + 5
#define MAX_FILE_NAME sizeof(int) + 1

typedef struct f_Word
{
		char *eng;
		char *kor;
		struct f_Word *next;
} f_Word;

void SplitLine(char *line, char *output[]);
void InsertWord(f_Word **head, f_Word *new_Word);
void InsertWords(f_Word **head, FILE *fp);
void PrintWords(f_Word **head, int speed);
void FreeWords(f_Word **head);
int Compare(const void *p, const void *q);
void SortWords(f_Word **head);
void Flashcard();

#endif