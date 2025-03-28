#include <string.h>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

void manage();
void worker();
int main()
{
    system("./dm");
    while (1) {
        system("clear");
        char password[11] = {};
        int select;
        printf(" ______________________________________________\n");
        printf("              ____       __        __\n");
        printf("             /    )    /    )    /    )\n");
        printf(" -----------/____/----/----/-----\\-------------\n");
        printf("           /         /    /       \\\n");
        printf(" _________/_________(____/____(____/___________\n");
        printf("                             제작: 노다빈/유혁진\n\n");
        printf(" ┌─────────────────────────────────────────────┐\n");
        printf(" │                  메인 화면                  │\n");
        printf(" │─────────────────────────────────────────────│\n");
        printf(" │ ┌──────────────────┐   ┌──────────────────┐ │\n");
        printf(" │ │  1. 관리자 모드  │   │  2. 근무자 모드  │ │\n");
        printf(" │ └──────────────────┘   └──────────────────┘ │\n");
        printf(" │                                             │\n");
        printf(" │ ┌─────────────────────────────────────────┐ │\n");
        printf(" │ │            0. 프로그램 종료             │ │\n");
        printf(" │ └─────────────────────────────────────────┘ │\n");
        printf(" └─────────────────────────────────────────────┘\n\n");
        printf(" 입력 : ");
        scanf("%d", &select);
        int n = 0;
        if (select == 0) {
            printf(" 프로그램을 종료합니다");
            system("ps ax | grep ./dm | awk '{print $1}' | xargs kill");    // dm 종료
            printf("\n");
            sleep(1);
            system("clear");
            exit(1);
        }
        if (select == 1){
            printf(" 비밀번호 : ");
            scanf("%s", password);
            if (strcmp(password, "1234") == 0) {
                manage();
                continue;
            }
            else {
                printf(" 비밀번호를 잘못 입력했습니다.\n");
                sleep(1);
                continue;
            }
        }
        if (select == 2){
            worker();
            continue;
        }
    }
}

