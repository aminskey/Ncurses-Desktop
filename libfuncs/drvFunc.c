#include<ncurses.h>
#include<strings.h>
#include<string.h>
#include<unistd.h>

#include "acorn.h"


void bluescreen(char *s){
        int t=0;

        curs_set(0);

        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLUE);
        paint(32,1);

        mvprintw(MAXY/6,(MAXX-strlen(s))/2,"%s",s);

        for(int i=0;i<strlen(drives);i++){
                mvprintw(20+(i+1),40,"DRIVE %c:",drives[i]);
        }
        mvprintw(21,50,"%s",drva);
        mvprintw(22,50,"%s",drvc);
        mvprintw(23,50,"%s",drvd);
        mvprintw(24,50,"%s",drve);
        mvprintw(25,50,"%s",drvz);

        attron(COLOR_PAIR(1));
        for(int i=0;i<getmaxy(stdscr);i++){
                for(int j=0;j<getmaxx(stdscr);j++){
                        t=mvinch(i,j);
                        mvaddch(i,j,(const chtype)t);
                }
        }
        attroff(COLOR_PAIR(1));

        getch();
//        endwin();

}

void drvchck(void){

        register int state=0;

        char er[100];
        char err[500];
        char drvnames[6]="ACDEZ";
        char *drvs[5];

        drvs[0]=drva;
        drvs[1]=drvc;
        drvs[2]=drvd;
        drvs[3]=drve;
        drvs[4]=drvz;

        for(int i=0;i<5;i++){
                switch(chdir(drvs[i])){
                        case -1:
                                sprintf(er,"DRIVE %c IS DOWN, YOU CAN TRY TO CONTINUE, BUT FILES ON THE DRIVE WILL NOT BE SAVED!!\n",drvnames[i]);
                                sprintf(err,"%s",er);
                                state=1;
                                break;
                        default:
                                break;
                }
        }
        if(state==1)
                bluescreen(err);
}

