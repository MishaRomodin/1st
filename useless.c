//secondTask from МС Мишаня & company
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

char NextLine = 10;
int MaxStringSize = 100;

int useless(char *str){
    int pause;
    char *argument=malloc(MaxStringSize);
    char *command=malloc(MaxStringSize),*p;
    pid_t pid;	
    if((pid=fork())<0)//проверяем возможность создания процесса ребенок
    {
	   printf("%s\n","Can't create child process.");
	   exit(-1);
    }
    if (pid>0) return 0;
    pause=strtol(str,&p,10);//преобразуем из строки в longint число; указателю последнего элемента присваиваем значение p, все число присваем паузе - время паузы
    sleep(pause);
    strcpy(command,p+1);//копируем в command все с p+1
    int i = strlen(command)-1;//i присваиваем длину строки command-1
    while(command[i] != '/')//пока символ строки не равен слэшу, уменьшаем длину i и читаем предыдущий символ
    {
        i--;
    }
    char mc[20];//создаем массив
    strncpy(mc, command, i)// (тоже самое что strcpy только с защиткой) скопировали в mc весь command начиная с i(т.е. со слэша). т.о. читаем только имя команды, ограниченное слэшэм

    if(execl(command, mc, NULL)<0)//если команду выполнить невозможно, то пишем что она фейлится//mc-то из строки command, что мы должны выполнить
    {
        printf("Error - %d", errno);
        printf("%s%s%s\n","Program ",command," failed to load.");
        exit(0);//выходим
    }
    exit(-1);//выходим
}
int main()
{ 
    int file;
    char c,*str,*cur;
    ssize_t size;
    if((file=open("Input.txt",O_RDONLY))<0)
    {
    	    printf("%s\n","Can't open file!");
            exit(-1);
    }
    str=malloc(MaxStringSize);
    cur=str;
    size=1;
    while (size!=0){
        size=read(file,&c,1);//читает один байт из файла в буфер с
	if((c == NextLine)||(size==0))//если с-символ перевода строки и длина строки больше 0...
	{ 	    
            *cur=0;
            if(strlen(str)>0)
            { 
		      useless(str);
            }
            cur=str;
	}
	    else
	    {
		  *cur=c;
		  cur++;
	    }
	}    
    if(close(file)<0)
    {
        printf("%s\n","Can't close file!");
	    exit(-1);
    }
}
