#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/signal.h>

void *reset_buf(void *buf)
{
	int idx;

	idx = 0;
	while (idx < 100)
		((unsigned char *)buf)[idx++] = 0;
	return (buf);
}
#include <time.h>

void handler(int signum, siginfo_t *info, void *context)
{
	static unsigned char buf[200];
	static int			 str_idx;
	static int			 bit_idx;
	static clock_t		start;
	static clock_t		end;
	static int			start_flag;

	if (!start_flag && str_idx == 0)
	{
		start_flag = 1;
		start = clock();
	}
	if (bit_idx == 8)
	{
		bit_idx = 0;
		str_idx++;
	}
	if (signum == SIGUSR2)
		buf[str_idx] |= (1 << (bit_idx));
	bit_idx++;
	if (buf[str_idx] == 255 || str_idx == 99)
	{
		write(1, buf, str_idx);
		if (buf[str_idx] == 255)
		{
			write(1, "\n", 1);
			end = clock();
			printf("sec : %lf\n", (double)(end-start)/CLOCKS_PER_SEC);
			start_flag = 0;
		}
		reset_buf(buf);	
		str_idx = 0;
	}
}

int main(int argc, char **argv)
{
	struct sigaction act;

	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	printf("server pid : %d\n", getpid());
	if (sigaction(SIGUSR1, &act, NULL))
	{
		printf("sigaction sigusr1 error\n");
		exit(0);
	}
	if (sigaction(SIGUSR2, &act, NULL))
	{
		printf("sigaction sigusr2 error\n");
		exit(0);
	}
	while (1)
		;
	return (0);
}
