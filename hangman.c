#include "hangman.h"

void h_SplitLine(char *line, char *output[])
{
	char *p = strtok(line, " ");
	output[0] = p; 			// eng 
	output[1] = strtok(NULL, "");	// kor
}

void h_InsertWord(h_Word **head, h_Word *new_Word)
{
	if (*head == NULL)
	{
		*head = new_Word;
		return;
	}
	h_Word *w = *head;
	while (w -> next != NULL)
		w = w -> next;
	w -> next = new_Word;
}

int h_InsertWords(h_Word **head, FILE *fp)
{
	char *output[2];
	int is_empty_file = 1;
	h_Word *w;
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
		w = (h_Word *)malloc(sizeof(h_Word));
		h_SplitLine(line, output);
		w -> eng = (char *)malloc(sizeof(char) * strlen(output[0]) + 1);
		strcpy(w -> eng, output[0]);
		w -> kor = (char *)malloc(sizeof(char) * strlen(output[1]) + 1);
		strcpy(w -> kor, output[1]);
		w -> next = NULL;
		h_InsertWord(head, w);
	}
	if (is_empty_file) // check whether given dic file is empty or not
	{
		fclose(fp);
		return -1;
	}
	fclose(fp);
	return 0;
}

void h_FreeWords(h_Word **head)
{
	h_Word *w = *head;
	while (w != NULL)
	{
		h_Word *tmp = w;
		free(tmp -> eng);
		free(tmp -> kor);
		free(tmp);
		w = w -> next;
	}
}

void GetRandomWord(h_Word **head, h_Word **target_word)
{
    h_Word *ptr = *head;
    int num_of_nodes = 0, random_value, i;

    while (ptr != NULL)
	{
		ptr = ptr -> next;
		num_of_nodes++;
	}

    srand(time(NULL));
    random_value = rand() % num_of_nodes;

    ptr = *head;
    for (i = 0; i < random_value; i++)
    {
        ptr = ptr -> next;
    }
    *target_word = ptr;
}

void PrintHangman(int num_of_errors)
{
    if (num_of_errors >= 0) printf("-------------------+\n");
    if (num_of_errors >= 1) printf("                   O\n");
    if (num_of_errors >= 2) printf("                 / ");
    if (num_of_errors >= 3) printf("|");
    if (num_of_errors >= 4) printf("\\\n");
    if (num_of_errors >= 5) printf("                  /");
    if (num_of_errors >= 6) printf(" \\");

    if (num_of_errors == 0) printf("\n\n\n");
    else if (num_of_errors == 1 || num_of_errors == 2 || num_of_errors == 3) printf("\n\n");
    else printf("\n");
    
    printf("\n\n");
}

void MyFlush()
{
    while (getchar() != '\n')
            ;
}

int IsCorrectAnswer(char *correct_char, int eng_len)
{
    int i;
    for (i = 0; i < eng_len; i++)
    {
        if (!correct_char[i])
        {
            return 0;
        }
    }

    return 1;
}

int UpdateCorrectArr(char *correct_char, char *eng, int eng_len, char ch)
{
    int i, is_correct = 0;
    for (i = 0; i < eng_len; i++)
    {
        if (eng[i] == ch)
        {
            correct_char[i] = 1;
            is_correct = 1;
        }
    }
    return (is_correct == 1 ? 1 : 0);
}

void PrintCurrentText(char *correct_char, char *eng, int eng_len)
{
    int i;
    for (i = 0; i < eng_len; i++)
    {
        if (correct_char[i])
        {
            printf("%c ", eng[i]);
        }
        else
        {
            printf("_ ");
        }    
    }
    printf("\n\n");
}

void PlayHangman(h_Word *target_word)
{
    int i, num_of_errors = 0, num_of_try = 1, eng_len;
    char *correct_char, input_char, ch;

    eng_len = strlen(target_word->eng);
    correct_char = malloc(eng_len);

    for (i = 0; i < eng_len; i++)
    {
        correct_char[i] = 0;
    }

    MyFlush();
    while(1)
    {
        system("clear");
        printf(TITLE_H); 
        printf("\n(힌트) %s\n\n", target_word->kor);

        PrintHangman(num_of_errors);
        PrintCurrentText(correct_char, target_word->eng, eng_len);

        printf("%d번째 시도 : ", num_of_try);
        scanf("%c", &input_char);
        MyFlush();

        if(!UpdateCorrectArr(correct_char, target_word->eng, eng_len, input_char))
        {
            num_of_errors++;
        }

        if (IsCorrectAnswer(correct_char, eng_len))
        {
            printf(MSG_SUCCESS);
            printf("ENTER 키 입력 시 Main 화면으로 돌아갑니다.\n");
            while ((ch = getchar()) !='\n')
                ;
            break;
        }
        if (num_of_errors == 6)
        {
            system("clear");
            printf(TITLE_H); 
            printf("\n(힌트) %s\n\n", target_word->kor);

            PrintHangman(num_of_errors);
            PrintCurrentText(correct_char, target_word->eng, eng_len);
            
            printf(MSG_FAIL);
            printf("ENTER 키 입력 시 Main 화면으로 돌아갑니다.\n");
            while ((ch = getchar()) !='\n')
                ;
            break;
        }

        num_of_try++;
    }
	free(correct_char);
}

void Hangman()
{
	FILE *fp;
	h_Word *wordlist = NULL, *target_word = NULL;
	char day[MAX_FILE_NAME];

	printf("파일명(일차) : ");
	scanf("%s", day);
	if (!(fp = fopen(strcat(day, ".dic"), "r")))
	{
		printf(" >> 파일 읽기 에러 : 해당 파일이 없습니다. <<\n");
		sleep(SYSTEM_SLEEP_SPEED);
		return;
	}

	// file 내 단어들 삽입
	if(h_InsertWords(&wordlist, fp))
	{
		printf(" >> 데이터 파일 에러 : 입력한 파일에 아무 단어도 없습니다. <<\n");
		sleep(SYSTEM_SLEEP_SPEED);
		return;	
	}

    // 랜덤으로 word node 중 하나 선택
    GetRandomWord(&wordlist, &target_word);

    printf("%s %s\n", target_word->eng, target_word->kor);
    // 행맨게임 메인 파트
    PlayHangman(target_word);

	// 동적 메모리 할당 해제
	h_FreeWords(&wordlist);
}
