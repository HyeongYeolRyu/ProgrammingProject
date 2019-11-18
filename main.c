#include "common.h"
#include "flashcard.h"
#include "managedic.h"

int main()
{
	char select = -1;
	while (select != '5')
	{
		system("clear");
		printf(">> 영어 단어 암기 프로그램 <<\n");
		printf("1. 영어 단어 맞추기    2. 플래쉬카드\n");
		printf("3. 행맨(hangman)       4. 단어장 관리\n");
		printf("5. 프로그램 종료\n\n");
		printf("번호를 선택하세요 : ");
		scanf(" %c", &select);
		switch (select)
		{
			case '1': //myfunc1
					break;
			case '2': //Flashcard();
					break;
			case '3': //myfunc3 
					break;
			case '4': managedic(); 
					break;
			case '5': 
				printf("\n프로그램을 종료합니다.\n");	
				sleep(2);
				break;
			default: 
				printf("\n메뉴를 다시 선택하십시오.\n");
				sleep(2);
				break;
		}
	}
	system("clear");

	return 0;
}
