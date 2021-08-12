#include <unistd.h>
#include <signal.h>

int ft_strlen(char *s)
{
    int len;

	len = 0;
    while (s[len])
        len++;
	return (len);
}

int ft_atoi(char *s)
{
	unsigned int num;
	unsigned int idx;

	num = 0;
	while ('0' <= *s && *s <= '9')
	{
		num = num * 10 + *s - '0';
		s++;
	}
	return (num);
}
void ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_putnbr(int n)
{
	if (n >= 10)
    {
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
    }
	if (n < 10)
		ft_putchar(n + '0');
}

void send_signal(int pid, char *str)
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
    if (argc == 3)
    {
        ft_putstr("server pid :");
		ft_putstr(argv[1]);
        ft_putstr("\nsend string : ");
		ft_putstr(argv[2]);
        ft_putstr("\nlen : ");
		ft_putnbr(ft_strlen(argv[2]));
        send_signal(ft_atoi(argv[1]), argv[2]);
    }
    return (0);
}

