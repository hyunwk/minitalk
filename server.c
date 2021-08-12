#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/signal.h>

void reset_buf(unsigned char *buf)
{
	int idx;

	idx = 0;
	while (idx < 100)
		buf[idx] = 0;
}

void handler(int signo, siginfo_t *info, void *context)
{
	static unsigned char buf[200];
	static int			 str_idx;
	static int			 bit_idx;

	if (bit_idx == 0)
	{
		//printf("%d", buf[str_idx]);
		bit_idx = 8;
		str_idx++;
	}
	//buf[str_idx] &= ~128;
	if (signo == SIGUSR1)
	{
		//buf[str_idx] |= (0 << bit_idx);
		bit_idx--;
	}
	else if (signo == SIGUSR2)
	{
		buf[str_idx] |= (1 << (bit_idx - 1));
		bit_idx--;
	}
	if (buf[str_idx] == 255 || str_idx == 99)
	{
		write(1, buf, str_idx);
		write(1, "\n", 1);
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
