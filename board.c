#include <stdio.h>
#include <stdlib.h>
#include "board.h"

#define N_BOARD             15 //ĭ�� ��ũ�θ� ����Ͽ� ����. 15���� ���� ���� ĭ�� ���� .
#define N_COINPOS           12 //12���� ĭ�� ������ ��ġ�� ��
#define MAX_COIN            4 //�ִ� 4���α��� ���� ��

#define MAX_SHARKSTEP        6 //�� �� ���� ���� �̵��� �� �ִ� 
#define SHARK_INITPOS		-4 //4�� �տ��� ��� ó�� ��ġ ���� 

static int board_status[N_BOARD]; //1���� �迭�� �� ��° ĭ�� ����ִ°� �׾��ִ°��� �Ǵ�
static int board_coin[N_BOARD]; //i��° ĭ�� ���� ���� ���� �ִ��� �����ϴ� �迭. 

static int board_sharkPosition; //�� �� ��° ĭ�� �ִ��� int������ ���� �ϳ� ��Ƶα�

int board_initboard(void) //�ʱ�ȭ
{
    int i;
    for (i=0;i<N_BOARD;i++)
    {
        board_status[i] = BOARDSTATUS_OK;  //����ִ� �� 
        board_coin[i] = 0; //������ 0���� �ʱ�ȭ
    }
    
    board_sharkPosition =  SHARK_INITPOS;
    
    
    for (i=0;i<N_COINPOS;i++)
    {
        int flag = 0; //�ʱ�ȭ�� ��Ű�� ����� �������� ���� �ݺ� 
        while(flag == 0)
        {
            int allocPos = rand()%N_BOARD; //������ ������ ���� 0���� 14���� ���� 
            if (board_coin[allocPos] == 0)
            {
                board_coin[allocPos] = rand()%MAX_COIN+1; //1���� 4������ ���� ������ ���� 
                flag = 1; //Ư���̺�Ʈ���� while���� ���� �� ����� �ø���. 
            }
        }
    }
    
    return 0;
}

int board_printBoardStatus(void) //�Է��� void ����� int
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

int board_getBoardStatus(int pos)  //��ġ�� �ļյǾ��°��� ���� ���� �Է��� ��ġpos 
{
    return board_status[pos];
}

int board_getBoardCoin(int pos) //�Է��� �� ��ġ
{
    int coin = board_coin[pos]; //������ ������ �ݴ� ���̹Ƿ� �ʱ�ȭ 0�� �ʿ���.
    board_coin[pos] = 0;
    return coin;	//�����ع����� �Լ��� ���������Ƿ� ���ο� �������� coin�� �ʿ��ϰ� ��.	
}	

//int board_getSharkPosition(void);
int board_stepShark(void){ //��� �Է��� �ʿ� ������ void
	int step = rand()%MAX_SHARKSTEP+1;
	int i;
	for (i=board_sharkPosition+1;i<=board_sharkPosition+step;i++) //���� ��� ��ġ�� -4 ��� 
	{
		if (i>=0 && i<N_BOARD) //�����ġ�� 0���� ũ�鼭 �ִ밪���ٴ� ���������� �־����. 
		board_status[i] = BOARDSTATUS_NOK;
	}
	
	board_sharkPosition += step;
	
	return board_sharkPosition;
	
}

