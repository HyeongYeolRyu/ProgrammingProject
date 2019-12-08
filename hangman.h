#ifndef _HANGMAN_H_
#define _HANGMAN_H_


#include "common.h"

#define NO_ERROR 1
#define FILE_ERROR 2
#define NO_WORD 3

// 영어 단어 길이
#define ENG_LEN 30
// 한글 길이
#define KOR_LEN 60

// 영어 단어 가져오기
int GetWord(char* targetEng, char* targetKor);
// 현재 상태 출력
void PrintHangman(int ErrorCount);
// 정답 출력(게임하기)
void PrintAnswer(char* targetEng, char* Answer, int* ErrorCount);
// 행맨 게임 플레이 시작
void Hangman();

#endif
