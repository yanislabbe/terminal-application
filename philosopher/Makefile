# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylabbe <ylabbe@student.42quebec.c>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/26 21:20:11 by ylabbe            #+#    #+#              #
#    Updated: 2022/11/27 16:49:06 by ylabbe           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

S = src/
O = obj/

SRCS = $Smain.c \
	   $Srun_the_program.c \
	   $Sinitialize_the_program.c \

OBJS = $(SRCS:$S%=$O%.o)

NAME = philo

CC = gcc

FLAGS = -pthread -Wall -Werror -Wextra

RM = rm -rfd

all:	$(NAME)

$O:
	@mkdir $@

$(OBJS): | $O

$(OBJS): $O%.o: $S%
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $^ -o $@

clean:
	@$(RM) $(OBJS)
	@$(RM) $O

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
