#include<stdio.h> 
#include<conio.h> 
#include<windows.h> 
#include<stdlib.h> 
#include<time.h> 
typedef struct {int x; int y;} POS; 

void gotoxy(int x, int y, char* s)
{ 
    COORD Pos={x*2,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos); 
    printf("%s",s); 
}

void map()  
{
    int i; 
    system("cls");  
    gotoxy(0,0,"#############################################################"); 
    for(i=1;i<20;i++) 
    {
        gotoxy(0,i,"#");
        gotoxy(30,i,"#");
    }
    gotoxy(0,20,"#############################################################\n");

}

void moving(POS* snk, int len) 
{
    static int dir=2021;
    if(kbhit())
    {
        int key; 
        do{key=getch();}while(key==224); 
        switch(key)
        {
            case 72: dir=0;break;
            case 80: dir=1;break; 
            case 75: dir=2;break;
            case 77: dir=3;break;
        }
    }
    if(dir!=2021) 
    {
        int i;
        gotoxy(snk[len-1].x, snk[len-1].y,"  ");
        for(i=len-1;i>0;i--)snk[i]=snk[i-1];
        gotoxy(snk[1].x,snk[1].y," S"); 
    }
    switch(dir) 
    {
        case 0: snk[0].y--;;break;
        case 1: snk[0].y++;break; 
        case 2: snk[0].x--;break;
    	case 3: snk[0].x++;break;
    }
    gotoxy(snk[0].x,snk[0].y," @"); 
}

int game_over(POS* snk, int len)
{
    int i;
    if(snk[0].x==0||snk[0].y==0||snk[0].x==30||snk[0].y==20)return 0; 
    for(i=1;i<len;i++)
    {
        if(snk[0].x==snk[i].x&&snk[0].y==snk[i].y)return 0;
    }
    return 1; 
}


int main()
{
    POS snk[100], food; 
    int i;
	int dir=20212957; 
	int len=5;  
	int score=0; 
    int speed=100; 
    srand(time(NULL));
    map();

    for(i=0;i<len;i++)

    {
        snk[i].x=15+i; 
        snk[i].y=10; 
        gotoxy(snk[i].x,snk[i].y," S");
    }
    food.x=rand()%28+1; 
    food.y=rand()%18+1;
    gotoxy(0,21,"점수 : 0"); 

    while(1) 
    {
        if(game_over(snk,len)==0)
        break;
        
        if(snk[0].x==food.x&&snk[0].y==food.y)
        {
            score+=1; 

            food.x=rand()%28+1; 
            food.y=rand()%18+1; 
            gotoxy(0,21,"점수 : "); 
       
            printf("%d",score); 
            if(speed>10) speed-=5; 
            if(len<100)
            {
                snk[len]=snk[len-1]; 
                len++;
            }

        }
        gotoxy(food.x,food.y,"F"); 
        moving(snk,len);

        Sleep(speed); 
    }
    gotoxy(0,22,"게임 끝\n"); 

}


