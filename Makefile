# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunwkim <hyunwkim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/13 22:28:48 by hyunwkim          #+#    #+#              #
#    Updated: 2021/08/14 03:01:55 by hyunwkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_S = server 
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

S_SRCS 		= $(addsuffix SRCS_DIR, $(S_FUNC))
C_SRCS 		= $(addsuffix SRCS_DIR, $(C_FUNC))
S_SRCS_B    = $(addsuffix BONUS_DIR, $(S_FUNC_B))
C_SRCS_B    = $(addsuffix BONUS_DIR, $(C_FUNC_B))

S_OBJS 		= $(S_SRCS:.c=.o)
C_OBJS 		= $(C_SRCS:.c=.o)
S_OBJS_B 	= $(S_SRCS_B:.c=.o)
C_OBJS_B 	= $(C_SRCS_B:.c=.o)

all : $(NAME)

$(NAME) : $(SERVER) $(CLIENT)

$(SERVER) : $(S_OBJS)
		$(CC) $(CFLAGS) $(S_OBJS) -o $(NAME_S)
	
$(CLIENT) : $(C_OBJS)
		$(CC) $(CFLAGS) $(C_OBJS) -o $(NAME_C)

$(SERVER_B) : $(S_OBJS_B)
		$(CC) $(CFLAGS) $(S_OBJS_B) -o $(BONUS_S)

$(CLIENT_B) : $(S_OBJS_B)
		$(CC) $(CFLAGS) $(S_OBJS_B) -o $(BONUS_S)
	
bonus :  $(SERVER_B) $(CLIENT_B)

clean :
	rm -f $(S_OBJS) $(C_OBJS) $(S_OBJS_B) $(C_OBJS_B)

fclean : clean
	rm -f $(NAME_S) $(NAME_C) $(BONUS_S) $(BONUS_C)


re : fclean all