void worker()
{
    while (1)
    {
        system("clear");
        printf(" ______________________________________________\n");
        printf("              ____       __        __\n");
        printf("             /    )    /    )    /    )\n");
        printf(" -----------/____/----/----/-----\\-------------\n");
        printf("           /         /    /       \\\n");
        printf(" _________/_________(____/____(____/___________\n\n\n");
        printf(" ┌─────────────────────────────────────────────┐\n");
        printf(" │                 근무자 모드                 │\n");
        printf(" ├─────────────────────────────────────────────┤\n");
        printf(" │ ┌──────────────────┐   ┌──────────────────┐ │\n");
        printf(" │ │   1. 판매        │   │  2. 상품 리스트  │ │\n");
        printf(" │ └──────────────────┘   └──────────────────┘ │\n");
        printf(" │                                             │\n");
        printf(" │ ┌─────────────────────────────────────────┐ │\n");
        printf(" │ │              0. 메인 화면               │ │\n");
        printf(" │ └─────────────────────────────────────────┘ │\n");
        printf(" └─────────────────────────────────────────────┘\n\n");
        int select;
        printf(" 입력: ");
        scanf("%d", &select);
        getchar();

        if (select == 1)    // 판매
        {
            system("clear");
            int fd1, fd2, i, j, n;
            int product_num, product_count;
            char buf[8192];
            time_t t;
            struct tm *pt;
            time(&t);
            pt = localtime(&t);

            while((fd1 = open("currentList", O_RDONLY | O_CREAT, 0644)) < 0){
                if(errno != EEXIST){
                    perror("open");
                    exit(1);
                }
            }
            if((n = read(fd1,buf,8192)) < 0){
                printf("read error");
                exit(1);
            }

            int count = 0; 
            char* ptr = strstr(buf, "\n");
            while (ptr != NULL)
            {
                ptr = strstr(ptr + 1, "\n");
                count++;
            }

            char *cbuf[count][10];
            char *temp = strtok(buf, "/");;
            
            printf("──────────────────────────────── 상품리스트 ────────────────────────────────\n");
            printf("현재 시각 : %d년 %d월 %d일 | %d시 %d분 %d초\n", pt->tm_year + 1900, pt->tm_mon + 1, pt->tm_mday, pt->tm_hour, pt->tm_min, pt->tm_sec);
            printf("순서 / 상품명 / 가격 / 개수\n\n");
            printf("────────────────────────────────────────────────────────────────────────────\n");
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
                printf("%d. %s / %s원 / %s개\n", i+1, cbuf[i][1], cbuf[i][2], cbuf[i][9]);
            }
            printf("────────────────────────────────────────────────────────────────────────────\n");
            close(fd1);
            printf("판매할 상품의 순서를 입력하시오 : ");
            scanf("%d", &product_num);
            if(product_num < 1 || product_num > count){
                printf("해당 상품의 순서는 없습니다.\n");
                sleep(1);
                continue;
            }
            printf("개수를 입력하시오 : ");
            scanf("%d", &product_count);
            // 개수가 적을 때
            if(atoi(cbuf[product_num - 1][9]) > product_count){
                sprintf(cbuf[product_num - 1][9], "%d", atoi(cbuf[product_num - 1][9]) - product_count);
                printf("판매 완료.\n");
            }
            // 개수가 같을 때
            else if(atoi(cbuf[product_num - 1][9]) == product_count){
                cbuf[product_num - 1][9] = "0";
                printf("판매 완료.\n");
            }
            // 개수가 많을 때
            else if(atoi(cbuf[product_num - 1][9]) < product_count){
                printf("원하는 개수가 현재 상품 개수보다 적습니다. 이전화면으로 돌아갑니다.\n");
                sleep(2);
                continue;
            }

            while((fd1 = open("currentList", O_WRONLY | O_TRUNC)) < 0){
                if(errno != EEXIST){
                    perror("open");
                    exit(1);
                }
            }
            for(i = 0; i < count; i++){
                if(strcmp(cbuf[i][9], "0") == 0){
                    continue;
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
                
            }
            close(fd1);

            char *product_count_char[100];
            sprintf(product_count_char, "%d", product_count);

            while((fd2 = open("soldList", O_WRONLY | O_APPEND | O_CREAT, 0644)) < 0){
                if(errno != EEXIST){
                    perror("open");
                    exit(1);
                }
            }
            sprintf(cbuf[product_num - 1][3], "%d", pt->tm_year + 1900);
            sprintf(cbuf[product_num - 1][4], "%d", pt->tm_mon + 1);
            sprintf(cbuf[product_num - 1][5], "%d", pt->tm_mday);
            sprintf(cbuf[product_num - 1][6], "%d", pt->tm_hour);
            sprintf(cbuf[product_num - 1][7], "%d", pt->tm_min);
            sprintf(cbuf[product_num - 1][8], "%d", pt->tm_sec);
            for(i = 0; i < 10; i++){
                if(i == 9){
                    write(fd2, product_count_char, strlen(product_count_char));
                    write(fd2, "\n", 1);
                }
                else{
                    write(fd2, cbuf[product_num - 1][i], strlen(cbuf[product_num - 1][i]));
                    write(fd2, "/", 1);
                }
            }
            close(fd2);
            sleep(1);
        }

        if (select == 2)    // 상품 리스트
        {
            system("clear");
            int fd, i, j, n;
            char buf[8192];
            time_t t;
            struct tm *pt;
            time(&t);
            pt = localtime(&t);

            while((fd = open("currentList", O_RDONLY | O_CREAT, 0644)) < 0){
                if(errno != EEXIST){
                    perror("open");
                    exit(1);
                }
            }
            if((n = read(fd,buf,8192)) < 0){
                printf("read error");
                exit(1);
            }

            int count = 0; 
            char* ptr = strstr(buf, "\n");
            while (ptr != NULL)
            {
                ptr = strstr(ptr + 1, "\n");
                count++;
            }

            char *cbuf[count][10];
            char *temp = strtok(buf, "/");;
            
            printf("──────────────────────────────── 상품리스트 ────────────────────────────────\n");
            printf("현재 시각 : %d년 %d월 %d일 | %d시 %d분 %d초\n", pt->tm_year + 1900, pt->tm_mon + 1, pt->tm_mday, pt->tm_hour, pt->tm_min, pt->tm_sec);
            printf("순서 / 코드 / 상품명 / 가격 / 유통기한 / 개수\n\n");
            printf("────────────────────────────────────────────────────────────────────────────\n");
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
                
                printf("%d. %s / %s / %s원 / %s년 %s월 %s일 | %s시 %s분 %s초 까지 / %s개\n", i+1, cbuf[i][0], cbuf[i][1], cbuf[i][2], cbuf[i][3], cbuf[i][4], cbuf[i][5], cbuf[i][6], cbuf[i][7], cbuf[i][8], cbuf[i][9]);
            }
            printf("────────────────────────────────────────────────────────────────────────────\n");
            close(fd);
            getchar();
        }
        if (select == 0)
        {
            return;
        }
    }
}

