#ifndef _HANGMAN_H
#define _HANGMAN_H

#define TITLE_H ">> 영어 단어 암기 프로그램 : 행맨 <<\n\n\n\n\n"
#define MAX_LEN_OF_INPUT 1*15 + 3*30*2 + 5
#define MAX_FILE_NAME sizeof(int) + 1
#define SYSTEM_SLEEP_SPEED 2
#define MSG_FAIL "실패하였습니다...\n"
#define MSG_SUCCESS "##########################\n### Congratulations!!! ###\n##########################\n\n"

#include "common.h"

typedef struct h_Word{
	char *eng;
	char *kor;
	struct h_Word *next;
}h_Word;

void h_SplitLine(char *line, char *output[]);
void h_InsertWord(h_Word **head, h_Word *new_Word);
int h_InsertWords(h_Word **head, FILE *fp);
void GetRandomWord(h_Word **head, h_Word **target_word);
void h_FreeWords(h_Word **head);
int UpdateCorrectArr(char *correct_char, char *eng, int eng_len, char ch);
void PrintHangman(int num_of_errors);
void PrintCurrentText(char *correct_char, char *eng, int eng_len);
void PlayHangman(h_Word *target_word);
void Hangman();

#endif
