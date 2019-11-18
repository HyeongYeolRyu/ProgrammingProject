#include "flashcard.h"

void SplitLine(char *line, char *output[])
{
	char *p = strtok(line, " ");
	output[0] = p; 					// eng 
	output[1] = strtok(NULL, "");	// kor
}

void InsertWord(f_Word **head, f_Word *new_Word)
{
	if (*head == NULL)
	{
		*head = new_Word;
		return;
	}
	f_Word *w = *head;
	while (w -> next != NULL)
		w = w -> next;
	w -> next = new_Word;
}

void InsertWords(f_Word **head, FILE *fp)
{
	char *output[2];
	f_Word *w;
	char line[MAX_LEN_OF_INPUT];
	while (fgets(line, sizeof(line), fp))
	{
		int line_len = strlen(line);
		if (line[line_len - 1] == '\n')
			line[line_len - 1] = '\0';
		w = (f_Word *)malloc(sizeof(f_Word));
		SplitLine(line, output);
		w -> eng = (char *)malloc(sizeof(char) * strlen(output[0]) + 1);
		strcpy(w -> eng, output[0]);
		w -> kor = (char *)malloc(sizeof(char) * strlen(output[1]) + 1);
		strcpy(w -> kor, output[1]);
		w -> next = NULL;
		InsertWord(head, w);
	}
	fclose(fp);
}

void PrintWords(f_Word **head, int speed)
{
	f_Word *ptr = *head;
	while (ptr != NULL)
	{
		system("clear");
		printf(TITLE);
		printf("%s%s\n", kWhiteSpace, ptr->eng);
		sleep(speed);
		system("clear");
		printf(TITLE);
		printf("%s%s\n", kWhiteSpace, ptr->kor);
		sleep(speed);
		ptr = ptr -> next; 	
	}
}

void FreeWords(f_Word **head)
{
	f_Word *w = *head;
	while (w != NULL)
	{
		f_Word *tmp = w;
		free(tmp -> eng);
		free(tmp -> kor);
		free(tmp);
		w = w -> next;
	}
}

int Compare(const void *p, const void *q)
{
	return strcmp((*(f_Word **)p)->eng, (*(f_Word **)q)->eng);
}

void SortWords(f_Word **head)
{
	int i, num_of_node = 0;
	f_Word *ptr = *head, *new_head = NULL, **arr;

	while (ptr != NULL)
	{
		ptr = ptr -> next;
		num_of_node++;
	}
	arr = (f_Word **)malloc(sizeof(f_Word *) * num_of_node);
	ptr = *head;
	for (i = 0; i < num_of_node; i++)
	{
		arr[i] = ptr;
		ptr = ptr -> next;
	}

	qsort(arr, num_of_node, sizeof(f_Word *), Compare);	
	for (i = 0; i < num_of_node; i++)
		arr[i] -> next = NULL;
	for (i = 0; i < num_of_node; i++)
		InsertWord(&new_head, arr[i]);
	*head = new_head;
	free(arr);
}

void Flashcard()
{
	FILE *fp;
	f_Word *wordlist = NULL;
	char day[MAX_FILE_NAME];
	int print_way, speed;

	// 설정 입력
	printf("속도(초) : ");
	scanf("%d", &speed);
	printf("파일명(일차) : ");
	scanf("%s", day);
	if (!(fp = fopen(strcat(day, ".dic"), "r")))
	{
		printf(" >> 파일 읽기 에러 : 해당 파일이 없습니다. <<\n");
		sleep(SYSTEM_SLEEP_SPEED);
		return;
	}
	printf("출력 방식(알파벳 순서대로 : 1, 무작위 : 2) : ");
	scanf("%d", &print_way);

	// file 내 단어들 삽입
	InsertWords(&wordlist, fp);

	// 알파벳 순으로 정렬할 경우
	if (print_way == 1)
		SortWords(&wordlist);

	system("clear");
	printf(TITLE);

	// 단어장 플래시 보여주기
	PrintWords(&wordlist, speed);

	// 동적 메모리 할당 해제
	FreeWords(&wordlist);

	// 함수 종료 전 화면 초기화
	system("clear");
}