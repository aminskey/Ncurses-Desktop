#include<ncurses.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

#include "acorn.h"
#include "cmd_acornDOS.h"

short fs, ss;
int col, ch;

extern int main();

char quote[100];

char window[6][200]= { /*	DECIDED NOT TO CHANGE THE REST		*/
	{"size of window :"},
	{"window coordinates : "},
	{"window type : "},
	{"size of subwindow : "},
	{"subwindow coordinates : "},
	{"times cleared : "},
};

static char cdrv='C';

int term(WINDOW *wterm, char *username){

	int winy;
	int winx;

        char cmd[30];
        char arg1[100];
        char arg2[100];
        char arg3[100];
        char arg4[100];
        char str[400];

        int ln=0;

	int st=0;
	int in=0;
	int wy, wx;


	char srch[200];
        char cwd[100];
	char start[100];
	char rs[100];

        int drvstate=0;

	drvchck();
	sprintf(quote,"YOUR SYSTEM IS DOWN");

	WINDOW *iterm=derwin(wterm,getmaxy(wterm)-2,getmaxx(wterm)-2,1,1);


	MEVENT evnt;

	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);


	sprintf(srch,"%s/dat",drva);
	FILE *fp=fopen(srch,"r");
	if(fp == NULL){
		bluescreen("Your System Is DOWN!! CALL THE MANUFACTURER AND TELL HIM THAT SOMETHING\'S MESSED UP");
		exit(0);
	}else{
		fscanf(fp,"%d %d %hd %hd",&ch,&col,&fs,&ss);
	}

        start_color();
        init_pair(1,COLOR_WHITE,COLOR_CYAN);
	init_pair(col,fs,ss);
	init_pair(2,COLOR_BLACK,COLOR_GREEN);
	init_pair(4,ss, fs);

	wclear(wterm);
	wclear(iterm);

	wpaint(wterm, 32, 4);
	wpaint(iterm, 32, 4);


	wattron(wterm, COLOR_PAIR(4));

        box(wterm,0,0);
        mvwprintw(wterm,0,(getmaxx(wterm)-strlen("Acorn Terminal"))/2,"Acorn Terminal");

	wattroff(wterm, COLOR_PAIR(4));
        wrefresh(wterm);


        echo();
        curs_set(1);

	drvchck();

	sprintf(start,"%s/%s",drvc,username);

	switch(cdrv){
		case 'A':
			drvstate=1;
			chdir(drva);
			break;
		case 'C':
			drvstate=0;
			chdir(start);
			break;
		case 'D':
			drvstate=3;
			chdir(drvd);
			break;
		case 'E':
			drvstate=4;
			chdir(drve);
			break;
		case 'Z':
			drvstate=5;
			chdir(drvz);
			break;
		default:
			drvstate=0;
			break;
	}


	sprintf(cmd, " ");
	char print[212];


        while(1){

		wattron(iterm, COLOR_PAIR(4));
		wattron(wterm, COLOR_PAIR(4));

		getbegyx(wterm,wy,wx);
		getcwd(cwd,180);

		drvchck();
		chdir(cwd);

		replace(cwd,'/','\\');
		reverse(cwd);

		sprintf(rs," ");

		for(int i=0;cwd[i]!=cdrv;i++){
			rs[i]=cwd[i];
		}
		reverse(rs);
		reverse(cwd);

		sprintf(print,"%c:\\%s>",cdrv, rs+4);

                mvwprintw(iterm,ln,0,"%s",print);
                mvwscanw(iterm,ln,3+strlen(print),"%s %s %s %s %s",cmd,arg1,arg2,arg3,arg4);
                ln++;

                if(!strcmp(cmd,"A:")||!strcmp(cmd,"a:")){
                        drvstate=1;
                }if(!strcmp(cmd,"C:")||!strcmp(cmd,"c:")){
                        drvstate=2;
                }if(!strcmp(cmd,"D:")||!strcmp(cmd,"d:")){
                        drvstate=3;
                }if(!strcmp(cmd,"E:")||!strcmp(cmd,"e:")){
                        drvstate=4;
                }if(!strcmp(cmd,"Z:")||!strcmp(cmd,"z:")){
                        drvstate=5;
                }


                switch(drvstate){
                        case 1:
                                cdrv='A';
				chdir(drva);
                                drvstate=0;
                                break;
                        case 2:
                                cdrv='C';
				chdir(drvc);
                                drvstate=0;
                                break;
                        case 3:
                                cdrv='D';
				chdir(drvd);
                                drvstate=0;
                                break;
                        case 4:
                                cdrv='E';
				chdir(drve);
                                drvstate=0;
                                break;
                        case 5:
                                cdrv='Z';
				chdir(drvz);
                                drvstate=0;
                                break;
                        default:
				drvstate=0;
				chdir(cwd);
                                break;
                }



                if(!strcmp(cmd,"exit") || !strcmp(cmd,"EXIT")){
                        if(!strcmp(arg1,"_")){
				st=0;
				break;
                        }

                        if(!strcmp(arg1,"desk") || !strcmp(arg1,"DESK")){
                                endwin();
                                return SYS_SHUTDOWN;
                        }
		}if(!strcmp(cmd,"edit")||!strcmp(cmd,"EDIT")){
			st=SYS_OK;
			edit();
			break;
		}if(!strcmp(cmd,"touch")||!strcmp(cmd,"TOUCH")){
			if(creat(arg1,S_IRWXO|S_IRWXG|S_IRWXU)==-1)
				wprintw(iterm,"Cannot Create File:-1\n");
			ln+=2;
		}
		if(!strcmp(cmd,"move")||!strcmp(cmd,"MOVE")){
			keypad(stdscr,TRUE);
			int c=getch();
			while(1){
				if(c==KEY_MOUSE){
					if(getmouse(&evnt)==OK){
						if(evnt.bstate >= BUTTON1_PRESSED){
							winy=evnt.y;
							winx=evnt.x;
						}
					}else{
						bluescreen("Your Mouse is not functioning, to use the desktop please fix the mouse!!");
						exit(0);
					}
				}
				break;
			}
                        if(!(winy>=(getmaxy(stdscr)-getmaxy(wterm))||winx>=(getmaxx(stdscr)-getmaxx(wterm)))){

				wclear(wterm);
				wpaint(wterm, 32, col);
				wrefresh(wterm);

				mvwin(wterm,winy,winx);
				return term(wterm,username);
			}
			else{
				ln+=3;
				wprintw(iterm,"You Cannot Place A Window Outside The Screen!!\n");
				ln++;
			}
			ln++;
		}if(!strcmp(cmd,"window")||!strcmp(cmd,"WINDOW")){
			if(!strcmp(arg1,"outer")||!strcmp(arg1,"OUTER")){
				int yside=getmaxy(wterm),xside=getmaxx(wterm);
				int data[2][2]={
					{yside,xside},
					{wy,wx}
				};
				for(int i=0;i<2;i++){
					wprintw(iterm,"%s%d,%d\n",window[i],data[i][i],data[i][i+(i-2)]);
				}
				wprintw(iterm,"%smain window\n",window[3]);

				ln+=6;
			}
			if(!strcmp(arg1,"inner")||!strcmp(arg1,"INNER")){
				int yside=getmaxy(iterm),xside=getmaxx(iterm);
				int y,x;
				getbegyx(iterm,y,x);
				wprintw(iterm,"size of window: %dx%d characters squared (ch2)\nsubwindow placed (%d,%d)\n times cleared: %d\nstatus: subwindow\n",xside,yside,x,y,in);
				ln+=5;
			}if(!strcmp(arg1,"all")||!strcmp(arg1,"ALL")){
				int yside=getmaxy(wterm),xside=getmaxx(wterm);
				int inyside=getmaxy(iterm),inxside=getmaxx(iterm);
				int y,x,iy,ix;
				getbegyx(wterm,y,x);
				getbegyx(iterm,iy,ix);
				wprintw(iterm,"size of window: %dx%d characters squared (ch2)\nsize of subwindow: %dx%d characters squared (ch2)\nwindow placed (%d,%d)\nsubwindow placed (%d,%d)\ntimes subwindow cleared: %d\nstatus: reporting both\n",xside,yside,inxside,inyside,x,y,ix,iy,in);
				ln+=11;
			}
		}if(!strcmp(cmd,"pwd")||!strcmp(cmd,"PWD")){
                        wprintw(iterm,"%s\n",cwd);
                }if(!strcmp(cmd,"cls")||!strcmp(cmd,"CLS")){
			wclear(iterm);
			wpaint(iterm, 32, 4);
			ln=0;
			in++;
		}if(!strcmp(cmd,"dir")||!strcmp(cmd,"DIR")){
			int dr=dir(iterm, arg1,ln);
			if(dr<=-1){
				wprintw(iterm,"Oopsy Something went wrong!!\n");
			}
                        else{
                                ln=dr;
                        }
			ln++;
                }if(!strcmp(cmd,"more")||!strcmp(cmd,"MORE")){
                        int f=more(iterm, arg1, ln);
			if(f == -1)
                        {
                                wprintw(iterm,"[more] : Cannot Open Requested File -\'%s\' - \"--help\" for help\n",arg1);
                        }if(f==-2){
                                wprintw(iterm,"[Usage] : more [filename] --help --version\n");
                        }if(f==-3){
                                wprintw(iterm,"[Version]: 1\n");
                        }else{
                                ln+=f;
                        }
			ln++;
                }if(!strcmp(cmd,"help")||!strcmp(cmd,"HELP")){
                        wprintw(iterm,"Help v 1.1\n\n");
                        ln+=2;
                        if(!strcmp(arg1,"_")){
                                sprintf(str,"%s/commands.txt",drvz);
                                int f=more(iterm,str,ln);
                                if(f == -1){
                                        wprintw(iterm,"[more] : Cannot Open Requested File \'%s\' - \"--help\" for help\nif you do help _ , then it will display help page\n",str);
                                }else{
                                        ln=f;
                                }
                        }
                        sprintf(str,"%s/%s.txt",drvz,arg1);
                        int f=more(iterm,str,ln);
                        if(f == -1){
                                wprintw(iterm,"[more] : Cannot Open Requested File \'%s\' - \"--help\" for help\nif you do help _ , then it will display help page\n",str);
                        }else{
                                ln=f;
                        }
                        sprintf(str," ");
			ln += 2;
                }if(!strcmp(cmd,"reset")||!strcmp(cmd,"RESET")){
                        st=term(wterm,username);
			return st;
                }if(!strcmp(cmd,"reboot")||!strcmp(cmd,"REBOOT")){
			endwin();
			return SYS_RESTART;
		}if(!strcmp(cmd,"console")||!strcmp(cmd,"CONSOLE")){
                        sprintf(str,"%s %s %s",arg1,arg2,arg3);
                        system(str);
			ln += 2;
                }if(!strcmp(cmd,"winout")||!strcmp(cmd,"WINOUT")){
			mvwprintw(wterm,0,0,"*");
			wrefresh(wterm);
			st=1;
			break;
		}if(!strcmp(cmd,"wheredrv")||!strcmp(cmd,"WHEREDRV")){
			locdrv(iterm);
			ln += 10;
		}if(!strcmp(cmd,"del")||!strcmp(cmd,"DEL")){
			int rm=remove(arg1);
			if(rm == -1){
				wprintw(iterm,"Cannot delete %s: %d",arg1,rm);
			}
			wprintw(iterm,"\n");
			ln+=2;
		}if(!strcmp(cmd,"cd")||!strcmp(cmd,"CD")||!strcmp(cmd,"chdir")||!strcmp(cmd,"CHDIR")){
			int cd=chdir(arg1);
			if(cd == -1){
				wprintw(iterm,"Cannot Access Directory: %d\n",cd);
				ln+=2;
			}else{
				ln++;
			}
		}
		if(!strcmp(cmd,"mkdir")||!strcmp(cmd,"MKDIR")){
			int stat=mkdir(arg1,0777);
			if(stat == -1){
				wprintw(iterm,"Ooops Cannot Create Directory: %d",stat);
			}
			wprintw(iterm,"\n");
			ln += 2;
		}
                if(ln >= getmaxy(iterm)-1){
                        ln=0;
                        wclear(iterm);
                }
	        sprintf(quote,"YOUR SYSTEM IS DOWN");

                sprintf(cmd," ");

		for(int i=0;i<getmaxy(wterm);i++){
			for(int j=0;j<getmaxx(wterm);j++){
				int t = mvwinch(wterm, i, j);
				mvwaddch(wterm, i, j, t);
			}
		}

		wattroff(iterm, COLOR_PAIR(4));
		wattroff(wterm, COLOR_PAIR(4));
                wrefresh(iterm);
        }

        noecho();
        curs_set(0);

	return st;

}
