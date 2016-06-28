/*
	* Powertiles
	* Header File
*/

#define SHIFT_LEFT 	0
#define SHIFT_RIGHT 1
#define SHIFT_UP 	2
#define SHIFT_DOWN 	3

typedef struct _board{
	int ** field;
	int size;
	unsigned long long score;
}*Board;

Board newBoard(int size);
void destroyBoard(Board b);

int getTile(Board b, int x, int y);
int getSize(Board b);
unsigned long long getScore(Board b);

void shiftField(Board b, char move);
void addRandomTile(Board b);

static int shiftTileLeft(Board b,int x, int y);
static int shiftTileRight(Board b,int x, int y);
static int shiftTileUp(Board b, int x, int y);
static int shiftTileDown(Board b, int x, int y);