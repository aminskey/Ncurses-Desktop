#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ncurses.h>
#include<unistd.h>

#include<acorn.h>
#include<cmd_acornDOS.h>

int edit(MEVENT evnt){

	noecho();
	cbreak();

	int c;
	char pwd[100];
	int ln=0;
	int rst;

	char appdata[100];

	drvchck();

	if(chdir(drvc)!=-1){

	}else{
		bluescreen("Cannot change dir");
	}

	WINDOW *warn=newwin(20,60,10,50);
	WINDOW *info=derwin(warn,18,58,1,1);
	WINDOW *yes=newwin(6,9,getbegy(warn)+7,getbegx(warn)+20);
	WINDOW *no=newwin(6,9,getbegy(warn)+7,getbegx(warn)+40);


	start_color();
	init_pair(1,COLOR_WHITE,COLOR_RED);
	init_pair(2,COLOR_WHITE,COLOR_GREEN);


	wpaint(warn,32,1);

	wattron(warn,COLOR_PAIR(1));
	box(warn,0,0);
	mvwprintw(warn,0,(getmaxx(warn)-strlen("--|  Warning!!  |--"))/2,"-=|  Warning!!  |=-");
	wrefresh(warn);

	sprintf(appdata,"%s/%%AppData%%/edit/warn.txt",drvz);

	wattron(info, COLOR_PAIR(1));

	getcwd(pwd,100);

	more(info,appdata,ln);
	mvwprintw(info,4,ln+1,"pwd:%s",pwd);

	int t;

	for(int i=0;i<getmaxy(info);i++){
		for(int j=0;j<getmaxx(info);j++){
			t=mvwinch(info,i,j);
			mvwprintw(info,i,j,"%c",t);
		}
	}

	wattroff(info, COLOR_PAIR(1));
	wrefresh(info);

	while(c != KEY_F(1)){
		if(c == 'Y' || c == 'y'){
			system("Edit");
			rst=SYS_RESTART;
			break;
		}
		if(c == 'n' || c == 'N'){
			rst=0;
			break;
		}
		c=getch();
	}


	wattroff(warn,COLOR_PAIR(1));

	wrefresh(warn);

	wpaint(warn,32,0);
	wrefresh(warn);
	delwin(warn);

	echo();
	curs_set(0);

	return rst;
}
