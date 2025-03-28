#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	pid_t pid;
	if ((pid = fork()) < 0)		// fork로 자식 프로세스 생성
		exit(0);
	else if (pid != 0)			// 부모 프로세스 종료
		exit(0);
	signal(SIGHUP, SIG_IGN);	// 터미널 연결 단절시 신호 무시
	setsid();					// 세션 생성, fork로 생성된 자식 프로세스를 현재 세션과 무관하게 동작
	while (1)					// 데몬 프로그램이 실행할 코드
	{
		system("./chk");
		sleep(1);
	}
}