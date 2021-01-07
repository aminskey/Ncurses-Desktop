#include<stdio.h>
#include<ncurses.h>
#include<string.h>
#include<time.h>

#include "acorn.h"

void mzclock(WINDOW *src){
	char str[50];

	int ch=0;
	int col=0;

	short fg=0;
	short bg=0;

	sprintf(str,"%s/.Mzdos/A/dat",home);

	FILE *fp=fopen(str,"r+");

	time_t lctime;
	struct tm *loctime;


	fscanf(fp,"%d %d %hd %hd",&ch,&col,&fg,&bg);

	start_color();
	init_pair(col,fg,bg);
	init_pair(2,COLOR_BLUE,COLOR_WHITE);


	refresh();
	wattron(src,COLOR_PAIR(col));

	box(src,0,0);
	mvwprintw(src,0,(getmaxx(src)-strlen("Clock"))/2,"Clock");

	wattroff(src,COLOR_PAIR(col));
	wrefresh(src);

	wattron(src,COLOR_PAIR(2));

	keypad(src,true);

	while(1){
	        time(&lctime);
	        loctime=localtime(&lctime);


		refresh();
		wattron(src,COLOR_PAIR(col));

		box(src,0,0);
		mvwprintw(src,0,(getmaxx(src)-strlen("Clock"))/2,"Clock");

		wattroff(src,COLOR_PAIR(col));


		mvwprintw(src,1,1,"%dh:%dmin:%ds",loctime->tm_hour,loctime->tm_min,loctime->tm_sec);
		wrefresh(src);

		delay_output(50);

		if(loctime->tm_sec % 60 == 0){
			mvwprintw(src,getmaxy(src)-1,(getmaxx(src)-strlen("Press Buttons To Function"))/2,"Press Buttons To Function");

			int c=wgetch(src);

			if(c==KEY_UP){
				continue;
			}
			if(c==KEY_DOWN){
				break;
			}
		}
		wclear(src);

	}

	wattroff(src,COLOR_PAIR(2));
	wrefresh(src);

	wpaint(src,ch,col);
	wrefresh(src);

	fclose(fp);
}
