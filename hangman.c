#include "hangman.h"


int GetWord(char* targetEng, char* targetKor)
{
	// 랜덤넘버
	int RandomNumber;
	// 파일포인터
	FILE* fp;
	// 파일명들
	char FileNames[10] = { 0 };
	// 파일안에 들어있는 단어 개수
	int wordCount = 0;
	// 기타변수
	int i;
	char tempStr[ENG_LEN + KOR_LEN];
	char Day[2] = { 0 };
	

	// 시드 설정
	srand((unsigned int)time(NULL));

	// 파일 입력
	printf("파일명(일차) : ");
	scanf("%s", Day);
	
	// 파일명 만들기
	strcpy(FileNames, Day);
	strcat(FileNames, ".dic");
	
	// 파일 오픈
	fp = fopen(FileNames, "r");
	if (fp == NULL)
	{
		// 오픈 에러
		printf(" >> 파일 읽기 에러 : 해당 파일이 없습니다. <<\n");
		return FILE_ERROR;
	}

	// 단어의 개수를 센다.
	while(!feof(fp))
	{
		fgets(tempStr, ENG_LEN + KOR_LEN, fp);
		wordCount++;
	}
	
	if(wordCount <= 1)
	{
		if(!((tempStr[0] >=65 && tempStr[0] <= 90) || (tempStr[0] >= 97 && tempStr[0] <= 122)))
		{
			return NO_WORD;
		}
	}

	// 파일포인터를 다시 처음으로
	fseek(fp, 0, SEEK_SET);

	// 1 ~ 30 까지중 랜덤한 숫자 하나 선택1
	RandomNumber = rand() % wordCount + 1;
		
	// 랜덤한 숫자까지 읽어서 tempStr 에 저장
	for (i = 0; i < RandomNumber; i++)
	{
		fgets(tempStr, ENG_LEN + KOR_LEN, fp);
	}

	// 진짜 데이터 (마지막에 읽은 데이터를 토큰분리하여 저장)
	strcpy(targetEng, strtok(tempStr, " "));
	strcpy(targetKor, strtok(NULL, ""));
	// 엔터기 NULL로 변경
	targetKor[strlen(targetKor) - 1] = 0;

	// 파일 닫기
	fclose(fp);

	return NO_ERROR;
}


// 현재 상태 출력
void PrintHangman(int ErrorCount)
{
	if (ErrorCount >= 0) printf("-------------------+\n");
	if (ErrorCount >= 1) printf("                   O\n");
	if (ErrorCount >= 2) printf("                 / ");
	if (ErrorCount >= 3) printf("|");
	if (ErrorCount >= 4) printf(" \\\n");
	if (ErrorCount >= 5) printf("                  /");
	if (ErrorCount >= 6) printf(" \\");

	if (ErrorCount == 0) printf("\n\n\n");
	else if (ErrorCount == 1) printf("\n\n");
	else if (ErrorCount == 2 || ErrorCount == 3) printf("\n\n");
	else if (ErrorCount == 4) printf("\n");
	else printf("\n");

	printf("\n\n");
}

// 정답 출력(현재까지 맞춘 정답)
void PrintAnswer(char* targetEng, char* Answer, int* ErrorCount)
{
	// 정답의 글자수
	int AnsLen = strlen(Answer);
	// 기타 변수
	int i;
	char Alpha;
	// 있는 알파벳을 입력했는지 확인
	int IsFind = 0;

	// 현재까지의 정답 출력
	for (i = 0; i < AnsLen; i++)
	{
		printf("%c ", Answer[i]);
	}
	// 시도 횟수
	printf("\n%d 번째 시도 : ", *ErrorCount + 1);
	// 입력 받기
	scanf(" %c", &Alpha);

	// 정답 출력
	for (i = 0; i < AnsLen; i++)
	{
		if (Answer[i] == '_')
		{
			if (targetEng[i] == Alpha)
			{
				Answer[i] = Alpha;
				IsFind = 1;
			}
		}
	}

	// 실수했으면 ErrorCount 증가
	if (IsFind == 0)
	{
		(*ErrorCount)++;
	}
}


void Hangman()
{
	// 영문 저장
	char targetEng[15];
	// 뜻, 한글 저장
	char targetKor[60]; 
	// 에러 횟수
	int ErrorCount = 0;
	// 정답
	char Answer[15] = { 0 };
	// 기타 변수 
	int i;
	int Error;
	
	// 파일에서 랜덤한 단어 얻어오기
	Error = GetWord(targetEng, targetKor);
	if(Error == NO_WORD)
	{
		printf(" >> 데이터 파일 에러 : 입력한 파일에 아무 단어도 없습니다. <<\n\n");
	}
	else if(Error == FILE_ERROR)
	{
	}
	else
	{
		// 정답 초기셋팅
		for (i = 0; i < strlen(targetEng); i++)
		{
			Answer[i] = '_';
		}

		// 6번 실패할때까지
		while (ErrorCount != 7)
		{
			// 화면 초기화
			system("clear");
			// 제목 출력
			printf(">> 영어 단어 암기 프로그램 : 헹맨 << \n");
			// 힌트 출력
			printf("(힌트) %s\n", targetKor);
			// 현재 상태 출력
			PrintHangman(ErrorCount);

			// 도전횟수 모두 사용
			if (ErrorCount == 6)
				break;

			// 정답 출력 및 게임하기
			PrintAnswer(targetEng, Answer, &ErrorCount);

			// 정답을 맞추엇다면 종료
			if (strcmp(targetEng, Answer) == 0)
			{
				printf("   ###########################\n");
				printf("   #### Congratulations!! ####\n");
				printf("   ###########################\n");
				break;
			}
		}
	}
	
	getchar();

	// 마지막 엔터키
	printf("\nENTER 키 입력 시 Main 화면으로 돌아갑니다.\n");
	while (getchar() != '\n');
}
