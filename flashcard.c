#include "flashcard.h"

void SplitLine(char *line, char *output[])
{
	char *p = strtok(line, " ");
	output[0] = p; 			// eng 
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

int InsertWords(f_Word **head, FILE *fp)
{
	char *output[2];
	int is_empty_file = 1;
	f_Word *w;
	char line[MAX_LEN_OF_INPUT];
	while (fgets(line, sizeof(line), fp))
	{
		int i; 
		int is_empty_line = 1;
		int line_len = strlen(line);
		
		for (i = 0; i < line_len; i++) 
		{
			if (!isspace(line[i]))
			{
				is_empty_line = 0;
				is_empty_file = 0;
			}
		}

		if (is_empty_line)
		{
			continue;
		}

		if (line[line_len - 1] == '\n')
		{
			line[line_len - 1] = '\0';
		}
		w = (f_Word *)malloc(sizeof(f_Word));
		SplitLine(line, output);
		w -> eng = (char *)malloc(sizeof(char) * strlen(output[0]) + 1);
		strcpy(w -> eng, output[0]);
		w -> kor = (char *)malloc(sizeof(char) * strlen(output[1]) + 1);
		strcpy(w -> kor, output[1]);
		w -> next = NULL;
		InsertWord(head, w);
	}
	if (is_empty_file) // check whether given dic file is empty or not
	{
		fclose(fp);
		return -1;
	}
	fclose(fp);
	return 0;
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

void Swap_word(f_Word **p1, f_Word **q1)
{
	f_Word *tmp = *p1;
	*p1 = *q1;
	*q1 = tmp;
}

void Shuffle(f_Word **arr, int num_of_nodes)
{
	int i, idx1, idx2;
	srand(time(NULL));
	for (i = 0; i < MAX_SHUFFLE_VALUE; i++)
	{
		idx1 = rand() % num_of_nodes;
		idx2 = rand() % num_of_nodes;
		Swap_word(&arr[idx1], &arr[idx2]);
	}
}

void SortWords(f_Word **head, int order_option)
{
	int i, num_of_nodes = 0;
	f_Word *ptr = *head, *new_head = NULL, **arr;

	while (ptr != NULL)
	{
		ptr = ptr -> next;
		num_of_nodes++;
	}

	arr = (f_Word **)malloc(sizeof(f_Word *) * num_of_nodes);
	ptr = *head;
	for (i = 0; i < num_of_nodes; i++)
	{
		arr[i] = ptr;
		ptr = ptr -> next;
	}

	if (order_option == 1) // alphabetical order
	{
		qsort(arr, num_of_nodes, sizeof(f_Word *), Compare);	
	}
	else // random order
	{
		Shuffle(arr, num_of_nodes);
	}
	
	for (i = 0; i < num_of_nodes; i++)
	{	
		arr[i] -> next = NULL;
	}
	for (i = 0; i < num_of_nodes; i++)
	{
		InsertWord(&new_head, arr[i]);
	}
	*head = new_head;
	free(arr);
}

void Flashcard()
{
	FILE *fp;
	f_Word *wordlist = NULL;
	char day[MAX_FILE_NAME];
	int order_option, speed;

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
	scanf("%d", &order_option);
	if (!(order_option == 1 || order_option == 2))
	{
		printf(" >> 출력 방식 입력 에러 : 1(알파벳 순서대로) 또는 2(무작위)를 입력해야 합니다. <<\n");
		sleep(SYSTEM_SLEEP_SPEED);
		return;	
	}

	// file 내 단어들 삽입
	if(InsertWords(&wordlist, fp))
	{
		printf(" >> 데이터 파일 에러 : 입력한 파일에 아무 단어도 없습니다. <<\n");
		sleep(SYSTEM_SLEEP_SPEED);
		return;	
	}

	// 알파벳 순 / 무작위 정렬
	SortWords(&wordlist, order_option);

	system("clear");
	printf(TITLE);

	// 단어장 플래시 보여주기
	PrintWords(&wordlist, speed);

	// 동적 메모리 할당 해제
	FreeWords(&wordlist);

	// 함수 종료 전 화면 초기화
	system("clear");
}