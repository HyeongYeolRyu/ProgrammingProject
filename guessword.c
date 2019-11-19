#include "guessword.h"

void jin_SplitLine(char *line, char *output[])
{
    char *p = strtok(line, " ");
    output[0] = p;                 // eng
    output[1] = strtok(NULL, "");  // kor
}

void jin_InsertWord(g_Word **head, g_Word *new_Word)
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

void jin_InsertWords(g_Word **head, FILE *fp)
{
    char *output[2];
    g_Word *w;
    char line[MAX_LEN_OF_INPUT];
    while (fgets(line, sizeof(line), fp))
    {
        int line_len = strlen(line);
        if (line[line_len - 1] == '\n')
            line[line_len - 1] = '\0';
        w = (g_Word *)malloc(sizeof(g_Word));
        jin_SplitLine(line, output);
        w -> eng = (char *)malloc(sizeof(char) * strlen(output[0]) + 1);
        strcpy(w -> eng, output[0]);
        w -> kor = (char *)malloc(sizeof(char) * strlen(output[1]) + 1);
        strcpy(w -> kor, output[1]);
        w -> next = NULL;
        jin_InsertWord(head, w);
    }
    fclose(fp);
}

void GuessWords(g_Word **head)
{
    g_Word *ptr = *head;
    char an[MAX_LEN_OF_INPUT];
    float score=0;
    int cnt_all=0,cnt_cor=0;
    while (strcmp(an,".quit") != 0)
    {
        printf("%s -> ", ptr->kor);
        scanf("%s",an);
        if(strcmp(an,ptr->eng) == 0) {
            printf("correct!\n");
            ++cnt_cor;
        }
        else
            printf("incorrect!\n");
        ptr = ptr -> next;
        ++cnt_all;
    }
    score = (float)cnt_cor/(float)cnt_all * 100;
    printf("당신의 점수는 %.2f 점입니다.\n",score);
}

void jin_FreeWords(g_Word **head)
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

int jin_Compare(const void *p, const void *q)
{
    return strcmp((*(g_Word **)p)->eng, (*(g_Word **)q)->eng);
}

void jin_SortWords(g_Word **head)
{
    int i, num_of_node = 0;
    g_Word *ptr = *head, *new_head = NULL, **arr;

    while (ptr != NULL)
    {
        ptr = ptr -> next;
        num_of_node++;
    }
    arr = (g_Word **)malloc(sizeof(g_Word *) * num_of_node);
    ptr = *head;
    for (i = 0; i < num_of_node; i++)
    {
        arr[i] = ptr;
        ptr = ptr -> next;
    }

    qsort(arr, num_of_node, sizeof(g_Word *), jin_Compare);
    for (i = 0; i < num_of_node; i++)
        arr[i] -> next = NULL;
    for (i = 0; i < num_of_node; i++)
        jin_InsertWord(&new_head, arr[i]);
    *head = new_head;
    free(arr);
}

void Guessword()
{
    FILE *fp;
    g_Word *wordlist = NULL;
    char day[MAX_FILE_NAME];
    int print_way;

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
    scanf("%d", &print_way);

    // file 내 단어들 삽입
    jin_InsertWords(&wordlist, fp);

    // 알파벳 순으로 정렬할 경우
    if (print_way == 1)
        jin_SortWords(&wordlist);

    system("clear");
    printf(TITLE_jin);

    // 단어장 맞추기
    GuessWords(&wordlist);

    // 동적 메모리 할당 해제
    jin_FreeWords(&wordlist);

    // 함수 종료 전 화면 초기화
    system("clear");
}
