#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>

void wpaint(WINDOW *win, char ch, short clr){
        wattron(win,COLOR_PAIR(clr));

        for(int i=0;i<getmaxy(win);i++)
                for(int j=0;j<getmaxx(win);j++)
                        mvwprintw(win,i,j,"%c",ch);

        wattroff(win, COLOR_PAIR(clr));
}
int chprint(WINDOW *win, char *fname){
        struct stat statbuf;
        char buff;

        int y=0,x=0;

        if(stat(fname,&statbuf)!=-1){
                FILE *fp=fopen(fname,"r+");
                wmove(win,0,0);

                while(!feof(fp)){
                        buff=fgetc(fp);
                        switch(buff){
                                case '\n':
                                        y++;
                                        x=0;
                                        break;
                                case '\t':
                                        x+=8;
                                        break;
                                default:
                                        x++;
                                        break;
                        }
                        mvwprintw(win,y,x,"%c",buff);
                }
                fclose(fp);
        }else{
                return -1;
        }
        return 0;
}
int touch(int y, int x, int y1, int x1, MEVENT evnt){
        return ((evnt.y > y && evnt.y < y1) && (evnt.x > x && evnt. x < x1));
}
// int mtouchwin(WINDOW *win, MEVENT evnt){
//         return touch(getbegy(win),getbegx(win),getmaxy(win),getmaxx(win),evnt);
// }

