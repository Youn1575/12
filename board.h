#define BOARDSTATUS_OK       1 //���� ĭ�� 1 �̸� ����ִ� ���̰� 
#define BOARDSTATUS_NOK      0 //���� ĭ�� 0�̸� �׾��ִ� ����. 

int board_initboard(void);//�ʱ�ȭ
int board_printBoardStatus(void); //�Է��� void ����� int

int board_getBoardStatus(int pos); //��ġ�� �ļյǾ��°��� ���� ���� �Է��� ��ġpos
int board_getBoardCoin(int pos); //�Է��� �� ��ġ

//int board_getSharkPosition(void);
//int board_stepShark(void); //��� �Է��� �ʿ� ������ void
