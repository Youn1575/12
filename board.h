#define BOARDSTATUS_OK       1 //보드 칸이 1 이면 살아있는 것이고 
#define BOARDSTATUS_NOK      0 //보드 칸이 0이면 죽어있는 것임. 

int board_initboard(void);//초기화
int board_printBoardStatus(void); //입력은 void 출력은 int

int board_getBoardStatus(int pos); //위치가 파손되었는가를 보기 위해 입력은 위치pos
int board_getBoardCoin(int pos); //입력은 그 위치

//int board_getSharkPosition(void);
//int board_stepShark(void); //상어 입력은 필요 없으니 void
