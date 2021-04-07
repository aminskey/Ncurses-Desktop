#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <acorn.h>

int edit(MEVENT evnt){

	noecho();
	cbreak();

	int c;
	int x,y;

	x = y = c = 0;

	WINDOW *win = newwin(40, 120, 5, 5);
	WINDOW *edwin = derwin(win, getmaxy(win), getmaxx(win), 1, 1);
	WINDOW *con = derwin(win, getmaxy(win)/4 - 1, getmaxx(win) - 2, (getmaxy(win)/4)*3, 1);

	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_BLUE, COLOR_WHITE);

	wpaint(win, 32, 1);


//	Graphics for main window (*win)
	wattron(win, COLOR_PAIR(1));

	box(win, 0, 0);
	mvwprintw(win, 0, (getmaxx(win) - strlen("Project Editor"))/2, "Project Editor");

	wattroff(win, COLOR_PAIR(1));
	wrefresh(win);

//	Graphics for console (*con)
	wattron(con, COLOR_PAIR(1));

	box(con, 0, 0);
	mvwprintw(con, 0, (getmaxx(con) - strlen("Console"))/2, "Console");

	wattroff(con, COLOR_PAIR(1));
	wrefresh(con);


	keypad(win, true);
	wmove(win, y=1, x=1);

	while(1){
		curs_set(1);

		c = wgetch(win);

		wattron(win, COLOR_PAIR(1));

		if(c == KEY_UP){
			y--;
		}else if(c == KEY_DOWN){
			y++;
		}else if(c == KEY_LEFT){
			x--;
		}else if(c == KEY_RIGHT){
			x++;
		}else if(c == KEY_ENTER){
			y++;
			x=0;
		}else{
			mvwaddch(win, y, x++, c);
		}
		wattroff(win, COLOR_PAIR(1));
		wrefresh(win);

	}

	curs_set(0);
	return 0;
}
