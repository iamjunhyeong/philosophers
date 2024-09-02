# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junhyeong <junhyeong@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/01 00:14:48 by junhyeong         #+#    #+#              #
#    Updated: 2024/09/02 17:51:51 by junhyeong        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC	= main.c \
		utils.c \
		init.c \
		philo_01.c \
		philo_02.c

INCDIRS = ./

OBJS = $(SRC:.c=.o)
OBJS_BONUS = $(SRC_BONUS:.c=.o)

CC = cc
MAKE = make
RM = rm -f
CFLAGS = -Wall -Wextra -Werror $(foreach D, $(INCDIRS), -I$(D))
ARFLAGS = rs

all: $(NAME)

%.o: %.c $(foreach D, $(INCDIRS), $(D)*.h)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
		$(CC) -o $(NAME) $(OBJS)
	
clean:
	${RM} *.o 

fclean: clean
	${RM} $(NAME) 

re: fclean all

.PHONY: all clean fclean re bonus