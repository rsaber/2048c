/*
	* Powertiles
	* Written by Riyasat Saber

	* THINGS TO DO
		- Rewrite ShiftLeft & ShiftUp to ShiftHorz, ShiftVert
		- Check for Game Over
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "powertiles.h"

Board newBoard(int size){
	Board b = malloc(sizeof(struct _board));
	b->size = size;
	b->field = malloc(sizeof(int *) * size);
	int i;
	for(i=0; i<size; i++){
		b->field[i] = calloc(sizeof(int), size);
	}
	b->score = 0;
	return b;
}

void destroyBoard(Board b){
	int i;
	for(i=0; i<b->size; i++) free(b->field[i]);
	free(b->field);
	free(b);
}

int getTile(Board b, int x, int y){
	return b->field[y][x];
}

int getSize(Board b){
	return b->size;
}

unsigned long long getScore(Board b){
	return b->score;
}

static int shiftTileLeft(Board b,int x, int y){
	if(x<=0 || b->field[x][y] == 0) return 0;

	if(b->field[x-1][y] == 0){
		// shift the tile onto the empty block
		b->field[x-1][y] = b->field[x][y];
		b->field[x][y] = 0;
		return 1;
	}

	if(b->field[x-1][y] == b->field[x][y]){
		// merge the tiles
		b->field[x-1][y]++;
		b->field[x][y] = 0;
		b->score+=b->field[x-1][y];
		return 1;
	}

	if(b->field[x-1][y] != 0){
		// can't move any further left
		return 0;
	}
	return 0;
}

static int shiftTileRight(Board b,int x, int y){
	if(x>= b->size-1 || b->field[x][y] == 0) return 0;

	if(b->field[x+1][y] == 0){
		// shift the tile onto the empty block
		b->field[x+1][y] = b->field[x][y];
		b->field[x][y] = 0;
		return 1;
	}

	if(b->field[x+1][y] == b->field[x][y]){
		// merge the tiles
		b->field[x+1][y]++;
		b->field[x][y] = 0;
		b->score+=b->field[x+1][y];
		return 1;
	}

	if(b->field[x+1][y] != 0){
		// can't move any further right
		return 0;
	}
	return 0;
}

static int shiftTileUp(Board b, int x, int y){
	if(y>b->size-1 || y<=0 || b->field[x][y] == 0) return 0;

	if(b->field[x][y-1] == 0){
		// shift the tile onto the empty block
		b->field[x][y-1] = b->field[x][y];
		b->field[x][y] = 0;
		return 1;
	}

	if(b->field[x][y-1] == b->field[x][y]){
		// merge the tiles
		b->field[x][y-1]++;
		b->field[x][y] = 0;
		b->score+=b->field[x][y-1];
		return 1;
	}

	if(b->field[x][y-1] != 0){
		// can't move any further up
		return 0;
	}
	return 0;
}

static int shiftTileDown(Board b, int x, int y){
	if(y>=b->size-1 || b->field[x][y] == 0) return 0;

	if(b->field[x][y+1] == 0){
		// shift the tile onto the empty block
		b->field[x][y+1] = b->field[x][y];
		b->field[x][y] = 0;
		return 1;
	}

	if(b->field[x][y+1] == b->field[x][y]){
		// merge the tiles
		b->field[x][y+1]++;
		b->field[x][y] = 0;
		b->score+=b->field[x][y+1];
		return 1;
	}

	if(b->field[x][y+1] != 0){
		// can't move any further down
		return 0;
	}
	return 0;
}

void shiftField(Board b, char move){
	int i,j;
	switch (move){
		case SHIFT_LEFT:
			for(i=0; i<b->size; i++){
				for(j=0; j<b->size; j++){
					if(shiftTileLeft(b,i,j)) i=j=0;
				}
			}
			break;

		case SHIFT_RIGHT:
			for(i=0; i<b->size; i++){
				for(j=0; j<b->size; j++){
					if(shiftTileRight(b,i,j)) i=j=0;
				}
			}
			break;

		case SHIFT_UP:
			for(i=0; i<b->size; i++){
				for(j=0; j<b->size; j++){
					if(shiftTileUp(b,i,j)) i=j=0;
				}
			}
			break;

		case SHIFT_DOWN:
			for(i=0; i<b->size; i++){
				for(j=0; j<b->size; j++){
					if(shiftTileDown(b,i,j)) i=j=0;
				}
			}
			break;
	}
}

// fix this up
void addRandomTile(Board b){
	srand((unsigned)time(NULL));

	int tile = (rand()  % 2) + 1;
	int x,y;

	do{
		x = rand() % b->size;
		y = rand() % b->size;
	}while(b->field[x][y]!=0);

	b->field[x][y] = tile;
}


