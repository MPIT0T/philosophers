# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/22 15:09:12 by mpitot            #+#    #+#              #
#    Updated: 2024/03/01 15:32:32 by mpitot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c				\
			utils.c				\
			init.c				\
			print_info.c		\
			time.c				\
			routine_odd.c		\
			routine_pair.c		\
			routine_utils.c		\
			fork_operations.c	\
			free.c

OBJS	=	$(SRCS:%.c=${OBJ_D}%.o)

SRC_D	=	srcs/

OBJ_D	=	.objs/

HEAD	=	includes/

NAME	=	philo

CC		=	cc

FLAGS	=	-Wall -Wextra -Werror #-fsanitize=address -g3

RED		=	\033[1;31m
GREEN	=	\033[1;32m
YELLOW	=	\033[1;33m
BLUE	=	\033[1;34m
MAGENTA	=	\033[1;35m
CYAN	=	\033[1;36m
WHITE	=	\033[1;37m
DEFAULT	=	\033[0m
UP		=	"\033[A"
CUT		=	"\033[K"

CHANGED	=	0

all		:	${NAME}

${OBJS}	:	${OBJ_D}%.o: ${SRC_D}%.c includes/philo.h
	@echo "$(YELLOW)Compiling [$<]$(DEFAULT)"
	@${CC} ${FLAGS} -I${HEAD} -c $< -o $@
	@printf ${UP}${CUT}
	@echo "$(GREEN)[$<] compiled.$(DEFAULT)"

${NAME}	:	${OBJ_D} ${OBJS} Makefile includes/philo.h
	@echo "$(YELLOW)Compiling '$(NAME)'...$(DEFAULT)"
	@${CC} ${FLAGS} -lpthread -I${HEAD} -o ${NAME} ${OBJS}
	@$(eval CHANGED=1)
	@printf ${UP}${CUT}
	@echo "$(GREEN)'$(NAME)' compiled.$(DEFAULT)"

${OBJ_D}:
	@mkdir -p ${OBJ_D}

clean	:
	@rm -rf ${OBJ_D}
	@echo "$(MAGENTA)'$(OBJ_D)' deleted.$(DEFAULT)"

fclean	:	clean
	@rm -f ${NAME}
	@echo "$(MAGENTA)'$(NAME)' deleted.$(DEFAULT)"

re		:	fclean all

.PHONY	:	all clean fclean re

.NOTPARALLEL all:
	@if [ $(CHANGED) -eq 0 ]; then \
		echo "$(YELLOW)Nothing to be done for '$(NAME)'.$(DEFAULT)"; \
	fi
