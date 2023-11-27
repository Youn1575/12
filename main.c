#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

#define MAX_CHARNAME	200 
#define N_PLAYER		3
#define MAX_DIE			6

#define PLAYERSTATUS_LIVE	0 //�÷��̾� ���¸� ������ ��Ÿ�� 
#define PLAYERSTATUS_DIE	1 //�÷��̾ ������ 1 
#define PLAYERSTATUS_END	2 //������ ��Ƴ��Ƽ� �̱�� 2 

//�÷��̾ ���� ���������� ����. ��ũ�� �� ���������� �𵨸��� �Ѵ�. 
//�÷��̾��� ���¿� ���� ���� ����, ��� ���� �迭�� ����
int player_position[N_PLAYER]; // �÷��̾� ��ġ 
char player_name[N_PLAYER][MAX_CHARNAME]; // 2���� �迭��  
int player_coin[N_PLAYER];//�����Ǵ� ������ ���� ����
int player_status[N_PLAYER]; //3������ ���� ���� ��.  0,1,2
char player_statusString[3][MAX_CHARNAME]={"LIVE", "DIE", "END"}; //����� �� 

// if (player_status[0] == PLAYERSTATUS_DIE) �̷� �뵵�� ��밡�� 

void opening(void){
	printf("==========================================\n");
	printf("              �� shark  game ��           \n");
	printf("==========================================\n");
}


int rolldie(void)
{
    return rand()%MAX_DIE+1;
}

void printPlayerPosition(int player)
		{
			int i;
			for (i=0; i<N_BOARD; i++)
			{
				printf("|");
				if (i == player_position[player])
					printf("%c", player_name[player][0]);
				else
				{
					if (board_getBoardStatus(i) == BOARDSTATUS_NOK) //i��° ĭ�� �ļյƴٸ�, 
						printf("X");
					else
						printf(" ");
				}
			}
		printf("|\n");			
}

void printPlayerStatus(void)
{
	int i;
	printf("player status ---\n");
	
	for(i=0;i<N_PLAYER;i++)
	{
		printf("%s : pos %i, coin %i, status %s\n", 
		player_name[i], player_position[i], player_coin[i], player_statusString[player_status[i]]);
		printPlayerPosition(i);
	}
	printf("--------------\n");
}


void checkDie(void) 
{
	int i;
	for (i=0; i<N_PLAYER; i++)
		if(board_getBoardStatus(player_position[i]) == BOARDSTATUS_NOK)
		player_status[i]=PLAYERSTATUS_DIE;
}

int game_end(void)
{
	int i;
	int flag_end = 1;
	
	for(i=0; i<N_PLAYER; i++)
	{
		if (player_status[i] == PLAYERSTATUS_LIVE)
		{
			flag_end = 0;
			break;
		}
	}
	return flag_end;
}

int getAlivePlayer(void)
{
	int i;
	int cnt = 0;
	for (i=0; i<N_PLAYER; i++)
	{
		if (player_status[i] != PLAYERSTATUS_DIE)//////////////////////////////
			cnt++;
	}
	return cnt;
}

int getWinner(void)
{
    int i;
    int winner = 0;
    int max_coin = -1;

    for (i = 0; i < N_PLAYER; i++)
    {
        if (player_coin[i] > max_coin)
        {
            max_coin = player_coin[i];
            winner = i;
        }
    }
    return winner;
}






void printGameResult(void)
{
    int alivePlayers = getAlivePlayer();
    int winner = getWinner();

    printf("GAME END!\n");

    if (alivePlayers > 1)
    {
        printf("%d players are alive! Winner is %s\n", alivePlayers, player_name[winner]);
    }
    else
    {
        printf("Winner is %s\n", player_name[winner]);
    }

    // �� �÷��̾��� ���� ���� ���
    for (int i = 0; i < N_PLAYER; ++i)
    {
        printf("%s's final status: pos %d, coin %d, status %s\n",
               player_name[i], player_position[i], player_coin[i], player_statusString[player_status[i]]);
    }
}



