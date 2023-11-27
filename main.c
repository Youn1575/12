#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

#define MAX_CHARNAME	200 
#define N_PLAYER		3
#define MAX_DIE			6

#define PLAYERSTATUS_LIVE	0 //플레이어 형태를 정수로 나타냄 
#define PLAYERSTATUS_DIE	1 //플레이어가 죽으면 1 
#define PLAYERSTATUS_END	2 //끝까지 살아남아서 이기면 2 

//플레이어에 관한 전역변수를 잡음. 매크로 및 전역변수로 모델링을 한다. 
//플레이어의 상태에 대한 것을 저장, 모든 것은 배열로 선언
int player_position[N_PLAYER]; // 플레이어 위치 
char player_name[N_PLAYER][MAX_CHARNAME]; // 2차원 배열로  
int player_coin[N_PLAYER];//누적되는 동전의 갯수 정의
int player_status[N_PLAYER]; //3가지의 값을 가질 것.  0,1,2
char player_statusString[3][MAX_CHARNAME]={"LIVE", "DIE", "END"}; //출력할 것 

// if (player_status[0] == PLAYERSTATUS_DIE) 이런 용도로 사용가능 

void opening(void){
	printf("==========================================\n");
	printf("              ※ shark  game ※           \n");
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
					if (board_getBoardStatus(i) == BOARDSTATUS_NOK) //i번째 칸이 파손됐다면, 
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

    // 각 플레이어의 최종 상태 출력
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
	
	//1.초기화 & 플레이어 이름 결정
	board_initboard();
	
	//1-2. 18p 
	for (i=0;i<N_PLAYER;i++) //반복적으로 나타날 것 같은 것은 반복문 이용 
	{
		player_position[i] = 0;
		player_coin[i] = 0;
		player_status[i] = PLAYERSTATUS_LIVE;
		printf("Player %i's name : ", i); //몇 번째 플레이어의 이름을 쓰시오. 
		scanf("%s", player_name[i]); //입력을 받아야함.  이거 자체가 포인터라 &필요없음. 
	}
	
//2. 반복문 (플레이어 턴)
  do {
    int step = rolldie();
    int coinResult;
    char c;
    
    // 얘가 끝난 것인지 아직 하고 있는 건지, 반복문에서 아래 쪽 코드를 할거냐, 말거냐? 를 짜야함.
	if(player_status[turn] != PLAYERSTATUS_LIVE) //플레이어가 주사위를 돌리면 안 되는, 즉 종료된 상황일 때. 
	{
		turn = (turn+1)%N_PLAYER;
		continue; //아래 것을 실행 안 하고 바로 위로 올라갈 것  
	}
    board_printBoardStatus();
    
	//2-1. 플레이어의 상태 출력
	for (i=0; i<N_PLAYER;i++)
		printPlayerPosition(i);
	printPlayerStatus();		
		
				
	//2-2. 주사위 던지기 
	printf("%s turn!!", player_name[turn]);
	printf("Press any key to roll a die!\n");
	scanf("%d", &c); //한 번 멈추게 하기 위해 입력을 받고 싶다... 
	fflush(stdin); //입출력할 때 버퍼의 개념, 입력을 하면 버퍼에 쌓였다가 프로그램으로 들어오기 때문에 버퍼에 원래 값이 남아있다면 그것을 제거해줘야함. 버퍼에 들어있는게 다시 들어오게 되므로 그냥 scanf가 넘어가는 경우가 생김. 입력을 해야만 넘어간다! 하려면 버퍼 플러쉬 필요. 
	step = rolldie();

	//2-3. 이동 
	player_position[turn] += step; //  pos += step;
	//예외 사항 퍼리 필요, 플레이어가 이동했는데 이동한 위치가  player_position[turn] >= N_BOARD 를 넘어가면 안 된다. 
	if(player_position[turn] > N_BOARD)
	{
		player_status[turn] = PLAYERSTATUS_END; 
	}
	if (player_position[turn] == N_BOARD-1){ //14로 이동시키면 됨.
		player_status[turn] = PLAYERSTATUS_END;
	}
	// printf() : 얘는 적절하게 어디까지 이동했습니다 

    //2-4. 동전 줍기
    coinResult = board_getBoardCoin(pos);
    player_coin[turn] +=coinResult;
    //동전을 주웠다고 알려주는 출력문 
	if (coinResult > 0)
	{
    printf("Lucky! %s got %d coins!\n", player_name[turn], coinResult);
	}
	//2-5. 다음 턴 
	turn = (turn+1)%N_PLAYER;//wrap around 제자리로 돌아가게끔. 나머지 연산으로 처리 
	
	//2-6. if(조건 : 모든 플레이어가 한 번씩 턴을 돈다.)
		//상어 동작 구현 
    if(turn==0)
	{
    		int shark_pos = board_stepShark(); //stepShark 구 
    		printf("Shark moved to %i\n", shark_pos);
    		checkDie(); //상어가 죽이는 함수 
    		
	}

	} while(game_end() == 0 ); // return값이 맞다 아니다를 ... 	
	
	// 3. 정리 (승자 계산, 출력 등) 
	

   // 게임 종료 후 결과 출력
    printGameResult();
	
  system("PAUSE");	
  return 0;
}
