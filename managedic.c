#include "managedic.h"

void managedic()//단어장 관리 기능
{
    int num;
    while(1)
    {
	system("clear");
	printf(">> 영어 단어 암기 프로그램 : 단어장 관리 <<\n");
	printf("1. 새 파일 추가하기          2. 새 단어 추가하기\n");
	printf("3. 단어장 보기               4. 단어 파일 목록보기\n");
	printf("5. 단어장 관리 종료\n\n");

	printf("번호를 입력하세요 : ");
	scanf("%d",&num);

	switch(num)
	{
	    case 1:
		file_add();
		break;
	    case 2:
		Word_add();
		break;
	    case 3:
		Words_see();
		break;
	    case 4:
		Word_file_list();
		break;
	    case 5:
		return;
	}
    }
}

void file_add()//새 파일 추가
{
    system("clear");
    printf(">> 영어 단어 암기 프로그램 : 단어장 관리 : 새 파일 추가 <<\n");

    char buf[200], filename[10];
    int cnt=0,space=0;
    m_Word Word;
    FILE *fp,*fp2;
    fp=fopen("dic.list","r+");
    system("ls -v *.dic > dic.list");
    getchar();
    while(1)
    {
	if(fgets(buf,sizeof(buf),fp)!=NULL)
	{
	    ++cnt;
	    continue;
	}
	else
	{
	    sprintf(filename,"%d.dic",cnt+1);
	    fwrite(filename, sizeof(char),strlen(filename),fp);
	    break;
	}
    }
    system("ls -v *.dic > dic.list");
    fclose(fp);

    fp2=fopen(filename,"w+");

    cnt=0;
    while(cnt<20)
    {
	fgets(buf,sizeof(buf),stdin);
	buf[strlen(buf)-1]='\0';

	if(!strcmp(buf,".add"))
	{
	    fflush(fp);
	    break;
	}
	if(cnt!=0)
	    fputs("\n",fp2);

	for(int i=0;i<strlen(buf);i++)
	{
	    if(buf[i]==' ')
		space+=1;
	}

	if(space>3)
	{
	    printf("한글 뜻은 3개까지 입력 가능합니다.\n");
	    space=0;
	    continue;
	}

	sscanf(buf,"%s %s %s %s", Word.spell, Word.mean1, Word.mean2, Word.mean3);

	if(strlen(Word.spell)>15)
	{
	    printf("영어 단어는 최대 15자 까지 입력 가능합니다.\n");
	    sleep(1);
	    return;
	}

	else if(strlen(Word.mean1)>60||strlen(Word.mean2)>60||strlen(Word.mean3)>60)
	{
	    printf("한글 뜻은 1개당 최대 30자 까지 입력 가능합니다.\n");
	    sleep(1);
	    return;
	}
	fwrite(buf, sizeof(char), strlen(buf), fp2);
	fflush(fp2);
	//fputs("\n",fp2);
	space=0;
	cnt++;
    }

    fclose(fp2);
}

void Word_add()//새 단어 추가
{
    FILE *fp;
    char filename[10], buf[200],ch;
    int num,cnt=0,space=0;
    m_Word Word;

    system("clear");
    printf(">>영어 단어 암기 프로그램 : 단어장 관리 : 새 단어 추가 <<\n");
    printf("파일명(일차) : ");
    scanf("%d",&num);

    sprintf(filename, "%d.dic", num);
    fp=fopen(filename,"a");
    getchar();

fseek(fp,-1,SEEK_END);
	ch=fgetc(fp);
	if(ch!='\n')
	    fputs("\n",fp);
	fseek(fp,0,SEEK_END);
	
    printf("단어는 최대 20개 까지 입력 가능합니다. 20개 초과시, 20개 까지만 입력됩니다.\n");

    while(cnt<20)
    {
	fgets(buf,sizeof(buf),stdin);
	buf[strlen(buf)-1]='\0';

	if(!strcmp(buf,".add"))
	    break;
	
	if(cnt!=0)
	    fputs("\n",fp);

	for(int i=0;i<strlen(buf);i++)
	{
	    if(buf[i]==' ')
		space+=1;
	}

	if(space>3)
	{
	    printf("한글 뜻은 3개까지 입력 가능합니다.\n");
	    space=0;
	    continue;
	}

	sscanf(buf,"%s %s %s %s", Word.spell, Word.mean1, Word.mean2, Word.mean3);

	if(strlen(Word.spell)>15)
	{
	    printf("영어 단어는 최대 15자 까지 입력 가능합니다.\n");
	    sleep(1);
	    return;
	}

	if(strlen(Word.mean1)>60||strlen(Word.mean2)>60||strlen(Word.mean3)>60)
	{
	    printf("한글 뜻은 1개당 최대 30자 까지 입력 가능합니다.\n");
	    sleep(1);
	    return;
	}
	//11월 23일 수정 시작 부분
	//11월 23일 수정 끝 부분

	fwrite(buf, sizeof(char), strlen(buf), fp);
	fflush(fp);
	//fputs("\n",fp);
	fflush(fp);
	space=0;
	cnt++;
    }
    fclose(fp);
}

void Words_see()//단어장 보기
{
    FILE *fp;
    int num;
    char buf[200],buf2[200],ch,filename[10];
    printf("파일명(일차) : ");
    scanf("%d",&num);

    sprintf(filename, "%d.dic", num);
    fp=fopen(filename,"r");
    getchar();
    if(fgets(buf2,sizeof(buf2),fp)==NULL)
    {
	printf("파일안에 아무런 내용이 없습니다.\n");
	printf("ENTER 키 입력 시 Main 화면으로 돌아갑니다.\n");
	if((ch=getchar())=='\n')
	    system("clear");
	return;
    }

    printf("-----단어장-----------\n");

    rewind(fp);
    while(fgets(buf,sizeof(buf),fp)!=NULL)
    {
	printf("%s",buf);
    }

    fclose(fp);

    printf("\n"); 
    printf("ENTER 키 입력 시 Main 화면으로 돌아갑니다.\n");
    if((ch=getchar())=='\n')
	return;

}

void Word_file_list()//파일 목록 보기
{
    FILE *fp;
    int num=0;
    char buf[200],ch;
    ch=getchar();
    printf("-----단어 파일 목록-----------\n");
    fp=fopen("dic.list","r");
    system("ls -v  *.dic > dic.list");

    while(fscanf(fp,"%s",buf)!=EOF)
    {
	printf("%10s ",buf);
	num++;
	if(num%5==0)
	    printf("\n");
    }
    fclose(fp);

    printf("\n");
    printf("\n");
    printf("ENTER 키 입력 시 Main 화면으로 돌아갑니다. \n");
    if((ch=getchar())!='\n')
	return;
}
