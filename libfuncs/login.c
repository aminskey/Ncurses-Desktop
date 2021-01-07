#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<ncurses.h>

#include "acorn.h"


char *login(char *s){

	char lfile[60], binfo[60], name[50], pass[50], inputName[50], inputPass[50];
	short pair, fg, bg;
	int bgch;

	sprintf(lfile,"%s/login",drva);
	sprintf(binfo,"%s/dat",drva);

	drvchck();

	FILE *fp1=fopen(lfile,"r");
	FILE *fp2=fopen(binfo,"r");

	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION,NULL);

	if(fp1 == NULL){
		attron(A_REVERSE);
		mvprintw(0,0,"Could not access login file");
		attroff(A_REVERSE);
		return "-1";
	}

	fscanf(fp2,"%d %hd %hd %hd",&bgch, &pair, &fg, &bg);

	WINDOW *lwin=newwin(MAXY/2, MAXX/2, MAXY/2 - MAXY/4, MAXX/2 - MAXX/4);
	WINDOW *swin=derwin(lwin,getmaxy(lwin)-2,getmaxx(lwin)-2,1,1);
	WINDOW *shdw=newwin(getmaxy(lwin),getmaxx(lwin),getbegy(lwin)+1,getbegx(lwin)+2);

	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_WHITE);
	init_pair(3, bg, fg);
	init_pair(pair, fg, bg);

	paint(bgch,pair);
	refresh();

	wpaint(shdw, bgch, 1);
	wpaint(lwin, 32, 3);

	wrefresh(shdw);
	wrefresh(lwin);

	wattron(swin,COLOR_PAIR(3));

	mvwprintw(swin,5,2,"User Name:");
	for(int i=2+strlen("User Name:");i<40;i++)
		mvwaddch(swin,6,i,ACS_S1);

	mvwprintw(swin,8,2,"Password:");
	for(int i=2+strlen("Password:");i<40;i++)
		mvwaddch(swin,9,i,ACS_S1);
	curs_set(1);
	echo();
	mvwscanw(swin,5,3+strlen("User Name:"),"%s",inputName);

	noecho();
	mvwscanw(swin,8,3+strlen("Password:"),"%s",inputPass);

	if(!strcmp(inputName,"shutdown")){
		endwin();
		exit(0);
	}

	while(!feof(fp1)){
		fscanf(fp1,"%s %s",name, pass);
		if(!strcmp(inputName,name) && !strcmp(inputPass, pass)){
			break;
		}else{

		}
	}
	if(strcmp(inputName,name)){
		login(s);
	}

	wattroff(swin, COLOR_PAIR(3));
	wrefresh(swin);

	sprintf(s,"%s",inputName);

	return s;
}
