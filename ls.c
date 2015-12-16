//узнать свойства файла
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <limits.h>
#include <stdlib.h>


int main(int argc, const char** argv)//(argc-кол-во аргументов, argv - имя файла)
{
	DIR* dir;//создания данной типа DIR* (поток данных о месторасположении)
	struct dirent* curr_file_info;//в структуру будет складываться инфа о текущем файле из потока
	struct stat sb;//сюда будем складывать готовую статистику
	char* full_path = NULL;//создаем переменную (строковая и пустая) для пути к файлу
	struct passwd  *pw_d;
	if(argc < 2)//аргументов недостаточно, файл не найден
	{
		printf("No arguments supplied\n");
		return -1;
	}
	dir = opendir(argv[1]);//открываем файл (поток данных о первом элементе argv), при ошибке он присваивает NULL
	if(dir == NULL)
	{
		printf("Error - %d\n", errno);
		return -1;
	}
	full_path = realpath(argv[1], NULL);//команда получает местонахождение файла(argv)
	while( ( curr_file_info = readdir(dir) ) != NULL )//читаем все из dira, пока не наступит конец
	{
		printf("--------------------------------------------\n");
		printf("File path:  %s/%s\n", full_path, curr_file_info->d_name);//пишем путь к файлу+имя, взятое из currfileinfo
		full_path = realpath(argv[1], NULL);//присваиваем истинный путь
                char* tempp = full_path;
                tempp = strcat(tempp, "/");
                tempp = strcat(tempp, curr_file_info->d_name);//после полного путя нужно еще вписать имя(после слэша) в tempp, т.о. получим полный путь
		if (stat(tempp, &sb) == -1) //снимаем статистику о файле (13 параметров)  и кладем в sb (при ошибке и в винде возвратит -1)
		{
        	printf("Statistics couldn't be taken.");
        	return -1;
    	        }	
    	printf("File size:                %lld bytes\n", (long long) sb.st_size);//далее выводим всю статистику...
    	pw_d = getpwuid ( sb.st_uid ); 
  		printf ( "File owner:               %s \n", pw_d->pw_name); 
    	printf("Mode:                     %lo (octal)\n", (unsigned long) sb.st_mode);
    	printf("Last file access:         %s", ctime(&sb.st_atime));//время последнего доступа
      printf("Last file modification:   %s", ctime(&sb.st_mtime));//время последней модификации
      printf("File create time:         %s", ctime(&sb.st_ctime));//время создания файла
	}
	free(full_path);//освобождаем переменную	
	closedir(dir);//закрываем поток и
	printf("%s %s\n", argv[0], argv[1]);
	return 0;
}
