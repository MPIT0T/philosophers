# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/22 15:09:12 by mpitot            #+#    #+#              #
#    Updated: 2024/02/29 15:26:24 by mpitot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c			\
			utils.c			\
			init.c			\
			print_info.c	\
			time.c			\
			routine_odd.c	\
			routine_pair.c	\
			routine_utils.c	\
			fork_operations.c

OBJS	=	$(SRCS:%.c=${OBJ_D}%.o)

SRC_D	=	srcs/

OBJ_D	=	.objs/

HEAD	=	includes/

NAME	=	philo

CC		=	cc

FLAGS	=	-Wall -Wextra -Werror

GREEN	=	\033[1;32m
BLUE	=	\033[1;34m
RED		=	\033[1;31m
YELLOW	=	\033[1;33m
DEFAULT	=	\033[0m
UP		=	"\033[A"
CUT		=	"\033[K"

CHANGED	=	0

all		:	${NAME}

${OBJS}	:	${OBJ_D}%.o: ${SRC_D}%.c includes/philo.h
	@echo "$(YELLOW)Compiling [$<]$(DEFAULT)"
	@${CC} ${FLAGS} -c $< -o $@
	@printf ${UP}${CUT}

${NAME}	:	${OBJ_D} ${OBJS} Makefile includes/philo.h
	@${CC} ${FLAGS} -lpthread -I{HEAD} -o ${NAME} ${OBJS}
	@$(eval CHANGED=1)
	@echo "$(GREEN)$(NAME) compiled.$(DEFAULT)"

${OBJ_D}:
	@mkdir -p ${OBJ_D}

clean	:
	@rm -rf ${OBJ_D}
	@echo "$(BLUE)$(OBJ_D) deleted.$(DEFAULT)"

fclean	:	clean
	@rm -f ${NAME}
	@echo "$(BLUE)$(NAME) deleted.$(DEFAULT)"

re		:	fclean all

.PHONY	:	all clean fclean re

.NOTPARALLEL all:
	@if [ $(CHANGED) -eq 0 ]; then \
		echo "$(YELLOW)Nothing to do for all.$(DEFAULT)"; \
	fi