void manage()
{
    while (1)
    {
        system("clear");
        printf(" ______________________________________________\n");
        printf("              ____       __        __\n");
        printf("             /    )    /    )    /    )\n");
        printf(" -----------/____/----/----/-----\\-------------\n");
        printf("           /         /    /       \\\n");
        printf(" _________/_________(____/____(____/___________\n\n\n");
        printf(" ┌─────────────────────────────────────────────┐\n");
        printf(" │                 관리자 모드                 │\n");
        printf(" ├─────────────────────────────────────────────┤\n");
        printf(" │ ┌──────────────────┐   ┌──────────────────┐ │\n");
        printf(" │ │   1. 발주        │   │  2. 상품 리스트  │ │\n");
        printf(" │ └──────────────────┘   └──────────────────┘ │\n");
        printf(" │ ┌──────────────────┐   ┌──────────────────┐ │\n");
        printf(" │ │   3. 폐기 상품   │   │  4. 매출 확인    │ │\n");
        printf(" │ └──────────────────┘   └──────────────────┘ │\n");
        printf(" │ ┌──────────────────┐   ┌──────────────────┐ │\n");
        printf(" │ │   5. 폐기 제거   │   │  6. 매출 초기화  │ │\n");
        printf(" │ └──────────────────┘   └──────────────────┘ │\n");
        printf(" │ ┌─────────────────────────────────────────┐ │\n");
        printf(" │ │              0. 메인 화면               │ │\n");
        printf(" │ └─────────────────────────────────────────┘ │\n");
        printf(" └─────────────────────────────────────────────┘\n\n");
        int select;
        printf(" 입력: ");
        scanf("%d", &select);
        getchar();

        if (select == 1)    // 발주
        {
            system("clear");
            int fd1, fd2, n, i, j;
            char product_code[256], product_count[256];
            char buf[8192];
            char buf1[8192];
            time_t t;
            struct tm *pt;
            time(&t);
            pt = localtime(&t);

            int year = pt->tm_year + 1900;
            int month = pt->tm_mon + 1;
            int day = pt->tm_mday;
            int hour = pt->tm_hour;
            int minute = pt->tm_min;
            int sec = pt->tm_sec;

            // product_list 불러오기
            while((fd1 = open("productList", O_RDONLY)) < 0){
                if(errno != EEXIST){
                    perror("open");
                    exit(1);
                }
            }
            if((n = read(fd1,buf,8192)) < 0){
                printf("read error");
                exit(1);
            }
            close(fd1);

            // buf안에 있는 / 개수 세기
            int count = -1;
            char* ptr = strstr(buf, "\n");
            while (ptr != NULL)
            {
                ptr = strstr(ptr + 1, "\n");
                count++;
            }

            // 상품코드 확인을 위한 분리
            char *product_code_list[count];

            // 리스트 출력하기
            strcpy(buf1, buf);
            char *cbuf[count][7];
            char *temp = strtok(buf1,"\n");
            printf("──────────────────────────────── 발주리스트 ────────────────────────────────\n");
            printf("현재 시각 : %d년 %d월 %d일 %d시 %d분 %d초\n", year, month, day, hour, minute, sec);
            printf("코드 / 상품명 / 가격 / 유통기한\n\n");
            for(i = 0; i < count; i++){
                for(j = 0; j < 7; j++){
                    if(j < 3){
                        temp = strtok(NULL, "/");
                        cbuf[i][j] = temp;
                    }
                    else if(j < 6){
                        temp = strtok(NULL, "-");
                        cbuf[i][j] = temp;
                    }
                    else{
                        temp = strtok(NULL, "\n");
                        cbuf[i][j] = temp;
                    }
                }
                product_code_list[i] = cbuf[i][0];
                printf("%s / %s / %s원 / %s일 %s시 %s분 %s초 후\n", cbuf[i][0], cbuf[i][1], cbuf[i][2], cbuf[i][3], cbuf[i][4], cbuf[i][5], cbuf[i][6]);
            }

            // 상품 코드 확인
            bool check_code = true;
            while(check_code){
                printf("────────────────────────────────────────────────────────────────────────────\n");
                printf("발주할 상품 코드를 입력하시오 : ");
                scanf("%s", product_code);
                for(i = 0; i < count; i++){
                    if(strcmp(product_code, product_code_list[i]) == 0){
                        check_code = false;
                        break;
                    }
                }
                if(check_code){
                    printf("해당 하는 상품 코드가 없습니다. 다시 입력해주십시오\n");
                }
            }
            printf("발주할 상품의 개수를 입력하시오 : ");
            scanf("%s", product_count);

            // current_list 만들기
            while((fd2 = open("currentList", O_WRONLY | O_APPEND | O_CREAT , 0644)) < 0){
                if(errno != EEXIST){
                    perror("open");
                    exit(1);
                }
            }
            char *p1 = strstr(buf, product_code);
            temp = strtok(p1, "/");
            write(fd2, temp, strlen(temp));

            temp = strtok(NULL, "/");
            write(fd2, "/", 1);
            write(fd2, temp, strlen(temp));

            temp = strtok(NULL, "/");
            write(fd2, "/", 1);
            write(fd2, temp, strlen(temp));

            temp = strtok(NULL, "-");
            day += atoi(temp);
            temp = strtok(NULL, "-");
            hour += atoi(temp);
            temp = strtok(NULL, "-");
            minute += atoi(temp);
            temp = strtok(NULL, "/");
            sec += atoi(temp);
            
            char cyear[100];
            char cmonth[5];
            char cday[5];
            char chour[5];
            char cmin[5];
            char csec[5];
            if(sec >= 60){
                sec -= 60;
                minute += 1;
            }
            if(minute >= 60){
                minute -= 60;
                hour += 1;
            }
            if(hour >= 24){
                hour -= 24;
                day += 1;
            }
            if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
                if(day > 31){
                    day -= 31;
                    month += 1;
                }
            }
            else if(month == 2){
                if(day > 28){
                    day -= 28;
                    month += 1;
                }
            }   
            else{
                if(day > 30){
                    day -= 30;
                    month += 1;
                }
            }
            if(month > 12){
                month -= 12;
                year += 1;
            }
            sprintf(cyear, "%d", year);
            strcat(cyear, "/");

            sprintf(cmonth, "%d", month);
            strcat(cyear, cmonth);
            strcat(cyear, "/");

            sprintf(cday, "%d", day);
            strcat(cyear, cday);
            strcat(cyear, "/");

            sprintf(chour, "%d", hour);
            strcat(cyear, chour);
            strcat(cyear, "/");

            sprintf(cmin, "%d", minute);
            strcat(cyear, cmin);
            strcat(cyear, "/");

            sprintf(csec, "%d", sec);
            strcat(cyear, csec);
            write(fd2, "/", 1);
            write(fd2, cyear, strlen(cyear));

            temp = strtok(NULL, "/");
            write(fd2, "/", 1);
            write(fd2, product_count, strlen(product_count));
            write(fd2, "\n", 1);
            close(fd2);

            printf("발주가 완료되었습니다.\n");
            sleep(1);
        }

        if (select == 2)    // 상품 리스트
        {
            system("clear");
            int fd, i, j, n;
            char buf[8192];
            time_t t;
            struct tm *pt;
            time(&t);
            pt = localtime(&t);

            while((fd = open("currentList", O_RDONLY | O_CREAT, 0644)) < 0){
                if(errno != EEXIST){
                    perror("open");
                    exit(1);
                }
            }
            if((n = read(fd,buf,8192)) < 0){
                printf("read error");
                exit(1);
            }

            int count = 0; 
            char* ptr = strstr(buf, "\n");
            while (ptr != NULL)
            {
                ptr = strstr(ptr + 1, "\n");
                count++;
            }

            char *cbuf[count][10];
            char *temp = strtok(buf, "/");;
            
            printf("──────────────────────────────── 상품리스트 ────────────────────────────────\n");
            printf("현재 시각 : %d년 %d월 %d일 | %d시 %d분 %d초\n", pt->tm_year + 1900, pt->tm_mon + 1, pt->tm_mday, pt->tm_hour, pt->tm_min, pt->tm_sec);
            printf("순서 / 코드 / 상품명 / 가격 / 유통기한 / 개수\n\n");
            printf("────────────────────────────────────────────────────────────────────────────\n");
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
                
                printf("%d. %s / %s / %s원 / %s년 %s월 %s일 | %s시 %s분 %s초 까지/ %s개\n", i+1, cbuf[i][0], cbuf[i][1], cbuf[i][2], cbuf[i][3], cbuf[i][4], cbuf[i][5], cbuf[i][6], cbuf[i][7], cbuf[i][8], cbuf[i][9]);
            }
            printf("────────────────────────────────────────────────────────────────────────────\n");
            close(fd);
            getchar();
        }

        if (select == 3)    // 폐기 상품
        {
            system("clear");
            int fd, i, j, n;
            int total = 0;
            char buf[8192];
            time_t t;
            struct tm *pt;
            time(&t);
            pt = localtime(&t);

            while((fd = open("expiredList", O_RDONLY | O_CREAT, 0644)) < 0){
                if(errno != EEXIST){
                    perror("open");
                    exit(1);
                }
            }
            if((n = read(fd,buf,8192)) < 0){
                printf("read error");
                exit(1);
            }

            int count = 0; 
            char* ptr = strstr(buf, "\n");
            while (ptr != NULL)
            {
                ptr = strstr(ptr + 1, "\n");
                count++;
            }

            char *cbuf[count][10];
            char *temp = strtok(buf, "/");;
            
            printf("──────────────────────────────── 폐기리스트 ────────────────────────────────\n");
            printf("현재 시각 : %d년 %d월 %d일 | %d시 %d분 %d초\n", pt->tm_year + 1900, pt->tm_mon + 1, pt->tm_mday, pt->tm_hour, pt->tm_min, pt->tm_sec);
            printf("순서 / 코드 / 상품명 / 가격 / 판매시간 / 개수\n\n");
            printf("────────────────────────────────────────────────────────────────────────────\n");
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
                printf("%d. %s / %s / %s원 / %s년 %s월 %s일 | %s시 %s분 %s초 / %s개\n", i+1, cbuf[i][0], cbuf[i][1], cbuf[i][2], cbuf[i][3], cbuf[i][4], cbuf[i][5], cbuf[i][6], cbuf[i][7], cbuf[i][8], cbuf[i][9]);
            }
            printf("────────────────────────────────────────────────────────────────────────────\n");
            close(fd);
            getchar();
        }

        if (select == 4)    // 매출 확인
        {
            system("clear");
            int fd, i, j, n;
            int total = 0;
            char buf[8192];
            time_t t;
            struct tm *pt;
            time(&t);
            pt = localtime(&t);

            while((fd = open("soldList", O_RDONLY | O_CREAT, 0644)) < 0){
                if(errno != EEXIST){
                    perror("open");
                    exit(1);
                }
            }
            if((n = read(fd,buf,8192)) < 0){
                printf("read error");
                exit(1);
            }

            int count = 0; 
            char* ptr = strstr(buf, "\n");
            while (ptr != NULL)
            {
                ptr = strstr(ptr + 1, "\n");
                count++;
            }

            char *cbuf[count][10];
            char *temp = strtok(buf, "/");;
            
            printf("──────────────────────────────── 판매리스트 ────────────────────────────────\n");
            printf("현재 시각 : %d년 %d월 %d일 | %d시 %d분 %d초\n", pt->tm_year + 1900, pt->tm_mon + 1, pt->tm_mday, pt->tm_hour, pt->tm_min, pt->tm_sec);
            printf("순서 / 코드 / 상품명 / 가격 / 판매시간 / 개수\n\n");
            printf("────────────────────────────────────────────────────────────────────────────\n");
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
                total += atoi(cbuf[i][2]) * atoi(cbuf[i][9]);
                printf("%d. %s / %s / %s원 / %s년 %s월 %s일 | %s시 %s분 %s초 / %s개\n", i+1, cbuf[i][0], cbuf[i][1], cbuf[i][2], cbuf[i][3], cbuf[i][4], cbuf[i][5], cbuf[i][6], cbuf[i][7], cbuf[i][8], cbuf[i][9]);
            }
            printf("────────────────────────────────────────────────────────────────────────────\n");
            printf("총 판매 금액 : %d원\n", total);
            close(fd);
            getchar();
        }
        if (select == 5)    // 폐기 제거
        {
            system("clear");
            system("rm expiredList");
            printf(" 폐기 제거 완료.\n");
            sleep(1);
            continue;
        }
        if (select == 6)    // 매출 초기화
        {
            system("clear");
            system("rm soldList");
            printf(" 매출 초기화 완료.\n");
            sleep(1);
            continue;
        }
        if (select == 0)
        {
            return;
        }
    }
}
