#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#define MAX_SIZE 8192

int main()
{
	int fd, n, i, j, k;
	if ((fd = open("currentList", O_RDWR | O_CREAT, 0644)) < 0)
	{
		exit(0);
	}
	char buf1[MAX_SIZE];

	if ((n = read(fd, buf1, MAX_SIZE)) < 0)
	{
		exit(0);
	}
	time_t t;
	struct tm *pt;
	time(&t);
	pt = localtime(&t);

	int count = 0; 
	char* ptr = strstr(buf1, "\n");
	while (ptr != NULL)
	{
		ptr = strstr(ptr + 1, "\n");
		count++;
	}

	int year[count], month[count], day[count], hour[count], minute[count], sec[count];
	bool check[count];
	char *cbuf[count][10];
	char *temp = strtok(buf1, "/");

	for(i = 0; i < count; i++){
		for(j = 0; j < 10; j++){
			if(j == 8){
				cbuf[i][j] = temp;
				temp = strtok(NULL, "\n");
			}
			else{
				cbuf[i][j] = temp;
				temp = strtok(NULL, "/");
			}
		}
		check[i] = false;
		year[i] = atoi(cbuf[i][3]);
		month[i] = atoi(cbuf[i][4]);
		day[i] = atoi(cbuf[i][5]);
		hour[i] = atoi(cbuf[i][6]);
		minute[i] = atoi(cbuf[i][7]);
		sec[i] = atoi(cbuf[i][8]);
	}
	close(fd);

	for(i = 0; i < count; i++){
		if((pt->tm_year + 1900) < year[i])
			continue;
		else if((pt->tm_year + 1900) > year[i]){
			check[i] = true;
			int fd1, fd2;
			if((fd1 = open("expiredList", O_WRONLY | O_APPEND | O_CREAT, 0644)) < 0){
				exit(0);
			}
			for(j = 0; j < 10; j++){
                if(j == 9){
                    write(fd1, cbuf[i][j], strlen(cbuf[i][j]));
                    write(fd1, "\n", 1);
                }
                else{
                    write(fd1, cbuf[i][j], strlen(cbuf[i][j]));
                    write(fd1, "/", 1);
                }
            }
			close(fd1);

			if((fd2 = open("currentList", O_WRONLY | O_TRUNC)) < 0){
                exit(1);
            }
            for(j = 0; j < count; j++){
                if(check[j]){
                    continue;
                }
                for(k = 0; k < 10; k++){
                    if(k == 9){
                        write(fd2, cbuf[j][k], strlen(cbuf[j][k]));
                        write(fd2, "\n", 1);
                    }
                    else{
                        write(fd2, cbuf[j][k], strlen(cbuf[j][k]));
                        write(fd2, "/", 1);
                    }
                }
            }
			close(fd2);
		}
		if((pt->tm_mon+1) < month[i])
			continue;
		else if((pt->tm_mon+1) > month[i]){
			check[i] = true;
			int fd1, fd2;
			if((fd1 = open("expiredList", O_WRONLY | O_APPEND | O_CREAT, 0644)) < 0){
				exit(0);
			}
			for(j = 0; j < 10; j++){
                if(j == 9){
                    write(fd1, cbuf[i][j], strlen(cbuf[i][j]));
                    write(fd1, "\n", 1);
                }
                else{
                    write(fd1, cbuf[i][j], strlen(cbuf[i][j]));
                    write(fd1, "/", 1);
                }
            }
			close(fd1);

			if((fd2 = open("currentList", O_WRONLY | O_TRUNC)) < 0){
				exit(1);
            }
            for(j = 0; j < count; j++){
                if(check[j]){
                    continue;
                }
                for(k = 0; k < 10; k++){
                    if(k == 9){
                        write(fd2, cbuf[j][k], strlen(cbuf[j][k]));
                        write(fd2, "\n", 1);
                    }
                    else{
                        write(fd2, cbuf[j][k], strlen(cbuf[j][k]));
                        write(fd2, "/", 1);
                    }
                }
            }
			close(fd2);
		}
		if(pt->tm_mday < day[i])
			continue;
		else if(pt->tm_mday > day[i]){
			check[i] = true;
			int fd1, fd2;
			if((fd1 = open("expiredList", O_WRONLY | O_APPEND | O_CREAT, 0644)) < 0){
				exit(0);
			}
			for(j = 0; j < 10; j++){
                if(j == 9){
                    write(fd1, cbuf[i][j], strlen(cbuf[i][j]));
                    write(fd1, "\n", 1);
                }
                else{
                    write(fd1, cbuf[i][j], strlen(cbuf[i][j]));
                    write(fd1, "/", 1);
                }
            }
			close(fd1);

			if((fd2 = open("currentList", O_WRONLY | O_TRUNC)) < 0){
				exit(1);
            }
            for(j = 0; j < count; j++){
                if(check[j]){
                    continue;
                }
                for(k = 0; k < 10; k++){
                    if(k == 9){
                        write(fd2, cbuf[j][k], strlen(cbuf[j][k]));
                        write(fd2, "\n", 1);
                    }
                    else{
                        write(fd2, cbuf[j][k], strlen(cbuf[j][k]));
                        write(fd2, "/", 1);
                    }
                }
            }
			close(fd2);
		}
		if(pt->tm_hour < hour[i]){
			continue;
		}
		else if(pt->tm_hour > hour[i]){
			check[i] = true;
			int fd1, fd2;
			if((fd1 = open("expiredList", O_WRONLY | O_APPEND | O_CREAT, 0644)) < 0){
				exit(0);
			}
			for(j = 0; j < 10; j++){
                if(j == 9){
                    write(fd1, cbuf[i][j], strlen(cbuf[i][j]));
                    write(fd1, "\n", 1);
                }
                else{
                    write(fd1, cbuf[i][j], strlen(cbuf[i][j]));
                    write(fd1, "/", 1);
                }
            }
			close(fd1);

			if((fd2 = open("currentList", O_WRONLY | O_TRUNC)) < 0){
				exit(1);
            }
            for(j = 0; j < count; j++){
                if(check[j]){
                    continue;
                }
                for(k = 0; k < 10; k++){
                    if(k == 9){
                        write(fd2, cbuf[j][k], strlen(cbuf[j][k]));
                        write(fd2, "\n", 1);
                    }
                    else{
                        write(fd2, cbuf[j][k], strlen(cbuf[j][k]));
                        write(fd2, "/", 1);
                    }
                }
            }
			close(fd2);
		}
		if(pt->tm_min < minute[i])
			continue;
		else if(pt->tm_min > minute[i]){
			check[i] = true;
			int fd1, fd2;
			if((fd1 = open("expiredList", O_WRONLY | O_APPEND | O_CREAT, 0644)) < 0){
				exit(0);
			}
			for(j = 0; j < 10; j++){
                if(j == 9){
                    write(fd1, cbuf[i][j], strlen(cbuf[i][j]));
                    write(fd1, "\n", 1);
                }
                else{
                    write(fd1, cbuf[i][j], strlen(cbuf[i][j]));
                    write(fd1, "/", 1);
                }
            }
			close(fd1);

			if((fd2 = open("currentList", O_WRONLY | O_TRUNC)) < 0){
				exit(1);
            }
            for(j = 0; j < count; j++){
                if(check[j]){
                    continue;
                }
                for(k = 0; k < 10; k++){
                    if(k == 9){
                        write(fd2, cbuf[j][k], strlen(cbuf[j][k]));
                        write(fd2, "\n", 1);
                    }
                    else{
                        write(fd2, cbuf[j][k], strlen(cbuf[j][k]));
                        write(fd2, "/", 1);
                    }
                }
            }
			close(fd2);
		}
		if(pt->tm_sec < sec[i])
			continue;
		else{
			check[i] = true;
			int fd1, fd2;
			if((fd1 = open("expiredList", O_WRONLY | O_APPEND | O_CREAT, 0644)) < 0){
				exit(0);
			}
			for(j = 0; j < 10; j++){
                if(j == 9){
                    write(fd1, cbuf[i][j], strlen(cbuf[i][j]));
                    write(fd1, "\n", 1);
                }
                else{
                    write(fd1, cbuf[i][j], strlen(cbuf[i][j]));
                    write(fd1, "/", 1);
                }
            }
			close(fd1);

			if((fd2 = open("currentList", O_WRONLY | O_TRUNC)) < 0){
				exit(1);
            }
            for(j = 0; j < count; j++){
                if(check[j]){
                    continue;
                }
                for(k = 0; k < 10; k++){
                    if(k == 9){
                        write(fd2, cbuf[j][k], strlen(cbuf[j][k]));
                        write(fd2, "\n", 1);
                    }
                    else{
                        write(fd2, cbuf[j][k], strlen(cbuf[j][k]));
                        write(fd2, "/", 1);
                    }
                }
            }
			close(fd2);
		}
	}
}