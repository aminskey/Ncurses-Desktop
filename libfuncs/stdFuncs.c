#include<strings.h>
#include<string.h>
#include<stdio.h>

char *nreverse(char *str, int num1, int num2){
        int c;
        for(int i=num1, j=num2;i<j;i++, j--){
                c=str[i];
                str[i]=str[j];
                str[j]=c;
        }
        return str;
}
char *replace(char *string, char c1, char c2){

        char str[200];

        strcat(str, string);

        for(int i=0;i<strlen(str)-1;i++){
                if(str[i]==c1)
                        str[i]=c2;
        }
        sprintf(string,"%s",str);

        return string;
}


