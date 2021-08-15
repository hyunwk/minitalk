# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunwkim <hyunwkim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/13 22:28:48 by hyunwkim          #+#    #+#              #
#    Updated: 2021/08/15 16:57:48 by hyunwkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server 
NAME_C = client 
BONUS_S = server_b
BONUS_C = client_b

CC = gcc
CFLAGS = -Wall -Werror -Wextra

S_FUNC 		= server.c print_util.c
C_FUNC 		= client.c print_util.c
S_FUNC_B 	= server_bonus.c print_util_bonus.c
C_FUNC_B 	= client_bonus.c print_util_bonus.c

SRCS_DIR 	= srcs/
BONUS_DIR 	= bonus/

S_SRCS 		= $(addprefix $(SRCS_DIR), $(S_FUNC))
C_SRCS 		= $(addprefix $(SRCS_DIR), $(C_FUNC))
S_SRCS_B    = $(addprefix $(BONUS_DIR), $(S_FUNC_B))
C_SRCS_B    = $(addprefix $(BONUS_DIR), $(C_FUNC_B))

S_OBJS 		= $(S_SRCS:.c=.o)
C_OBJS 		= $(C_SRCS:.c=.o)
S_OBJS_B 	= $(S_SRCS_B:.c=.o)
C_OBJS_B 	= $(C_SRCS_B:.c=.o)

all : $(NAME) 

$(NAME) : $(S_OBJS) $(C_OBJS)
		$(CC) $(CFLAGS) $(S_SRCS) -o $(NAME)
		$(CC) $(CFLAGS) $(C_SRCS) -o $(NAME_C)

bonus : $(S_OBJS_B) $(C_OBJS_B) 
		$(CC) $(CFLAGS) $(S_OBJS_B) -o $(BONUS_S)
		$(CC) $(CFLAGS) $(C_OBJS_B) -o $(BONUS_C)

clean :
	rm -f $(S_OBJS) $(C_OBJS) $(S_OBJS_B) $(C_OBJS_B)

fclean : clean
	rm -f $(NAME) $(NAME_C) $(BONUS_S) $(BONUS_C)

re : fclean all
