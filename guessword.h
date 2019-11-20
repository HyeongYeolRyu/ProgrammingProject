//#ifndef UNTITLED7_GUESSWORD_H
//#define UNTITLED7_GUESSWORD_H


#ifndef _GUESSWORD_H
#define _GUESSWORD_H


#define TITLE_g ">> 영어 단어 암기 프로그램 : 영어 단어 맞추기 <<\n\n\n\n\n"
#define MAX_LEN_OF_INPUT 1*15 + 3*30*2 + 5
#define MAX_FILE_NAME sizeof(int) + 1
#define MAX_SHUFFLE_VALUE 1000

#include "common.h" //전체 헤더파일

/*단어장 구조체*/
typedef struct g_Word{
	char *eng;
	char *kor;
	struct g_Word *next;
}g_Word;

/*guessword.c 에서 쓰이는 함수 목록*/
void g_SplitLine(char *line, char *output[]);
void g_InsertWord(g_Word **head, g_Word *new_Word);
int g_InsertWords(g_Word **head, FILE *fp);
void GuessWords(g_Word **head);
void g_FreeWords(g_Word **head);
int g_Compare(const void *p, const void *q);
void g_swap_word(g_Word **p1, g_Word **q1);
void g_shuffle(g_Word **arr, int num_of_nodes);
void g_SortWords(g_Word **head, int num_of_nodes);
void Guessword();

//#endif UNTITLED7_GUESSWORD_H

#endif
