#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <termio.h>


typedef struct _word {
  char* eng;
  char* kor;
  struct _word* next;
} word;

typedef struct _list {
  int count;
  word* head;
} list;

list* word_list[4];

void word_add(list* list, char eng[], char kor[]) {
   word* new = (word*)malloc(sizeof(word));

  new->eng = (char*)calloc(strlen(eng)+1, sizeof(char));
  strcpy(new->eng, eng);

  new->kor = (char*)calloc(strlen(kor)+1, sizeof(char));
  strcpy(new->kor, kor);
  if(list->count == 0) {        //리스트에 아무것도 없을 때
    new->next = list->head;     //new의 다음 노드는 리스트의 첫번째 노드(NULL)
    list->head = new;           //리스트의 헤드는 new
  }                             //
  else {                        //리스트에 노드가 하나 이상 있을 때
      word* tmp = list->head;   //tmp : 회원 리스트의 첫번째 노드
      int i;
      for(i = 1; i < list->count; i++) {
         tmp = tmp->next;
      }                           //마지막 노드를 찾을 때 까지 다음 노드로 넘김
      new->next = tmp->next;      //new의 다음 노드는 tmp의 다음 노드
      tmp->next = new;            //tmp의 다음 노드는 new
   }
   list->count++;
}

void list_init(list* list) {
  //회원 리스트 초기화 함수
   list->count = 0;
   list->head = NULL;
}

void list_read(list* list, int num) {
  //회원 노드 불러오기 함수
  char filename[10];
  sprintf(filename, "%d.dic", num);
  FILE *fp = fopen(filename, "r");
  char text[300];
  int i = 0;
  while(1) {
       if(fgets(text, 400, fp) == NULL) {
            break;
       }
      char a[30], b[30];
      char* ptr;
      ptr = strtok(text, " ");
      strcpy(a, ptr);
      ptr = strtok(NULL, " ");
      strcpy(b, strtok(ptr, "\n"));
      word_add(list, a, b);
   }
   fclose(fp);

}

int getch(void){                  // 한 문자만 받는 함수
    int ch;
    struct termios buf, save;
    tcgetattr(0,&save);
    buf = save;
    buf.c_lflag &= ~(ICANON|ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &buf);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &save);
    return ch;
}

void HangMan_print(char* mean_word, int wrong_num, char* now_text) {
  printf("%c", system("clear"));
  printf(">> 영어 단어 암기 프로그램 : 행맨 <<\n");
  printf("(힌트) %s\n", mean_word);
  printf("\n--------------------------+");
  printf("\n\t\t\t");
  if(wrong_num >= 1)  printf("　O");
  printf("\n\t\t\t");
  if(wrong_num == 2) printf("　|");
  else if(wrong_num == 3) printf(" /|");
  else if(wrong_num >= 4) printf(" /|\\");
  printf("\n\t\t\t ");
  if(wrong_num == 5) printf("/");
  else if(wrong_num >= 6) printf("/ \\");
  printf("\n\n");
  for(int i = 0; i < strlen(now_text); i++) {
    printf("%c ", now_text[i]);
  }
}

int HangMan() {
  int num;
  printf("파일명(일차) : ");
  scanf("%d",&num);

  getch();

  if(word_list[num]->count == 0)
  {
    while(1) {
      printf("%c", system("clear"));

      printf("파일안에 아무런 내용이 없습니다.\n");
      printf("ENTER 키 입력 시 Main 화면으로 돌아갑니다.\n");
      if((getchar())=='\n') return 0;
    }
  }


  srand(time(NULL));
  int rnd = rand()%(word_list[num]->count);

  word* tmp = word_list[num]->head;
  int now = 0;
  while(now != rnd) {
    tmp = tmp->next;
    now++;
  }

  char *Word = (char*)calloc(strlen(tmp->eng)+1, sizeof(char));
  strcpy(Word, tmp->eng);

  char *Mean = (char*)calloc(strlen(tmp->kor)+1, sizeof(char));
  strcpy(Mean, tmp->kor);

  int wrong_num = 0;
  char* Now_word = (char*)calloc(strlen(Word)+1, sizeof(char));
  int result = 0;
  for(int i = 0; i < strlen(Word); i++) {
    Now_word[i] = '_';
  }
  int i = 1;
  HangMan_print(Mean, wrong_num, Now_word);
  printf("\n%d번째 시도 : ", i);
  while(1) {
    i++;
    char ch = getch();
    char cts[2];
    cts[0] = ch;
    cts[1] = '\0';
    if(!strstr(Now_word, cts) && strstr(Word, cts)) {
      for(int i = 0; i < strlen(Now_word); i++) {
        if(Word[i] == ch) {
          Now_word[i] = ch;
        }
      }
    } else {
      wrong_num++;
    }
    HangMan_print(Mean, wrong_num, Now_word);

    if(strstr(Now_word, "_"))
      printf("\n%d번째 시도 : ", i);
    else {
      result++;
      break;
    }
    if(wrong_num >= 6) break;
  }

  while(1) {
    HangMan_print(Mean, wrong_num, Now_word);
    if(result) printf("#####################\n### Congratulations!!! #####################");
    else printf("실패!");
    if(strstr(Now_word, "_"))
      printf("\n%d번째 시도 : ", i);
    printf("\n\nENTER키를 누르시면 메뉴로 돌아갑니다…");
    if(getch() == '\n') {
      return 0;
    }
  }
}

int main() {
  for(int i = 1; i <= 3; i++) {
    word_list[i]= (list*)malloc(sizeof(list));
    list_init(word_list[i]);
    list_read(word_list[i], i);
  }

  HangMan();
  printf("프로그램 종료");
}
