#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "powertiles.h"

#define WINDOW_SIZE_WIDTH	80
#define WINDOW_SIZE_HEIGHT 	24

#define RED	"\x1B[31m"
#define GRN	"\x1B[32m"
#define YEL	"\x1B[33m"
#define BLU	"\x1B[34m"
#define MAG	"\x1B[35m"
#define CYN	"\x1B[36m"
#define WHT	"\x1B[37m"
#define RST	"\x1B[0m"


void updateGameView(WINDOW * win, Board b);

int main(int argc, char ** argv){
	if(argc!=2){
		printf("Invalid Arguments!\nRun with: %s -[size]",argv[0]);
		return -1;
	}

	WINDOW * win;
	initscr();

	start_color();
	use_default_colors();

	clear();
	noecho();
	cbreak();
	curs_set(0);

	Board b = newBoard(atoi(argv[1]));

	win = newwin(getSize(b)+2,getSize(b) + 20,0,2);

	init_pair(1, COLOR_WHITE, COLOR_RED);
	init_pair(2, COLOR_WHITE, COLOR_BLUE);
	init_pair(3, COLOR_WHITE, COLOR_GREEN);
	init_pair(4, COLOR_WHITE, COLOR_YELLOW);
	init_pair(5, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(6, COLOR_WHITE, COLOR_CYAN);
	init_pair(7, COLOR_RED, COLOR_WHITE);
	init_pair(8, COLOR_BLUE, COLOR_WHITE);
	init_pair(9, COLOR_GREEN, COLOR_WHITE);
	init_pair(10, COLOR_YELLOW, COLOR_WHITE);
	init_pair(11, COLOR_MAGENTA, COLOR_WHITE);
	init_pair(12, COLOR_RED, COLOR_WHITE);
	init_pair(13, COLOR_CYAN, COLOR_WHITE);
	init_pair(14, COLOR_MAGENTA, COLOR_RED);
	init_pair(15, COLOR_CYAN, COLOR_BLUE);

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

void printTile(WINDOW * win, int i, int j, int val){
	wattron(win, COLOR_PAIR(val));
	mvwprintw(win,i,j,"%X", val);
	wattroff(win, COLOR_PAIR(val));
}

void updateGameView(WINDOW * win, Board b){
	box(win, 0, 0);
	int i,j,tmp;
	for(i=1; i<=getSize(b); i++){
		for(j=1; j<=getSize(b); j++){
			if((tmp=getTile(b,i-1,j-1)) != 0)
				printTile(win,i,j,tmp);
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