int main(int argc, char *argv[])
{
  int pos=0;
  int i;
  int turn = 0;
  
  srand((unsigned)time(NULL));
  
  	//opening 
	opening();
	
	//1.�ʱ�ȭ & �÷��̾� �̸� ����
	board_initboard();
	
	//1-2. 18p 
	for (i=0;i<N_PLAYER;i++) //�ݺ������� ��Ÿ�� �� ���� ���� �ݺ��� �̿� 
	{
		player_position[i] = 0;
		player_coin[i] = 0;
		player_status[i] = PLAYERSTATUS_LIVE;
		printf("Player %i's name : ", i); //�� ��° �÷��̾��� �̸��� ���ÿ�. 
		scanf("%s", player_name[i]); //�Է��� �޾ƾ���.  �̰� ��ü�� �����Ͷ� &�ʿ����. 
	}
	
//2. �ݺ��� (�÷��̾� ��)
  do {
    int step = rolldie();
    int coinResult;
    char c;
    
    // �갡 ���� ������ ���� �ϰ� �ִ� ����, �ݺ������� �Ʒ� �� �ڵ带 �Ұų�, ���ų�? �� ¥����.
	if(player_status[turn] != PLAYERSTATUS_LIVE) //�÷��̾ �ֻ����� ������ �� �Ǵ�, �� ����� ��Ȳ�� ��. 
	{
		turn = (turn+1)%N_PLAYER;
		continue; //�Ʒ� ���� ���� �� �ϰ� �ٷ� ���� �ö� ��  
	}
    board_printBoardStatus();
    
	//2-1. �÷��̾��� ���� ���
	for (i=0; i<N_PLAYER;i++)
		printPlayerPosition(i);
	printPlayerStatus();		
		
				
	//2-2. �ֻ��� ������ 
	printf("%s turn!!", player_name[turn]);
	printf("Press any key to roll a die!\n");
	scanf("%d", &c); //�� �� ���߰� �ϱ� ���� �Է��� �ް� �ʹ�... 
	fflush(stdin); //������� �� ������ ����, �Է��� �ϸ� ���ۿ� �׿��ٰ� ���α׷����� ������ ������ ���ۿ� ���� ���� �����ִٸ� �װ��� �����������. ���ۿ� ����ִ°� �ٽ� ������ �ǹǷ� �׳� scanf�� �Ѿ�� ��찡 ����. �Է��� �ؾ߸� �Ѿ��! �Ϸ��� ���� �÷��� �ʿ�. 
	step = rolldie();

	//2-3. �̵� 
	player_position[turn] += step; //  pos += step;
	//���� ���� �۸� �ʿ�, �÷��̾ �̵��ߴµ� �̵��� ��ġ��  player_position[turn] >= N_BOARD �� �Ѿ�� �� �ȴ�. 
	if(player_position[turn] > N_BOARD)
	{
		player_status[turn] = PLAYERSTATUS_END; 
	}
	if (player_position[turn] == N_BOARD-1){ //14�� �̵���Ű�� ��.
		player_status[turn] = PLAYERSTATUS_END;
	}
	// printf() : ��� �����ϰ� ������ �̵��߽��ϴ� 

    //2-4. ���� �ݱ�
    coinResult = board_getBoardCoin(pos);
    player_coin[turn] +=coinResult;
    //������ �ֿ��ٰ� �˷��ִ� ��¹� 
	if (coinResult > 0)
	{
    printf("Lucky! %s got %d coins!\n", player_name[turn], coinResult);
	}
	//2-5. ���� �� 
	turn = (turn+1)%N_PLAYER;//wrap around ���ڸ��� ���ư��Բ�. ������ �������� ó�� 
	
	//2-6. if(���� : ��� �÷��̾ �� ���� ���� ����.)
		//��� ���� ���� 
    if(turn==0)
	{
    		int shark_pos = board_stepShark(); //stepShark �� 
    		printf("Shark moved to %i\n", shark_pos);
    		checkDie(); //�� ���̴� �Լ� 
    		
	}

	} while(game_end() == 0 ); // return���� �´� �ƴϴٸ� ... 	
	
	// 3. ���� (���� ���, ��� ��) 
	

   // ���� ���� �� ��� ���
    printGameResult();
	
  system("PAUSE");	
  return 0;
}
