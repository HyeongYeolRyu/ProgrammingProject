#include "guessword.h"

void g_SplitLine(char *line, char *output[])
{
	char *p = strtok(line, " ");
	output[0] = p;                 // eng
	output[1] = strtok(NULL, "");  // kor
}

void g_InsertWord(g_Word **head, g_Word *new_Word)
{
	if (*head == NULL)
	{
		*head = new_Word;
		return;
	}
	g_Word *w = *head;
	while (w -> next != NULL)
		w = w -> next;
	w -> next = new_Word;
}

int g_InsertWords(g_Word **head, FILE *fp)
{
	char *output[2];
	int is_empty_file = 1;
	g_Word *w;
	char line[MAX_LEN_OF_INPUT];
	while (fgets(line, sizeof(line), fp))
	{
		int is_empty_line = 1;
		int line_len = strlen(line);

		for(int i=0;i<line_len;i++){
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
			line[line_len - 1] = '\0';
		w = (g_Word *)malloc(sizeof(g_Word));
		g_SplitLine(line, output);
		w -> eng = (char *)malloc(sizeof(char) * strlen(output[0]) + 1);
		strcpy(w -> eng, output[0]);
		w -> kor = (char *)malloc(sizeof(char) * strlen(output[1]) + 1);
		strcpy(w -> kor, output[1]);
		w -> next = NULL;
		g_InsertWord(head, w);
	}
	if (is_empty_file) // check whether given dic file is empty or not
	{
		fclose(fp);
		return -1;
	}

	fclose(fp);
	return 0;
}

void GuessWords(g_Word **head)
{
	g_Word *ptr = *head;
	char an[MAX_LEN_OF_INPUT];
	float score=0;
	int cnt_cor=0,cnt_incor=0;
	
	while (strcmp(an,".quit") != 0)
	{
		printf("%s -> ", ptr->kor);
		scanf("%s",an);
		if(strcmp(an,ptr->eng) == 0) {
			printf("correct!\n");
			++cnt_cor;
		}
		else if(strcmp(an,".quit") == 0)
			continue;
		else
		{
			printf("incorrect!\n");
			++cnt_incor;
		}
		ptr = ptr -> next;
		if(ptr == NULL){
			printf("단어가 없어욤 뿌우\n");
			break;
		}
	}
	//printf("전체 : %d, 맞은 것 : %d",cnt_cor+cnt_incor, cnt_cor);
	if (cnt_cor + cnt_incor == 0)
		score = 0;
	else
		score = (float)cnt_cor/(float)(cnt_cor+cnt_incor) * 100;
	printf("당신의 점수는 %.2f 점입니다.\n",score);
}

void g_FreeWords(g_Word **head)
{
	g_Word *w = *head;
	while (w != NULL)
	{
		g_Word *tmp = w;
		free(tmp -> eng);
		free(tmp -> kor);
		free(tmp);
		w = w -> next;
	}
}

int g_Compare(const void *p, const void *q)
{
	return strcmp((*(g_Word **)p)->eng, (*(g_Word **)q)->eng);
}

void g_swap_word(g_Word **p1, g_Word **q1)
{
	g_Word *tmp = *p1;
	*p1 = *q1;
	*q1 = tmp;
}

void g_shuffle(g_Word **arr, int num_of_nodes)
{
	int i, idx1, idx2;
	srand(time(NULL));
	for (i = 0; i < MAX_SHUFFLE_VALUE; i++)
	{
		idx1 = rand() % num_of_nodes;
		idx2 = rand() % num_of_nodes;
		g_swap_word(&arr[idx1], &arr[idx2]);
	}
}

void g_SortWords(g_Word **head, int order_option)
{
	int i, num_of_nodes = 0;
	g_Word *ptr = *head, *new_head = NULL, **arr;

	while (ptr != NULL)
	{
		ptr = ptr -> next;
		num_of_nodes++;
	}
	arr = (g_Word **)malloc(sizeof(g_Word *) * num_of_nodes);
	ptr = *head;
	for (i = 0; i < num_of_nodes; i++)
	{
		arr[i] = ptr;
		ptr = ptr -> next;
	}

	if(order_option == 1)
	{
		qsort(arr, num_of_nodes, sizeof(g_Word *), g_Compare);	
	}
	else
	{
		g_shuffle(arr, num_of_nodes);
	}

	for (i = 0; i < num_of_nodes; i++)
		arr[i] -> next = NULL;
	for (i = 0; i < num_of_nodes; i++)
		g_InsertWord(&new_head, arr[i]);
	*head = new_head;
	free(arr);
}

void Guessword()
{
	FILE *fp;
	g_Word *wordlist = NULL;
	char day[MAX_FILE_NAME];
	int order_option;

	// 설정 입력
	printf("파일명(일차) : ");
	scanf("%s", day);
	if (!(fp = fopen(strcat(day, ".dic"), "r")))
	{
		printf(" >> 파일 읽기 에러 : 해당 파일이 없습니다. <<\n");
		sleep(2);
		return;
	}
	printf("출력 방식(알파벳 순서대로 : 1, 무작위 : 2) : ");
	scanf("%d", &order_option);

	// file 내 단어들 삽입
	if(g_InsertWords(&wordlist, fp))
	{
		printf(" >> 데이터 파일 에러 : 입력한 파일에 아무 단어도 없습니다. <    <\n");
		sleep(2);
		return ;
	}

	// 알파벳 순/ 무작위
	g_SortWords(&wordlist, order_option);

	system("clear");
	printf(TITLE_g);

	// 단어장 맞추기
	GuessWords(&wordlist);

	// 동적 메모리 할당 해제
	g_FreeWords(&wordlist);

	// 함수 종료 전 화면 초기화
//	system("clear");
}
