#include<ncurses.h>
#include<strings.h>
#include<string.h>
#include<stdio.h>
#include<dirent.h>

extern char drva[];
extern char drvc[];
extern char drvd[];
extern char drve[];
extern char drvz[];

void Mzpause(WINDOW *src){
        wprintw(src,"\tPress Anything To Continue ...");
        wgetch(src);
}
int dir(WINDOW *src, char d[],int ln){

	int i=0;

	DIR *dp;
	struct dirent *dir;

	if((dp=opendir(d)) == NULL){
		return -1;
	}

	while((dir=readdir(dp)) != NULL){
		wprintw(src,"%25s",dir->d_name);
		i++;
		if(i>=2){
			ln++;
			wprintw(src,"\n");
			i=0;
		}

		if(ln >= getmaxy(src) - 2){
			Mzpause(src);
			wclear(src);
			ln=0;
		}
	}
        wprintw(src,"\n");
        closedir(dp);

        return ln;
}
int more(WINDOW *src, char *f, int ln){
        int i=0;
        char buff;

        FILE *fp=fopen(f,"r+");
        if(!strcmp(f,"--help")){
                return -2;
        }if(!strcmp(f,"--version")){
                return -3;
        }if(fp == NULL){
                return -1;
        }


        while(!feof(fp)){
                buff = fgetc(fp);
                i++;

                if(buff == '\n'){
                        ln++;
                }
                if(ln>=getmaxy(src)-1){
                        Mzpause(src);
                        wclear(src);
                        ln=0;
                }
		wprintw(src,"%c",buff);
        }
        wprintw(src,"\n---%s---\n",f);
        fclose(fp);

        return (ln++);

}
void locdrv(WINDOW *src){
	char drives[]={'A','C','D','E','Z'};
	char *drvs[]={0,0,0,0,0};

	drvs[0]=drva;
	drvs[1]=drvc;
	drvs[2]=drvd;
	drvs[3]=drve;
	drvs[4]=drvz;

	for(int i=0;i<45;i++){
		wprintw(src,"%c",(unsigned char)205);
		if(i == 15)
			wprintw(src,"%c",(unsigned char)206);
	}
	wprintw(src,"\nDRIVES");
	for(int i=strlen("\n WHERE"); i<45-strlen("DRIVES");i++){
		wprintw(src," ");
		if(i == 16){
			wprintw(src,"%c",(unsigned char)186);
		}
	}
	wprintw(src," WHERE\n");
        for(int i=0;i<45;i++){
                wprintw(src,"%c",(unsigned char)205);
                if(i == 15)
                        wprintw(src,"%c",(unsigned char)206);
        }
	wprintw(src,"\n");

	for(int i=0;i<5;i++){
		wprintw(src,"DRIVE %c",drives[i]);
		for(int i=strlen("DRIVE #");i<20;i++){
			wprintw(src," ");
			if(i == 15){
				wprintw(src,"%c",(unsigned char)186);
			}
		}
		wprintw(src,"%s\n",drvs[i]);
	}

        for(int i=0;i<45;i++){
                wprintw(src,"%c",(unsigned char)205);
                if(i == 15)
                        wprintw(src,"%c",(unsigned char)206);
        }
	wprintw(src,"\n");


}


