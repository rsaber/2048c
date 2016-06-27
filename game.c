#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "powertiles.h"

#define WINDOW_SIZE_WIDTH	80
#define WINDOW_SIZE_HEIGHT 	24

void updateGameView(WINDOW * win, Board b);

int main(int argc, char ** argv){
	if(argc!=2){
		printf("Invalid Arguments!\nRun with: %s -[size]",argv[0]);
		return -1;
	}

	WINDOW * win;
	WINDOW * scorewin;
	initscr();
	clear();
	noecho();
	cbreak();
	curs_set(0);

	Board b = newBoard(atoi(argv[1]));

	win = newwin(getSize(b)+2,getSize(b) + 20,0,2);

	keypad(win,TRUE);
	refresh();
	addRandomTile(b);
	updateGameView(win,b);
	int c = 0;
	while(c!='q'){
		c = wgetch(win);
		switch(c){
			case KEY_UP:
				shiftField(b, SHIFT_UP);
				break;
			case KEY_DOWN:
				shiftField(b, SHIFT_DOWN);
				break;
			case KEY_LEFT:
				shiftField(b, SHIFT_LEFT);
				break;
			case KEY_RIGHT:
				shiftField(b, SHIFT_RIGHT);
				break;
			default:
				refresh();
				break;
		}
		addRandomTile(b);
		updateGameView(win,b);
	}
	destroyBoard(b);
	clrtoeol();
	refresh();
	endwin();
	return 0;
}

void updateGameView(WINDOW * win, Board b){
	box(win, 0, 0);
	int i,j,tmp;
	for(i=1; i<=getSize(b); i++){
		for(j=1; j<=getSize(b); j++){
			if((tmp=getTile(b,i-1,j-1)) != 0) mvwprintw(win,i,j,"%d", tmp);
			else mvwprintw(win,i,j," ");
		}
	}
	for(i=1; i<=getSize(b); i++){
		mvwprintw(win,i, getSize(b)+2,"|");
	}

	mvwprintw(win,1, getSize(b)+4,"2048c:%d",getSize(b));
	mvwprintw(win,2, getSize(b)+4,"Score:");
	mvwprintw(win,3, getSize(b)+4,"%lu",getScore(b));
	
}