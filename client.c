#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <unistd.h>
#include <signal.h>

void post(int pid, char *str)
{
	int idx;
	int close_idx;
	int c;

	close_idx = 0;
	while (*str)
	{
		c = (int)*str;
		idx = 0;
		while (idx <= 7)
		{
			if (c >> idx & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(500);
			idx++;
		}
		str++;
	}
	while (close_idx++ <= 7)
		kill(pid, SIGUSR2); 
}

int main(int argc, char **argv)
{
	if (argc != 3)
		printf("usage %s error\n", argv[0]);
	else
	{
		printf("server pid : %d\n", atoi(argv[1]));
		printf("send string : %s\n", argv[2]);
		int len = 0;
		while (argv[2][len])
			len++;
		printf("len : %d\n",  len);
		post(atoi(argv[1]), argv[2]);
	}
	return (0);
}
