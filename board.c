#include <stdio.h>
#include <stdlib.h>
#include "board.h"

#define N_BOARD             15 //칸을 매크로를 사용하여 정의. 15개의 정수 보드 칸이 존재 .
#define N_COINPOS           12 //12개의 칸에 코인을 배치할 것
#define MAX_COIN            4 //최대 4코인까지 놓을 것

#define MAX_SHARKSTEP        6 //상어가 몇 개의 판을 이동할 수 있는 
#define SHARK_INITPOS		-4 //4개 앞에서 상어 처음 위치 선정 

static int board_status[N_BOARD]; //1차원 배열로 몇 번째 칸이 살아있는가 죽어있는가를 판단
static int board_coin[N_BOARD]; //i번째 칸이 동전 몇을 갖고 있는지 저장하는 배열. 

static int board_sharkPosition; //상어가 몇 번째 칸에 있는지 int형으로 변수 하나 잡아두기

int board_initboard(void) //초기화
{
    int i;
    for (i=0;i<N_BOARD;i++)
    {
        board_status[i] = BOARDSTATUS_OK;  //살아있는 판 
        board_coin[i] = 0; //코인은 0으로 초기화
    }
    
    board_sharkPosition =  SHARK_INITPOS;
    
    
    for (i=0;i<N_COINPOS;i++)
    {
        int flag = 0; //초기화를 시키고 깃발이 내려갔을 때만 반복 
        while(flag == 0)
        {
            int allocPos = rand()%N_BOARD; //나머지 연산을 통해 0부터 14까지 숫자 
            if (board_coin[allocPos] == 0)
            {
                board_coin[allocPos] = rand()%MAX_COIN+1; //1에서 4사이의 값의 코인이 랜덤 
                flag = 1; //특정이벤트에서 while문을 나갈 때 깃발을 올린다. 
            }
        }
    }
    
    return 0;
}

int board_printBoardStatus(void) //입력은 void 출력은 int
{
    int i;
    printf("------------- BOARD STATUS ---------------\n");
    for (i=0;i<N_BOARD;i++)
    {
        printf("|");
        if (board_status[i] == BOARDSTATUS_NOK)
            printf("X");
        else
            printf("O");
    }   
    printf("|\n");
    printf("------------------------------------------\n"); 
    
    return 0;
}

int board_getBoardStatus(int pos)  //위치가 파손되었는가를 보기 위해 입력은 위치pos 
{
    return board_status[pos];
}

int board_getBoardCoin(int pos) //입력은 그 위치
{
    int coin = board_coin[pos]; //실제로 동전을 줍는 것이므로 초기화 0이 필요함.
    board_coin[pos] = 0;
    return coin;	//리턴해버리면 함수가 끝나버리므로 새로운 지역변수 coin이 필요하게 됨.	
}	

//int board_getSharkPosition(void);
int board_stepShark(void){ //상어 입력은 필요 없으니 void
	int step = rand()%MAX_SHARKSTEP+1;
	int i;
	for (i=board_sharkPosition+1;i<=board_sharkPosition+step;i++) //원래 상어 위치가 -4 였어서 
	{
		if (i>=0 && i<N_BOARD) //상어위치가 0보다 크면서 최대값보다는 작은범위에 있어야함. 
		board_status[i] = BOARDSTATUS_NOK;
	}
	
	board_sharkPosition += step;
	
	return board_sharkPosition;
	
}

