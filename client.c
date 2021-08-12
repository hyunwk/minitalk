#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <unistd.h>
#include <signal.h>

void send_signal(int pid, int c)
{
	if (c == 0)
		kill(pid, SIGUSR1);
	else if (c == 1)
		kill(pid, SIGUSR2);
	usleep(1000);
}

void to_binary(int pid, int c, int digit)
{
	if (!c)
	{
		while (digit < 8)
		{
			send_signal(pid, 0);
			digit++;
		}
		return ;
	}
	else
	{
		digit++;
		to_binary(pid, c / 2, digit);
		send_signal(pid, c % 2);
	}
}

void post(int pid, char *str)
{
	int idx;
	int close_idx;
	int c;
	int digit;

	idx = 0;
	close_idx = 0;
	while (str[idx])
	{
		digit = 0;
		c = (int)str[idx];
		to_binary(pid, c, digit);
		idx++;
	}
	while (close_idx++ <= 7)
		send_signal(pid, 1); 
}

int main(int argc, char **argv)
{
	if (argc != 3)
		printf("usage %s error\n", argv[0]);
	else
	{
		printf("server pid : %d\n", atoi(argv[1]));
		printf("send string : %s\n", argv[2]);
		post(atoi(argv[1]), argv[2]);
	}
	return (0);
}
